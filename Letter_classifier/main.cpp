#include "data_load.h"
#include"classifier.h"

using namespace sf;

int main()
{
    srand(time(NULL));
    classifier cl(4, { 5, 50, 500, 2500 }, 1.5, 1.0, 4);

    dataset DATA = load_dataset();

    cl.selection_load(DATA);

    //cl.train_loop(31);
    
    cl.learn();

    cl.accuracy_test_on_dataset();
    
    return 0;
}

