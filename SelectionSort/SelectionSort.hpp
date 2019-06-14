#ifndef SELECTIONSORT_HPP
#define SELECTIONSORT_HPP

#include "bits/stdc++.h"

namespace DSAA {

    class SelectionSort {
      public:
        void sort(double*& arr, unsigned int N) const;
    };

    void SelectionSort::sort(double*& arr, unsigned int N) const {
        for (unsigned int i = 0; i != N; ++i) {
            unsigned int min = i;

            for (unsigned int j = i + 1; j != N; ++j) {
                if (arr[j] < arr[min]) {
                    min = j;
                }
            }

            std::swap(arr[i], arr[min]);
        }
    }
}  // namespace DSAA
#endif  // SELECTIONSORT_HPP
