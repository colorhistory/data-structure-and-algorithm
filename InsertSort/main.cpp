/**
 ** This file is part of the data-structure-and-algorithm project.
 ** Copyright 2019 xiaohaijin <xiaohaidotpro@outlook.com>.
 **
 **/

#include "bits/stdc++.h"

#include "InsertSort.hpp"

int main(int /* argc */, char** /* argv */) {
    std::vector<int> intVec{1, 4, 2, 87, 3, 2, 9, 5, 7, 10, 23};
    DSAA::InsertSort(intVec.begin(), intVec.end());

    for (auto& i : intVec) {
        std::cout << i << std::endl;
    }

    return 0;
}
