#include "bits/stdc++.h"

#include "find_if_not.h"

bool greaterFive(int value) {
    if (value > 5) {
        return true;
    }
    return false;
}

int main() {
    std::vector<int> vec{7, 8, 6, 9, 10, 3};
    std::cout << ALGO::find_if_not(vec.cbegin(), vec.cend(), greaterFive) - vec.begin() << std::endl;

    return 0;
}
