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

#include "BinarySearchTree.hpp"

using namespace DSAA;

int main(int /* argc */, char** /* argv */) {
    BinarySearchTree<int> t;
    int NUMS = 400000;
    const int GAP = 3711;
    int i;

    std::cout << "Checking... (no more output means success)" << std::endl;

    for (i = GAP; i != 0; i = (i + GAP) % NUMS) {
        t.insert(i);
    }

    t.printTree();

    for (i = 1; i < NUMS; i += 2) {
        t.remove(i);
    }

    if (NUMS < 40) {
        t.printTree();
    }
    if (t.findMin() != 2 || t.findMax() != NUMS - 2) {
        std::cout << "FindMin or FindMax error!" << std::endl;
    }

    for (i = 2; i < NUMS; i += 2) {
        if (!t.contains(i)) {
            std::cout << "Find error1!" << std::endl;
        }
    }

    for (i = 1; i < NUMS; i += 2) {
        if (t.contains(i)) {
            std::cout << "Find error2!" << std::endl;
        }
    }

    BinarySearchTree<int> t2;
    t2 = t;

    for (i = 2; i < NUMS; i += 2)
        if (!t2.contains(i))
            std::cout << "Find error1!" << std::endl;

    for (i = 1; i < NUMS; i += 2) {
        if (t2.contains(i)) {
            std::cout << "Find error2!" << std::endl;
        }
    }

    std::cout << "Finished testing" << std::endl;

    return 0;
}
