#include <iostream>

using namespace std;

template <typename T>
T PolyEval(T coeff[], int n, const T &x) {
    T y = 1, value = coeff[0];

    for (int i = 0; i != n; ++i) {
        y *= x;
        value += y * coeff[i];
    }

    return value;
}

int main() {
    cout << "Hello World!" << endl;
    return 0;
}
