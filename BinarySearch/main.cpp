#include <iostream>

using namespace std;

template <typename T>
int BinarySearch(T a[], const T &x, int n) {
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        int middle = (left + right) / 2;
        if (x == a[middle]) {
            return middle;
        }
        if (x > a[middle]) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }
}

int main() {
    cout << "Hello World!" << endl;
    return 0;
}
