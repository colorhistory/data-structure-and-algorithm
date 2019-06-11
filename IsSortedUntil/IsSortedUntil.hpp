#ifndef ISSORTEDUNTIL_HPP
#define ISSORTEDUNTIL_HPP

#include "bits/stdc++.h"

namespace DSAA {

    template <typename ForwardIterator, typename Compare>
    ForwardIterator IsSortUntil(ForwardIterator first, ForwardIterator last, Compare comp) {
        if (first != last) {
            ForwardIterator currentIter = first;

            while (++currentIter != last) {
                if (comp(*currentIter, *first)) {
                    return currentIter;
                }

                first = currentIter;
            }
        }

        return last;
    }

    template <typename ForwardIterator>
    ForwardIterator IsSortUntil(ForwardIterator first, ForwardIterator last) {
        IsSortUntil(first, last, std::less<typename std::iterator_traits<ForwardIterator>::value_type>());
    }

}  // namespace DSAA
#endif  // ISSORTEDUNTIL_HPP
