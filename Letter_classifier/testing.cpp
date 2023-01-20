#include "testing.h"

void test(classifier cl)
{
    int size_for_one_letter;
    Texture t;
    Sprite s;

    Vector2i mouse_pos;
    bool mouse_pressed = false;
    std::vector<std::vector<int>> mask(300, std::vector<int>(300, 0));
    std::vector<std::vector<int>> compressed_mask(50, std::vector<int>(50, 0));

    std::cout << "You are invited to draw several testing examples for each of the five letters\n\n";
    std::cout << "How many examples of one letter for testing would you like to darw:  ";

    std::cin >> size_for_one_letter;

    std::vector<std::vector<std::vector<int>>> A_letters(size_for_one_letter, std::vector<std::vector<int>>(50, std::vector<int>(50, 0)));
    std::vector<std::vector<std::vector<int>>> B_letters(size_for_one_letter, std::vector<std::vector<int>>(50, std::vector<int>(50, 0)));
    std::vector<std::vector<std::vector<int>>> C_letters(size_for_one_letter, std::vector<std::vector<int>>(50, std::vector<int>(50, 0)));
    std::vector<std::vector<std::vector<int>>> D_letters(size_for_one_letter, std::vector<std::vector<int>>(50, std::vector<int>(50, 0)));
    std::vector<std::vector<std::vector<int>>> E_letters(size_for_one_letter, std::vector<std::vector<int>>(50, std::vector<int>(50, 0)));

    ContextSettings settings;
    settings.antialiasingLevel = 8;

    for (int i = 0; i < 5; i++)
    {
        if (i == 0)
            printf("\nWrite first %d letters\n", size_for_one_letter);
        else
            printf("Write next %d letters\n", size_for_one_letter);

        for (int j = 0; j < size_for_one_letter; j++)
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

    std::cout << "\nThat's how testing examples looks like after compressing\n";

    RenderWindow window_compressed(VideoMode(50 * size_for_one_letter, 50 * 5), "Your letters after compressing", Style::Default, settings);
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
            for (int j = 0; j < size_for_one_letter; j++)
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

    std::vector<int> im(2500, 0);
    int all = 5 * size_for_one_letter;
    int recognized = 0;
    int pixel = 0;

    for (int c = 0; c < 5; c++)
    {
        for (int e = 0; e < size_for_one_letter; e++)
        {
            pixel = 0;
            if (c == 0)
            {
                for (int i = 0; i < 50; i++)
                    for (int j = 0; j < 50; j++, pixel++)
                        im[pixel] = A_letters[e][i][j];
                if (cl.classify(im.begin()) == 0)
                {
                    recognized++;
                    std::cout << "1  ";
                }
                else
                    std::cout << "0  ";
                    
            }
            else if (c == 1)
            {
                for (int i = 0; i < 50; i++)
                    for (int j = 0; j < 50; j++, pixel++)
                        im[pixel] = B_letters[e][i][j];
                if (cl.classify(im.begin()) == 1)
                {
                    recognized++;
                    std::cout << "1  ";
                }
                else
                    std::cout << "0  ";
            }
            else if (c == 2)
            {
                for (int i = 0; i < 50; i++)
                    for (int j = 0; j < 50; j++, pixel++)
                        im[pixel] = C_letters[e][i][j];
                if (cl.classify(im.begin()) == 2)
                {
                    recognized++;
                    std::cout << "1  ";
                }
                else
                    std::cout << "0  ";
            }
            else if (c == 3)
            {
                for (int i = 0; i < 50; i++)
                    for (int j = 0; j < 50; j++, pixel++)
                        im[pixel] = D_letters[e][i][j];
                if (cl.classify(im.begin()) == 3)
                {
                    recognized++;
                    std::cout << "1  ";
                }
                else
                    std::cout << "0  ";
            }
            else if (c == 4)
            {
                for (int i = 0; i < 50; i++)
                    for (int j = 0; j < 50; j++, pixel++)
                        im[pixel] = E_letters[e][i][j];
                if (cl.classify(im.begin()) == 4)
                {
                    recognized++;
                    std::cout << "1  ";
                }
                else
                    std::cout << "0  ";
            }
        }
        std::cout << std::endl;
    }

    printf("\nAccuracy on test = %f\n\n", (double)recognized / (double)all);
}
