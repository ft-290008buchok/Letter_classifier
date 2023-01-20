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
    std::vector<std::vector<int>> marks;
};

dataset load_dataset();

void _paint_over(Image& im, int x, int y, Color color, int radius);
double _euclid_distance(int x1, int y1, int x2, int y2);
void _load_pixels(std::vector<std::vector<int>>::iterator mask, int x, int y, int radius);
void _max_pull_compress_mask(std::vector<std::vector<int>>::iterator original_mask, std::vector<std::vector<int>>::iterator compressed_mask, int compression_lavel);



