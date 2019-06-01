#ifndef FIND_IF_H
#define FIND_IF_H

namespace DSAA {

    /*!
     * \brief find_if
     * \param first
     * \param last
     * \param pred
     * \return
     */
    template <typename InputIterator, typename Predicate>
    inline InputIterator find_if(InputIterator first, InputIterator last, Predicate pred) {
        for (; first != last; ++first) {
            if (pred(*first)) {
                break;
            }
        }

        return first;
    }

}  // namespace DSAA

#endif  // FIND_IF_H
