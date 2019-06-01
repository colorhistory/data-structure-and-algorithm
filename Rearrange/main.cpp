#include <iostream>

using namespace std;

template <typename T>
void Rearrange(T a[], int n, int r[]) {
    T *u = new T[n + 1];

    // move elements
    for (int i = 1; i != n; ++i) {
        u[r[i]] = a[i];
    }

    for (int i = 1; i != n; ++i) {
        a[i] = u[i];
    }

    delete[] u;
}

int main() {
    cout << "Hello World!" << endl;
    return 0;
}
