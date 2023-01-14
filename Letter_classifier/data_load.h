#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace sf;

struct dataset
{
public:
    std::vector<int> data;
    int size_for_one_letter;
    int letters_number;
    int immage_size;
};

dataset load_dataset();



