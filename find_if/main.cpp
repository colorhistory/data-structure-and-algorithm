#include "bits/stdc++.h"

#include "find_if.hpp"

bool greaterFive(int value) {
    if (value > 5) {
        return true;
    }
    return false;
}

int main() {
    std::vector<int> vec{5, 2, 6, 9, 10, 3};
    std::cout << ALGO::find_if(vec.cbegin(), vec.cend(), greaterFive) - vec.begin() << std::endl;

    return 0;
}
