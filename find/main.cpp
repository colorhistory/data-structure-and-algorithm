#include "bits/stdc++.h"

#include "find.hpp"

int main() {
    std::vector<int> vec{1, 2, 4, 5, 7, 3, 9, 0};
    std::cout << ALGO::find(vec.begin(), vec.end(), 9) - vec.begin() << std::endl;

    return 0;
}
