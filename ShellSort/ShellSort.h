#ifndef SHELLSORT_H
#define SHELLSORT_H

#include "bits/stdc++.h"

namespace DSAA {

    class ShellSort {
      public:
        void sort(char *&arr, int N);
    };

    void ShellSort::sort(char *&arr, int N) {
        int h = N / 2 * 2;

        while (h >= 1) {
            for (int i = h; i != N; ++i) {
                for (int j = i; j >= h && (arr[j] < arr[j - h]); j -= h) {
                    std::swap(arr[j], arr[j - h]);
                }
            }
            h = h / 2;
        }

        //        while (h >= 1) {
        //            for (int i = h; i != N; ++i) {
        //                for (int j = i; j >= h && (arr[j] < arr[j - h]); j -= h) {
        //                    std::swap(arr[j], arr[j - h]);

        //                    // print the array
        //                    std::cout << "h : " << h << std::endl;
        //                    for (int iBin = 0; iBin != N; ++iBin) {
        //                        std::cout << std::setw(3) << "[" << std::setw(2);
        //                        if (iBin == j) {
        //                            std::cout << "\033[32m" << iBin << "\033[0m";
        //                        } else {
        //                            std::cout << iBin;
        //                        }
        //                        std::cout << std::setw(1) << "]";
        //                    }
        //                    std::cout << std::endl;
        //                    for (int iBin = 0; iBin != N; ++iBin) {
        //                        std::cout << std::setw(6) << arr[iBin];
        //                    }
        //                    std::cout << std::endl << std::endl;
        //                    // print the array
        //                }
        //            }
        //            h = h / 2;
        //        }
    }

}  // namespace DSAA

#endif  // SHELLSORT_H
