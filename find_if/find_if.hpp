#ifndef FIND_IF_HPP
#define FIND_IF_HPP

namespace ALGO {

    template <typename InputIterator, typename UnaryPredicate>
    InputIterator find_if(InputIterator first, InputIterator last, UnaryPredicate p) {
        for (; first != last; ++first) {
            if (p(*first)) {
                return first;
            }
        }
        return last;
    }

}  // namespace ALGO

#endif  // FIND_IF_HPP
