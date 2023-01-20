#include "data_load.h"
#include"classifier.h"
#include"testing.h"

using namespace sf;

int main()
{
    srand(time(NULL));

    classifier cl(4, { 5, 50, 500, 2500 }, 1.0, 1.0, 6);

    dataset LEARNING_DATA = load_dataset();

    cl.selection_load(LEARNING_DATA);
    cl.learn();
    cl.accuracy_test_on_dataset();

    test(cl);
    
    return 0;
}

