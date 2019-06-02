#ifndef ADJACENT_FIND_H
#define ADJACENT_FIND_H

namespace DSAA {

    /*!
     * \brief adjacent_find
     * \param first
     * \param last
     * \param pred
     * \return
     */
    template <class ForwardIterator, typename BinaryPredicate>
    inline ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last, BinaryPredicate pred) {
        if (first != last) {
            ForwardIterator i = first;
            while (++i != last) {
                if (pred(*first, *i)) {
                    return first;
                }
                first = i;
            }
        }
        return last;
    }
}  // namespace DSAA

#endif  // ADJACENT_FIND_H
