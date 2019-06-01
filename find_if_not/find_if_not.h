#ifndef FIND_IF_NOT_H
#define FIND_IF_NOT_H

namespace ALGO {

    template <typename InputIterator, typename UnaryPredicate>
    InputIterator find_if_not(InputIterator first, InputIterator last, UnaryPredicate p) {
        for (; first != last; ++first) {
            if (!p(*first)) {
                return first;
            }
        }
        return last;
    }

}  // namespace ALGO
#endif  // FIND_IF_NOT_H
