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

#include "MergeSort.hpp"

int main(int /* argc */, char** /* argv */) {
    std::vector<int> intVec{1, 3, 4, 9, 3, 2, 6, 3, 89, 2, 4, 6, 8};

    MergeSort(intVec.begin(), intVec.end());

    for (auto i : intVec) {
        std::cout << i << "   ";
    }
    std::cout << std::endl;

    //    auto bigger = [](int value1, int value2) { return value1 >= value2; };
    //    MergeSort(intVec.begin(), intVec.end(), bigger);

    //    for (auto i : intVec) {
    //        std::cout << i << "   ";
    //    }
    //    std::cout << std::endl;

    return 0;
}
