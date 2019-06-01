#ifndef NONE_OF_HPP
#define NONE_OF_HPP

namespace DSAA {

    /*!
     * \brief none_of
     * \param first
     * \param last
     * \param pred
     * \return
     */
    template <typename InputIterator, typename Predicate>
    inline bool none_of(InputIterator first, InputIterator last, Predicate pred) {
        for (; first != last; ++first) {
            if (pred(*first)) {
                return false;
            }
        }
        return true;
    }

}  // namespace DSAA

#endif  // NONE_OF_HPP
