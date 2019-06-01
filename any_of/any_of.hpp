#ifndef ANY_OF_HPP
#define ANY_OF_HPP

namespace DSAA {

    /*!
     * \brief any_of
     * \param first
     * \param last
     * \param pred
     * \return
     */
    template <typename InputIterator, typename Predicate>
    inline bool any_of(InputIterator first, InputIterator last, Predicate pred) {
        for (; first != last; ++first) {
            if (pred(*first)) {
                return true;
            }
        }

        return false;
    }

}  // namespace DSAA

#endif  // ANY_OF_HPP
