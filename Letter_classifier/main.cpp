#include "data_load.h"
#include"classifier.h"

using namespace sf;

int main()
{
    srand(time(NULL));
    classifier cl(4, { 5, 100, 1000, 2500 }, 10000000.9);

    dataset DATA = load_dataset();
    //for (int i = 0; i < DATA.size_for_one_letter * 5 * 50 * 50; i++)
    //    std::cout << DATA.data[i];

    cl.selection_load(DATA);

    cl.train_loop(20);
    return 0;
}

