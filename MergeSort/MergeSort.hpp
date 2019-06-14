#ifndef MERGESORT_HPP
#define MERGESORT_HPP

#include "bits/stdc++.h"

template <typename ForwardIterator,
          typename Compare = std::less<typename std::iterator_traits<ForwardIterator>::value_type>>
void merge(const ForwardIterator begin, const ForwardIterator end, const ForwardIterator middle,
           Compare comp = Compare());

template <typename ForwardIterator,
          typename Compare = std::less<typename std::iterator_traits<ForwardIterator>::value_type>>
void MergeSort(const ForwardIterator begin, const ForwardIterator end, Compare comp = Compare()) {
    if (std::distance(begin, end) <= 1) {
        return;
    }

    ForwardIterator middle = begin + (end - begin) / 2;

    MergeSort(begin, middle);
    MergeSort(middle, end);
    merge(begin, end, middle, comp);
}

template <typename ForwardIterator, typename Compare>
void merge(const ForwardIterator begin, const ForwardIterator end, const ForwardIterator middle, Compare comp) {
    if (std::distance(begin, middle) <= 0 || std::distance(middle, end) <= 0) {
        return;
    }

    using T = typename std::iterator_traits<ForwardIterator>::value_type;
    std::vector<T> result(begin, end);

    auto current = result.begin();
    auto leftCurrent = begin;
    auto rightCurrent = middle;

    while (leftCurrent != middle && rightCurrent != end) {
        if (comp(*leftCurrent, *rightCurrent)) {
            *current++ = *leftCurrent++;
        } else {
            *current++ = *rightCurrent++;
        }
    }

    if (leftCurrent == middle && rightCurrent != end) {
        std::copy(rightCurrent, end, current);
    }
    if (leftCurrent != middle && rightCurrent == end) {
        std::copy(leftCurrent, middle, current);
    }

    std::copy(result.begin(), result.end(), begin);
}

#endif  // MERGESORT_HPP
