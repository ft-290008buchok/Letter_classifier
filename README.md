![Скриншот 24-01-2023 123526 — копия](https://user-images.githubusercontent.com/71639489/214236017-ce64e0e6-d1fc-4071-9af7-34db4d049bbf.jpg)


# A handwritten letter classifier based on a neural network in C++
![neural network](https://img.shields.io/badge/neuralnetwork-000000?style=for-the-badge&logo=&logoColor=white)
![neural network](https://img.shields.io/badge/errorBackPropagation-000000?style=for-the-badge&logo=&logoColor=white)
![neural network](https://img.shields.io/badge/c++-000000?style=for-the-badge&logo=&logoColor=white)


In this project, a classifier of handwritten letters is implemented. For classification, a neural network of direct propagation is used, training takes place according to the algorithm of error back propagation.

# Table of contents
⭘ Neural Network Characteristics   
⭘ Accuracy   
⭘ Neural network module classifier   
⭘ Project launch  
⭘ Support   

# Neural Network Characteristics
A direct propagation neural network is used for classification. The perceptron has 4 layers, the sizes of the input, first hidden, second hidden and output layers are 2500, 500, 50 and 5, respectively.
The type of activation function is a sigmoid. The type of error function is the Mean Squared Error. The learning algorithm is a method of error back propagation. The type of gradient descent is stochastic gradient descent.

    layer number =            4
    input layer size =        2500
    hidden layers sizes =     {500, 50}
    output layer size =       5
    activation function:      (sigmoid) f(s) = (1 + e^(-a * s))^(-1), a = 0.4
    error function:           (MSE) (x1 - t1)^2 + ... + (xn - tn)^2, x - output layer neuron out, t - output reference value, n = 5
    learning rate =           1.0
    number of epochs =        8
    type of gradient descent: stochastic gradient descent
  
# Accuracy
After training on a data set of 75 Latin letters A, B, C, D, E (15 for each class) and testing on a sample of 25 letters (5 for each class):

    Classification of the training sample - accuracy 100 %
    Classification of the test sample - accuracy 92 %


# Classifier neural network module
It is a mini frame work for creating and training a neural network by the method of error back propagation with stochastic gradient descent for the C++ language.

The classifier module is designed for designing a neural network with any number of layers of any size and can be used in other projects.You can find the header file and the classifier implementation file in the project files.

The classifier constructor accepts several parameters:   
1 - number of layers   
2 - list with the sizes of layers starting from the output and ending with the input   
3 - learning rate (step of gradient descent)   
4 - the range in which the weights of the neural network will be generated before the start of training   
5 - the number of epochs   
6 - slope of the sigmoid   
In this project, the neural network was created by calling the constructor with the following parameters   

    classifier cl(4, { 5, 50, 500, 2500 }, 1.0, 1.0, 8, 0.4);
    
This neural network has 4 layers 5 x 50 x 500 x 2500, learning rate = 1, the initial weights of the neural network are generated in the range (-1; 1) and 8 epochs will be passed during training, and sigmoid looks like f(s) = (1 + e^(-0.4 * s))^(-1).   

To load the date set, the classifier::selection_load(dataset) method is used, the Date set must be represented as a structure
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
    
The data vector stores all the images of the date set as a one-dimensional array in which the pixel intensity values of each image are recorded one by one (the images must be black and white). 
size_for_one_letter stores the number of training examples per class, letters_number stores the number of classes, immage_size stores the number of pixels in one image, and the marks vector stores the labels of the training sample as a two-dimensional array, the size of one label is equal to the size of the output layer, in this project it is 5, and the number of labels is letters_number * size_for_one_letter.

Label format:

All label values are zero, and the value whose number matches the class to which the image belongs is equal to one.
For example, if the 24 image in the data set belongs to the 3rd class, and there are 5 classes in total, then the 24 label will look like this - {0, 0, 1, 0, 0}.

To learn, you just need to call the classifier::learn() method.

To check the accuracy of training on a training sample, you can call the classifier::accuracy_test_on_dataset() method. The result of the classification of the dataset elements will be output to the console, 0 will be output for each element if the classification is performed incorrectly or 1 if the classification is performed correctly, and the overall classification accuracy for the entire data set will also be output. The perfect test result on a date set looks like this
![Screenshot 20-01-2023 220843 — копия](https://user-images.githubusercontent.com/71639489/213861107-25707bbb-ac91-4760-8c1b-8fc7ee49244d.jpg)


And to classify a new image using a trained neural network, the classifyer::classify(std) method is used::vector<int>::iterator immage), which takes as input an iterator of the vector of the input image, represented as a one-dimensional array, the length of which is equal to the size of the input layer of the neural network (by analogy with the dataset format), and returns the class number assigned to it by the neural network.


# Project launch
If you are working with Visual Studio, clone this repository to launch the project, set the Release x86 configuration type and build, after the first build, messages about the absence of the necessary DLL files will be displayed, copy the contents of the Letter_classifier\Letter_classifier\DLL-files folder to Letter_classifier\Release and build again - the project should start. The SFML Graphics library, which is used in the project for handwriting characters, is included in the project, and it does not need to be connected.

The user is invited to create a dataset on his own, to do this, in pop-up windows with a size of 300 X 300, you need to draw one letter with the mouse, holding the LMB. When the letter is drawn, you need to close the pop-up window, the window for the next letter will open itself. There are only 5 letter classes, it is recommended to draw at least 10 letters for each class. An example of a drawn letter in a pop-up eye is shown in the figure below.

<img src="https://user-images.githubusercontent.com/71639489/213845029-130fd1a7-5e45-417d-a472-b2c72cd772fb.jpg" width="200" height="200" /> 


After the training sample is loaded, the images of the letters are compressed to a size of 50 x 50, and the image of the entire training sample will be displayed in one window as shown below.

![Screenshot 20-01-2023 220533](https://user-images.githubusercontent.com/71639489/213845135-fb501502-17f0-45cb-a42a-ac1ee3eb8cc7.jpg)

You will be asked to save the date set in memory in case next time you want to save time on creating it. Then the neural network will be trained by the method of back propagation of the error. After that, you will also be asked to draw a few test examples for each letter with your mouse. After loading the test sample, it will be passed through a trained neural network and you will see an assessment of the accuracy of the classification of your test letters.
# Support
We all need support and motivation. TryShape is not an exception. Please give this project a ⭐️ to encourage and show that you liked it. Don't forget to leave a star ⭐️ before you move away.
