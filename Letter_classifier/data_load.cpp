#include "data_load.h"

using namespace sf;

void _paint_over(Image& im, int x, int y, Color color, int radius);
double _euclid_distance(int x1, int y1, int x2, int y2);
void _load_pixels(std::vector<std::vector<int>>::iterator mask, int x, int y, int radius);
void _max_pull_compress_mask(std::vector<std::vector<int>>::iterator original_mask, std::vector<std::vector<int>>::iterator compressed_mask, int compression_lavel);

dataset load_dataset()
{
    dataset LETTERS;
    std::cout << "Do you want to load data set from memory or create a new one?  (create a new one / load from memory -- 1 / 0):  ";
    bool create;
    std::cin >> create;

    if (create)
    {
        Texture t;
        Sprite s;

        Vector2i mouse_pos;
        bool mouse_pressed = false;
        std::vector<std::vector<int>> mask(300, std::vector<int>(300, 0));
        std::vector<std::vector<int>> compressed_mask(50, std::vector<int>(50, 0));

        std::cout << "You are invited to draw several training examples for each of the five letters\n\n";

        std::cout << "How many examples of one letter for data set would you like to darw:  ";
        std::cin >> LETTERS.size_for_one_letter;
        //DATASET
        std::vector<std::vector<std::vector<int>>> A_letters(LETTERS.size_for_one_letter, std::vector<std::vector<int>>(50, std::vector<int>(50, 0)));
        std::vector<std::vector<std::vector<int>>> B_letters(LETTERS.size_for_one_letter, std::vector<std::vector<int>>(50, std::vector<int>(50, 0)));
        std::vector<std::vector<std::vector<int>>> C_letters(LETTERS.size_for_one_letter, std::vector<std::vector<int>>(50, std::vector<int>(50, 0)));
        std::vector<std::vector<std::vector<int>>> D_letters(LETTERS.size_for_one_letter, std::vector<std::vector<int>>(50, std::vector<int>(50, 0)));
        std::vector<std::vector<std::vector<int>>> E_letters(LETTERS.size_for_one_letter, std::vector<std::vector<int>>(50, std::vector<int>(50, 0)));

        ContextSettings settings;
        settings.antialiasingLevel = 8;

        for (int i = 0; i < 5; i++)
        {
            if (i == 0)
                printf("\nWrite first %d letters\n", LETTERS.size_for_one_letter);
            else
                printf("Write next %d letters\n", LETTERS.size_for_one_letter);

            for (int j = 0; j < LETTERS.size_for_one_letter; j++)
            {
                Image im;
                im.create(300, 300);

                for (int k = 0; k < 50; k++)
                    for (int n = 0; n < 50; n++)
                        compressed_mask[n][k] = 0;

                for (int k = 0; k < 300; k++)
                    for (int n = 0; n < 300; n++)
                        mask[n][k] = 0;

                RenderWindow window(VideoMode(300, 300), "Draw your letter", Style::Default, settings);
                while (window.isOpen())
                {
                    // Обрабатываем очередь событий в цикле
                    Event event;
                    while (window.pollEvent(event))
                    {
                        if (event.type == Event::Closed)
                            window.close();
                        if (event.type == Event::MouseButtonPressed)
                            mouse_pressed = true;
                        if (event.type == Event::MouseButtonReleased)
                            mouse_pressed = false;
                        if (mouse_pressed)
                        {
                            mouse_pos = Mouse::getPosition(window);
                            _paint_over(im, mouse_pos.x, mouse_pos.y, Color::White, 10);
                            _load_pixels(mask.begin(), mouse_pos.x, mouse_pos.y, 10);
                        }
                    }
                    // Отрисовка окна
                    window.clear();

                    t.loadFromImage(im);
                    s.setTexture(t);
                    s.setPosition(0, 0);
                    window.draw(s);

                    window.display();
                }

                _max_pull_compress_mask(mask.begin(), compressed_mask.begin(), 6);

                if (i == 0)
                    A_letters[j] = compressed_mask;
                else if (i == 1)
                    B_letters[j] = compressed_mask;
                else if (i == 2)
                    C_letters[j] = compressed_mask;
                else if (i == 3)
                    D_letters[j] = compressed_mask;
                else if (i == 4)
                    E_letters[j] = compressed_mask;
            }
        }

        Image im_compressed, im_empty;
        im_compressed.create(50, 50);
        im_empty.create(50, 50);

        std::cout << "\nThat's how your dataset looks like after compressing\n";

        RenderWindow window_compressed(VideoMode(50 * LETTERS.size_for_one_letter, 50 * 5), "Your letters after compressing", Style::Default, settings);
        while (window_compressed.isOpen())
        {
            // Обрабатываем очередь событий в цикле
            Event event;
            while (window_compressed.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window_compressed.close();
            }
            // Отрисовка окна
            window_compressed.clear();

            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < LETTERS.size_for_one_letter; j++)
                {

                    t.loadFromImage(im_empty);
                    s.setTexture(t);

                    if (i == 0)
                    {
                        for (int k = 0; k < 50; k++)
                            for (int n = 0; n < 50; n++)
                                im_compressed.setPixel(n, k, Color(A_letters[j][k][n] * 255, A_letters[j][k][n] * 255, A_letters[j][k][n] * 255));
                        t.loadFromImage(im_compressed);
                        s.setTexture(t);
                        s.setPosition(50 * j, 50 * i);
                        window_compressed.draw(s);
                    }
                    else if (i == 1)
                    {
                        for (int k = 0; k < 50; k++)
                            for (int n = 0; n < 50; n++)
                                im_compressed.setPixel(n, k, Color(B_letters[j][k][n] * 255, B_letters[j][k][n] * 255, B_letters[j][k][n] * 255));
                        t.loadFromImage(im_compressed);
                        s.setTexture(t);
                        s.setPosition(50 * j, 50 * i);
                        window_compressed.draw(s);
                    }
                    else if (i == 2)
                    {
                        for (int k = 0; k < 50; k++)
                            for (int n = 0; n < 50; n++)
                                im_compressed.setPixel(n, k, Color(C_letters[j][k][n] * 255, C_letters[j][k][n] * 255, C_letters[j][k][n] * 255));
                        t.loadFromImage(im_compressed);
                        s.setTexture(t);
                        s.setPosition(50 * j, 50 * i);
                        window_compressed.draw(s);
                    }
                    else if (i == 3)
                    {
                        for (int k = 0; k < 50; k++)
                            for (int n = 0; n < 50; n++)
                                im_compressed.setPixel(n, k, Color(D_letters[j][k][n] * 255, D_letters[j][k][n] * 255, D_letters[j][k][n] * 255));
                        t.loadFromImage(im_compressed);
                        s.setTexture(t);
                        s.setPosition(50 * j, 50 * i);
                        window_compressed.draw(s);
                    }
                    else if (i == 4)
                    {
                        for (int k = 0; k < 50; k++)
                            for (int n = 0; n < 50; n++)
                                im_compressed.setPixel(n, k, Color(E_letters[j][k][n] * 255, E_letters[j][k][n] * 255, E_letters[j][k][n] * 255));
                        t.loadFromImage(im_compressed);
                        s.setTexture(t);
                        s.setPosition(50 * j, 50 * i);
                        window_compressed.draw(s);
                    }
                }
            }
            window_compressed.display();
        }

        std::cout << "Do you want to load this dataset to the memory?  (yes / no -- 1 / 0):  ";
        bool load_data;
        std::cin >> load_data;

        if (load_data)
        {
            std::fstream DATASET("DATASET.txt");
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < LETTERS.size_for_one_letter; j++)
                {
                    if (i == 0)
                    {
                        for (int k = 0; k < 50; k++)
                            for (int n = 0; n < 50; n++)
                                DATASET << A_letters[j][k][n] << " ";
                    }
                    else if (i == 1)
                    {
                        for (int k = 0; k < 50; k++)
                            for (int n = 0; n < 50; n++)
                                DATASET << B_letters[j][k][n] << " ";
                    }
                    else if (i == 2)
                    {
                        for (int k = 0; k < 50; k++)
                            for (int n = 0; n < 50; n++)
                                DATASET << C_letters[j][k][n] << " ";
                    }
                    else if (i == 3)
                    {
                        for (int k = 0; k < 50; k++)
                            for (int n = 0; n < 50; n++)
                                DATASET << D_letters[j][k][n] << " ";
                    }
                    else if (i == 4)
                    {
                        for (int k = 0; k < 50; k++)
                            for (int n = 0; n < 50; n++)
                                DATASET << E_letters[j][k][n] << " ";
                    }
                }
            }
            DATASET.close();
        }




        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < LETTERS.size_for_one_letter; j++)
            {
                if (i == 0)
                {
                    for (int k = 0; k < 50; k++)
                        for (int n = 0; n < 50; n++)
                            LETTERS.data.push_back(A_letters[j][k][n]);
                }
                else if (i == 1)
                {
                    for (int k = 0; k < 50; k++)
                        for (int n = 0; n < 50; n++)
                            LETTERS.data.push_back(B_letters[j][k][n]);
                }
                else if (i == 2)
                {
                    for (int k = 0; k < 50; k++)
                        for (int n = 0; n < 50; n++)
                            LETTERS.data.push_back(C_letters[j][k][n]);
                }
                else if (i == 3)
                {
                    for (int k = 0; k < 50; k++)
                        for (int n = 0; n < 50; n++)
                            LETTERS.data.push_back(D_letters[j][k][n]);
                }
                else if (i == 4)
                {
                    for (int k = 0; k < 50; k++)
                        for (int n = 0; n < 50; n++)
                            LETTERS.data.push_back(E_letters[j][k][n]);
                }
            }
        }
    }
    else
    {
        std::cout << "How many examples of one letter are in your dataset?:  ";
        std::cin >> LETTERS.size_for_one_letter;

        std::fstream DATASET("DATASET.txt");
        int pixel;

        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < LETTERS.size_for_one_letter; j++)
            {
                for (int k = 0; k < 50; k++)
                    for (int n = 0; n < 50; n++)
                    {
                        DATASET >> pixel;
                        LETTERS.data.push_back(pixel);
                    }
            }
        }
        DATASET.close();
    }

    LETTERS.letters_number = 5;
    LETTERS.immage_size = 50;

    return LETTERS;
}

