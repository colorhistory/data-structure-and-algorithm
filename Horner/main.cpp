#include <iostream>

using namespace std;

template <typename T>
T Horner(T coeff[], int n, const T &x) {
    T value = coeff[n];

    for (int i = 0; i != n; ++i) {
        value = value * x + coeff[n - i];
    }

    return value;
}

int main() {
    cout << "Hello World!" << endl;
    return 0;
}
