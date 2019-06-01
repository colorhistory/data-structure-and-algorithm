#ifndef FIND_IF_NOT_H
#define FIND_IF_NOT_H

namespace DSAA {

    /*!
     * \brief find_if_not
     * \param first
     * \param last
     * \param pred
     * \return
     */
    template <typename InputIterator, typename Predicate>
    inline bool find_if_not(InputIterator first, InputIterator last, Predicate pred) {
        for (; first != last; ++first) {
            if (!pred(*first)) {
                break;
            }
        }

        return first;
    }

}  // namespace DSAA

#endif  // FIND_IF_NOT_H
