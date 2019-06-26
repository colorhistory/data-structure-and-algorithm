#ifndef INSERTSORT_HPP
#define INSERTSORT_HPP

#include "bits/stdc++.h"

namespace DSAA {

    template <typename Iterator,
              typename CompareType = std::less<typename std::iterator_traits<Iterator>::value_type>>
    void InsertSort(const Iterator first, const Iterator last, CompareType compare = CompareType()) {
        auto size = std::distance(first, last);
        if (size <= 1) {
            return;
        }

        Iterator currentIter = first;
        while (++currentIter != last) {
            auto smallNext = currentIter;
            while (smallNext != first && compare(*currentIter, *(smallNext - 1))) {
                smallNext--;
            }

            auto key = *currentIter;
            auto iter = currentIter;
            while (iter != smallNext) {
                *iter = *(iter - 1);
                --iter;
            }
            *(iter) = key;
        }
    }

}  // namespace DSAA
#endif  // INSERTSORT_HPP
