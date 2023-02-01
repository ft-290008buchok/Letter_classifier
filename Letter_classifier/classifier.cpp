#include "classifier.h"

classifier::classifier(int numder_of_layers, std::initializer_list<int> sizes, double _learning_rate, double _initial_weights_range, int _learning_iterations_num, double _sigmoid_steepness, double _lr_multiplier)
{
    learning_rate = _learning_rate;
    initial_weights_range = _initial_weights_range;
    layer_quantity = numder_of_layers;
    learning_iterations_num = _learning_iterations_num;
    sigmoid_steepness = _sigmoid_steepness;
    lr_multiplier = _lr_multiplier;
    for (auto size : sizes)
        layer_sizes.push_back(size);

    for (int i = 0; i < layer_quantity - 1; i++)
    {
        std::vector<std::vector<double>> matrix(layer_sizes[i], std::vector<double>(layer_sizes[i + 1], 0));
        for (int j = 0; j < layer_sizes[i]; j++)
            for (int k = 0; k < layer_sizes[i + 1]; k++)
                matrix[j][k] = ( -1.0 + 2.0 * math_random()) * initial_weights_range;

        weights.push_back(matrix);
    }

    for (int i = 0; i < layer_quantity - 1; i++)
    {
        std::vector<std::vector<double>> matrix(layer_sizes[i], std::vector<double>(layer_sizes[i + 1], 0));
        amendments.push_back(matrix);
    }

    for (int i = 0; i < layer_quantity; i++)
    {
        std::vector<neuron> layer(layer_sizes[i]);
        layers.push_back(layer);
    }
}

void classifier::selection_load(dataset data)
{
    DATA = data;
}

void classifier::_loop(std::vector<int>::iterator immage)
{
    for (int i = 0; i < layer_sizes[layer_quantity - 1]; i++)
        layers[layer_quantity - 1][i].out = (double)immage[i];

    for (int n = layer_quantity - 2; n > -1; n--)
    {
        for (int i = 0; i < layer_sizes[n]; i++)
        {
            layers[n][i].s = 0;
            for (int j = 0; j < layer_sizes[n + 1]; j++)
                layers[n][i].s += layers[n + 1][j].out * weights[n][i][j];
            layers[n][i].activate(sigmoid_steepness);
        }
    }
}

void classifier::_calc_error_function(int learning_vector_number)
{
    error_value = 0;
    for (int i = 0; i < layer_sizes[0]; i++)
        error_value += pow((layers[0][i].out - DATA.marks[learning_vector_number][i]), 2);
}

void classifier::_calc_amendments(int learning_vector_number)
{
    std::vector<std::vector<double>> derivatives_by_s;

    std::vector<double> first_layer_derivatives_by_s(layer_sizes[0]);
    for (int i = 0; i < layer_sizes[0]; i++)
        first_layer_derivatives_by_s[i] = sigmoid_steepness * pow(M_E, -layers[0][i].s * sigmoid_steepness) / pow((1 + pow(M_E, -layers[0][i].s * sigmoid_steepness)), 2)    *    2 * (layers[0][i].out - DATA.marks[learning_vector_number][i]);

    derivatives_by_s.push_back(first_layer_derivatives_by_s);
    
    double summ;
    for (int n = 1; n < layer_quantity - 1; n++)
    {
        std::vector<double> current_layer_derivatives_by_s(layer_sizes[n]);
        for (int i = 0; i < layer_sizes[n]; i++)
        {
            summ = 0;
            for (int j = 0; j < layer_sizes[n - 1]; j++)
                summ += derivatives_by_s[n - 1][j] * weights[n - 1][j][i];

            current_layer_derivatives_by_s[i] = sigmoid_steepness * pow(M_E, -layers[n][i].s * sigmoid_steepness) / pow((1 + pow(M_E, -layers[n][i].s * sigmoid_steepness)), 2) * summ;
        }
        derivatives_by_s.push_back(current_layer_derivatives_by_s);
    }

    for (int n = 0; n < layer_quantity - 1; n++)
        for (int i = 0; i < layer_sizes[n]; i++)
            for (int j = 0; j < layer_sizes[n + 1]; j++)
                amendments[n][i][j] = layers[n + 1][j].out * derivatives_by_s[n][i];
}

