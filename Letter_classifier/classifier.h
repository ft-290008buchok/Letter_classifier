#pragma once

const double steepness = 0.3;

#include<iostream>
#include<vector>
#include<ctime>
#include<cstdlib>
#include "data_load.h"

class neuron
{
public:
	double s = 0;
	double out = 0;
	void activate(){ out = 1.0 / (1.0 + pow(M_E, -s * steepness)); }
};

class classifier
{
public:
	classifier(int numder_of_layers, std::initializer_list<int> sizes, double _learning_rate, double _initial_weights_range);
	void selection_load(dataset data);
	void loop(std::vector<int>::iterator immage);
	void train_loop(int learning_vector_number);
	void learn();
	void accuracy_test_on_dataset();
private:
	double learning_rate = 0;
	double initial_weights_range = 1;
	int layer_quantity = 0;
	std::vector<int> layer_sizes;
	std::vector<std::vector<std::vector<double>>> weights;
	std::vector<std::vector<std::vector<double>>> amendments;
	std::vector<std::vector<neuron>> layers;
	dataset DATA;
	double error_value = 0;
	void _calc_amendments(int learning_vector_number);
	void _calc_error_function(int learning_vector_number);
	void _apply_amendments();
	bool _test(int learning_vector_number);
};

int generate(int, int);
double math_random();