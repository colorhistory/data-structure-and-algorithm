#ifndef INSERTIONSORT_HPP
#define INSERTIONSORT_HPP

#include "bits/stdc++.h"

namespace DSAA {

    class Insertion {
      public:
        void sort(double*& arr, int N);
    };

    void Insertion::sort(double*& arr, int N) {
        for (int i = 1; i != N; ++i) {
            for (int j = i; j != 0; --j) {
                if (arr[j] < arr[j - 1]) {
                    std::swap(arr[j], arr[j - 1]);
                }
            }
        }
    }

}  // namespace DSAA
#endif  // INSERTIONSORT_HPP
