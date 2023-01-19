#include "data_load.h"
#include"classifier.h"

using namespace sf;

int main()
{
    srand(time(NULL));
    classifier cl(4, { 5, 100, 1000, 2500 }, 0.1);

    dataset DATA = load_dataset();
    //for (int i = 0; i < DATA.size_for_one_letter * 5 * 50 * 50; i++)
    //    std::cout << DATA.data[i];

    //загрузка обучающей выборки в нейросеть
    cl.selection_load(DATA);

    std::vector<int> im(2500, 0);
    for (int i = 0; i < 2500; i++)
        im[i] = DATA.data[i];
    cl.loop(im.begin());
    return 0;
}

