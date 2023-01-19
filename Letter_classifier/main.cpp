#include "data_load.h"
#include"classifier.h"

using namespace sf;

int main()
{
    srand(time(NULL));
    classifier cl(4, { 5, 50, 500, 2500 }, 0.07, 0.1);

    dataset DATA = load_dataset();

    cl.selection_load(DATA);

    //cl.train_loop(1);

    cl.learn();

    cl.test(20);

    

    return 0;
}

