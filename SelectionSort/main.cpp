/****************************************************************************
**
** Copyright (C) 2019 Xiaohai <xiaohaidotpro@outlook.com>.
** Contact: http://xiaohai.pro
**
** This file is part of data-structure-and-algorithm
**
**
****************************************************************************/

#include "bits/stdc++.h"

#include "SelectionSort.hpp"

int main(int /* argc */, char** /* argv */) {
    double* array = new double[5];
    array[0] = 90;
    array[1] = 10;
    array[2] = 7;
    array[3] = 60;
    array[4] = 4;

    for (int i = 0; i != 5; ++i) {
        std::cout << array[i] << "   ";
    }
    std::cout << std::endl;

    DSAA::SelectionSort selection;
    selection.sort(array, 5);

    for (int i = 0; i != 5; ++i) {
        std::cout << array[i] << "   ";
    }
    std::cout << std::endl;

    return 0;
}