void classifier::_apply_amendments()
{
    for (int n = 0; n < layer_quantity - 1; n++)
        for (int i = 0; i < layer_sizes[n]; i++)
            for (int j = 0; j < layer_sizes[n + 1]; j++)
                weights[n][i][j] -= learning_rate * amendments[n][i][j];
}

void classifier::train_loop(int learning_vector_number)
{
    std::vector<int> im(DATA.immage_size, 0);
    for (int i = learning_vector_number * DATA.immage_size, k = 0; i < (learning_vector_number + 1) * DATA.immage_size; i++, k++)
        im[k] = DATA.data[i];

    _loop(im.begin());
    for (int i = 0; i < layer_sizes[0]; i++)
        printf("%d  %f\n", i, layers[0][i].out);
    _calc_error_function(learning_vector_number);
    std::cout << error_value << std::endl;
    _calc_amendments(learning_vector_number);
    _apply_amendments();

    _loop(im.begin());
    for (int i = 0; i < layer_sizes[0]; i++)
        printf("%d  %f\n", i, layers[0][i].out);
    _calc_error_function(learning_vector_number);
    std::cout << error_value << std::endl;
}

void classifier::learn()
{
    std::cout << "Learning...\n\n";

    std::vector<int> numbers(DATA.letters_number * DATA.size_for_one_letter, 0);
    for (int n = 0; n < DATA.letters_number * DATA.size_for_one_letter; n++)
        numbers[n] = n;

    std::vector<int> im(DATA.immage_size, 0);
    for (int iter = 0; iter < learning_iterations_num; iter++)
    {
        for (int n = 0; n < DATA.letters_number * DATA.size_for_one_letter; n++)
            std::swap(numbers[n], numbers[rand() % (DATA.letters_number * DATA.size_for_one_letter)]);

        for (int n = 0; n < DATA.letters_number * DATA.size_for_one_letter; n++)
        {
            for (int i = numbers[n] * DATA.immage_size, k = 0; i < (numbers[n] + 1) * DATA.immage_size; i++, k++)
                im[k] = DATA.data[i];

            _loop(im.begin());
            _calc_amendments(numbers[n]);
            _apply_amendments();
        }
        learning_rate *= lr_multiplier;
    }
}

bool classifier::_test(int learning_vector_number)
{
    std::vector<int> im(DATA.immage_size, 0);

    for (int i = learning_vector_number * DATA.immage_size, k = 0; i < (learning_vector_number + 1) * DATA.immage_size; i++, k++)
        im[k] = DATA.data[i];

    int max_num = 0;
    double max_value = 0;

    _loop(im.begin());
    for (int i = 0; i < layer_sizes[0]; i++)
        if (layers[0][i].out > max_value)
        {
            max_value = layers[0][i].out;
            max_num = i;
        } 

    if (DATA.marks[learning_vector_number][max_num] == 1)
        return true;
    else
        return false;
}
void classifier::accuracy_test_on_dataset()
{
    int all = DATA.letters_number * DATA.size_for_one_letter;
    int recognized = 0;
    for (int n = 0; n < all; n++)
    {
        if (n % DATA.size_for_one_letter == 0)
            std::cout << std::endl;

        if (_test(n))
        {
            std::cout << "1  ";
            recognized++;
        }
        else
            std::cout << "0  ";
    }

    printf("\nAccuracy on dataset = %f\n\n", (double)recognized / (double)all);
}

int classifier::classify(std::vector<int>::iterator immage)
{
    _loop(immage);

    int max_num = 0;
    double max_value = 0;

    for (int i = 0; i < layer_sizes[0]; i++)
        if (layers[0][i].out > max_value)
        {
            max_value = layers[0][i].out;
            max_num = i;
        }

    return max_num;
}

int generate(int left_border, int right_border)
{
    return left_border + rand() % (right_border - left_border + 1);
}

double math_random()
{
    return generate(0, 1000) / 1000.0;
}