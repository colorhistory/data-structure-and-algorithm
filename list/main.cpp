#include <iostream>

#include "list.hpp"

using namespace std;

int main() {
    XIAOHAI::list<double> li;
    for (int i = 0; i != 30; ++i) {
        li.push_back(i);
    }

    return 0;
}
