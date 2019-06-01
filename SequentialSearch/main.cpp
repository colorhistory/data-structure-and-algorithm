#include <iostream>

using namespace std;

template <typename T>
int SequenceSearch(T a[], const T& x, int n) {
    int i;
    for (int i = 0; i != n && a[i] != x; ++i) {
        if (i == n) {
            return -1;
        }
    }
    return i;
}

int main() {
    return 0;
}
