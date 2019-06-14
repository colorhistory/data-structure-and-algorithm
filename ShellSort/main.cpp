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

#include "ShellSort.h"

int main(int /* argc */, char** /* argv */) {
    std::string str{"SHELLSORTEXAMPLE"};
    char* charValue = new char[16];
    for (std::string::size_type i = 0; i != 16; ++i) {
        charValue[i] = str.at(i);
    }

    for (std::string::size_type i = 0; i != 16; ++i) {
        std::cout << charValue[i] << "  ";
    }
    std::cout << std::endl;

    DSAA::ShellSort shell;
    shell.sort(charValue, 16);

    for (std::string::size_type i = 0; i != 16; ++i) {
        std::cout << charValue[i] << "  ";
    }
    std::cout << std::endl;

    return 0;
}
