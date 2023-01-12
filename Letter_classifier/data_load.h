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
};

dataset load_dataset();