void _paint_over(Image& im, int x, int y, Color color, int radius)
{
    for (int i = -radius; i < radius; i++)
        for (int j = -radius; j < radius; j++)
            if (_euclid_distance(0, 0, i, j) <= radius)
                if (x + i < 300 && y + j < 300 && x + i > 0 && y + j > 0)
                    im.setPixel(x + i, y + j, color);
}

void _load_pixels(std::vector<std::vector<int>>::iterator mask, int x, int y, int radius)
{
    for (int i = -radius; i < radius; i++)
        for (int j = -radius; j < radius; j++)
            if (_euclid_distance(0, 0, i, j) <= radius)
                if (x + i < 300 && y + j < 300 && x + i > 0 && y + j > 0)
                    mask[y + j][x + i] = 1;
}

double _euclid_distance(int x1, int y1, int x2, int y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void _max_pull_compress_mask(std::vector<std::vector<int>>::iterator original_mask, std::vector<std::vector<int>>::iterator compressed_mask, int compression_lavel)
{
    int x, y, max, compressed_pixel_x, compressed_pixel_y;
    for (int original_pixel_y = 0, compressed_pixel_y = 0; original_pixel_y < 300; original_pixel_y += compression_lavel, compressed_pixel_y++)
    {
        for (int original_pixel_x = 0, compressed_pixel_x = 0; original_pixel_x < 300; original_pixel_x += compression_lavel, compressed_pixel_x++)
        {
            max = 0;
            for (y = original_pixel_y; y < original_pixel_y + compression_lavel; y++)
            {
                for (x = original_pixel_x; x < original_pixel_x + compression_lavel; x++)
                {
                    if (original_mask[y][x] > max)
                        max = original_mask[y][x];
                }
            }
            compressed_mask[compressed_pixel_y][compressed_pixel_x] = max;
        }
    }
}
