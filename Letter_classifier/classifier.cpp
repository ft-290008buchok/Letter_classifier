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

int generate(int left_border, int right_border)
{
    return left_border + rand() % (right_border - left_border + 1);
}

double math_random()
{
    return generate(0, 1000) / 1000.0;
}