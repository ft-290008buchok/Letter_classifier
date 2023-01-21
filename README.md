# Классификатор рукописных букв на основе нейронной сети
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

    layer number = 4
    input layer size = 2500
    hidden layers sizes = {500, 50}
    output layer size = 5
    activation function: f(s) = (1 + e^(-a * s))^(-1), a = 0.3
    error function: (x1 - t1)^2 + ... + (xn - tn)^2, x - output layer neuron out, t - output reference value, n = 5
  
Класс нейросети classifier рассчитан на проеатирование нейросети с любым количеством слоёв любого размера и может быть использован в других проектах.
