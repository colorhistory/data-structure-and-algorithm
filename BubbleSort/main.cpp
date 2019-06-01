#include <algorithm>
#include <iostream>

using namespace std;

template <typename T>
void Bubble(T a[], int n) {
    for (int i = 0; i != n - 1; ++i) {
        if (a[i] > a[i + 1]) {
            swap(a[i], a[i + 1]);
        }
    }
}

template <typename T>
void BubbleSort(T a[], int n) {
    for (int i = n; i > 1; --i) {
        Bubble(a, i);
    }
}

int main() {
    cout << "Hello World!" << endl;
    return 0;
}
