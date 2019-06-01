#include <iostream>

using namespace std;

template <typename T>
void Add(T** a, T** b, T** c, int rows, int cols) {
    for (int i = 0; i != rows; ++i) {
        for (int j = 0; j != cols; ++j) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}

int main() {
    cout << "Hello World!" << endl;
    return 0;
}
