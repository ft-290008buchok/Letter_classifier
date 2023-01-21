# Классификатор рукописных букв на основе нейронной сети на C++
![neural network](https://img.shields.io/badge/-?style=for-the-badge&logo=&logoColor=white)


В этом проекте реализован классификатор рукописных букв. Для классификации используется нейронная сеть прямого распространения, обучение происходит по алгоритму обратного распространения ошибки.
Пользователю предлагается от руки нарисовать по несколько примеров пяти рукописных букв, например можно нарисоват
по 15 латинских букв A, B, C, D и E как в этом примере

![Скриншот 20-01-2023 220533](https://user-images.githubusercontent.com/71639489/213763573-a3d8daaf-43d0-4ac2-a1bd-ee7c055c5663.jpg)

За тем происходит обучение нейросети, а потом пользователю предлагается нарисовать по несколько примеров тех же самых букв для
тестирования нейросети, например по 5 букв как в данном примере

<img src="https://user-images.githubusercontent.com/71639489/213845451-9eefa3b6-6bd8-4e35-8fab-3a7f89d53d5a.jpg" width="200" height="200" />


После чего программа проводит тест на введённых примерах и выдаст оценку точности классификации тестовых букв.
# Использование
Пользователю предлагается самостоятельно создать  датасет, для этого во всплывающих окнах размером 300 Х 300 нужно мышкой, зажав ЛКМ, нарисовать по одной букве. Когда буква нарисована, нужно закрыть всплывающее окно, окно для следующей буквы откроется само. Классов букв всего 5, для каждого класса рекомендуется нарисовать хотя бы по 10 букв. Пример нарисованной буквы во всплывающем оке прелставлен на рисунке ниже.

<img src="https://user-images.githubusercontent.com/71639489/213845029-130fd1a7-5e45-417d-a472-b2c72cd772fb.jpg" width="200" height="200" /> 


После того как обучающая выборка загружена, изображения букв сжимаются до размера 50 х 50, и изображение всей обучающей выборки будет выведено в одном окне как покозано ниже.

![Скриншот 20-01-2023 220533](https://user-images.githubusercontent.com/71639489/213845135-fb501502-17f0-45cb-a42a-ac1ee3eb8cc7.jpg)

Вам будет предложено сохранить дата сет в память на случай, если в следующий раз вы захотите сэкономить время на его создание. Потом методом обратного распространения ошибки обучится нейронная сеть. После чего вам будет предложено так же мышклй нарисовать по несколько тестовых примеров для каждой буквы. После загрузки тестовой выборки она будет пропущена через обученную нейросеть и вы увидите оценку точности классификации ваших тестовых букв.
# Характеристики нейронной сети
Для классификации используется нейронная сеть прямого распространения. Перцептрон имеет 4 слоя, размеры входного, первого скрытого, второго скрытого и выходного слоёв равны 2500, 500, 50 и 5 соответственно.
Вид функции активации - сигмоида. Вид функции ошибки - среднеквадратичное отклонение. Алгоритм обучения - метод обратного распространения ошибки.

    layer number =        4
    input layer size =    2500
    hidden layers sizes = {500, 50}
    output layer size =   5
    activation function:  f(s) = (1 + e^(-a * s))^(-1), a = 0.3
    error function:       (x1 - t1)^2 + ... + (xn - tn)^2, x - output layer neuron out, t - output reference value, n = 5
  
# Точность
После обучения на дата сете из 75 латинских букв A, B, C, D, E (по 15 на каждый класс) и тестирования на выбрке из 25 букв (по 5 на каждый класс):

    Классификация обучающей выборки - точность 100 %
    Классификация тестовой выборки - точность 92 %


# Модуль нейросети classifier
Представляет из себя мини frame work для создания и обучения нейросети методом обратного распространения ошибки для языка C++.
Конструктор classifier принимает несколько параметров: 
1 - количество слоёв
2 - list с размерами слоёв начиная с выходного и заканчивая входным
3 - learning rate (шаг градиентного спуска)
4 - диапазон, в котором будут сгенерированы веса нейросети перед началом обучения
5 - количество итераций обратного распространения ошибки с применением поправок к весам
В данном проекте нейросеть была создана вызовом конструктора со следующими параметрами

    classifier cl(4, { 5, 50, 500, 2500 }, 1.0, 1.0, 6);
    
Данная нейронная сеть имеет 4 слоя 5 х 50 х 500 х 2500, learning rate = 1, начальные веса нейросети сгенерированы в диапазоне (-1; 1) и при обучении будет совершено 6 итераций алгоритма.

Для загрузки дата сета используется метод classifier::selection_load(dataset), Дата сет должен быть представлен в виде структуры
dataset.

    struct dataset
    {
    public:
        std::vector<int> data;
        int size_for_one_letter;
        int letters_number;
        int immage_size;
        std::vector<std::vector<int>> marks;
    };
    
Вектор data хранит все изображения дата сета в виде одномерного массива, в котором значения интенсивности пикселей каждого изображения записаны одно за другим (изображения должны быть чёрнобелыми). В size_for_one_letter хранится количество обучающих примеров на один класс, в letters_number хранится количество классов, в immage_size хранится количество пикселей в одном изображении, а в векторе marks хранятся метки обучающей выборки в виде двумерного массива, размер одной метки равен размеру выходного слоя, в данном проекте это 5, а количество меток равно letters_number * size_for_one_letter.

Формат метки:

Все значения метки равны нулю, а значение, номер которого совпадает с классом, к которому принадлежит изображение равно единице.
Например, если 24 изображение в дата сете принадлежит 3 классу, а всего классов 5, то 24 метка будет выглядеть вот так - {0, 0, 1, 0, 0}.

Для обучения нужно просто вызвать метод classifier::learn().

Проверить точность обучения на обучающей выборке можно вызвать метод classifier::accuracy_test_on_dataset(). В консоль будет выведен результат классификации элементов датасета, для каждого элемента будет выведен 0, есди классификация выполнена неправильно или 1, если классификация выполнена правильно, а также будет выведена общая точность классификации по всему дата сету. Идеальный результат теста на дата сете выглядит вот так
![Скриншот 20-01-2023 220843 — копия](https://user-images.githubusercontent.com/71639489/213861107-25707bbb-ac91-4760-8c1b-8fc7ee49244d.jpg)


А для классификации нового изображения с помощью обученной нейросети используется метод classifyer::classify(std::vector<int>::iterator immage), который принимает на вход итератор вектора входного изображения, представленного в виде одномерного массива, длина которого равна размеру входного слоя нейросети (по аналогии с форматом dataset), а возвращает номер класса, который ему присвоила нейросеть.
# 
Модуль classifier рассчитан на проектирование нейросети с любым количеством слоёв любого размера и может быть использован в других проектах.
