#include <iostream>

using namespace std;

template <typename T>
void Rank(T a[], int n, int r[]) {
    for (int i = 1; i != n; ++i) {
        r[i] = 0;
    }

    for (int i = 1; i != n; ++i) {
        for (int j = 1; j != i; ++j) {
            if (a[j] <= a[i]) {
                ++r[i];
            } else {
                // there is some problem.
                ++r[j];
            }
        }
    }
}

int main() {
    cout << "Hello World!" << endl;
    return 0;
}
