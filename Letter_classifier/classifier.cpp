#include "classifier.h"

classifier::classifier(int numder_of_layers, std::initializer_list<int> sizes, double _learning_rate)
{
    learning_rate = _learning_rate;
    layer_quantity = numder_of_layers;
    for (auto size : sizes)
        layer_sizes.push_back(size);

    for (int i = 0; i < layer_quantity - 1; i++)
    {
        std::vector<std::vector<double>> matrix(layer_sizes[i], std::vector<double>(layer_sizes[i + 1], 0));
        for (int j = 0; j < layer_sizes[i]; j++)
            for (int k = 0; k < layer_sizes[i + 1]; k++)
                matrix[j][k] = math_random();

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
    /*
    for (int n = 0; n < layer_quantity - 1; n++)
    {
        for (int i = 0; i < layer_sizes[n]; i++)
        {
            for (int j = 0; j < layer_sizes[n + 1]; j++)
                printf("%f  ", weights[n][i][j]);
            std::cout << std::endl;
        }
    }
    */
}

void classifier::selection_load(dataset data)
{
    DATA = data;
}

void classifier::loop(std::vector<int>::iterator immage)
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
            layers[n][i].activate();
        }
    }

    for (int i = 0; i < layer_sizes[0]; i++)
        printf("%d  %f\n", i, layers[0][i].out);

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
        first_layer_derivatives_by_s[i] = steepness * pow(M_E, -layers[0][i].s * steepness) / pow((1 + pow(M_E, -layers[0][i].s * steepness)), 2)    *    2 * (layers[0][i].out - DATA.marks[learning_vector_number][i]);

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

            current_layer_derivatives_by_s[i] = steepness * pow(M_E, -layers[n][i].s * steepness) / pow((1 + pow(M_E, -layers[n][i].s * steepness)), 2) * summ;
        }
        derivatives_by_s.push_back(current_layer_derivatives_by_s);
    }

    for (int n = 0; n < layer_quantity - 1; n++)
        for (int i = 0; i < layer_sizes[n]; i++)
            for (int j = 0; j < layer_sizes[n + 1]; j++)
                amendments[n][i][j] = layers[n + 1][j].out * derivatives_by_s[n][i];
}

int generate(int left_border, int right_border)
{
    return left_border + rand() % (right_border - left_border + 1);
}

double math_random()
{
    return generate(0, 1000) / 1000.0;
}