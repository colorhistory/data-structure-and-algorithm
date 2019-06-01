#ifndef ALL_OF_HPP
#define ALL_OF_HPP

namespace DSAA {

    /*!
     * \brief all_of
     * \param first
     * \param last
     * \param pred
     * \return
     */
    template <typename InputIterator, typename Predicate>
    inline bool all_of(InputIterator first, InputIterator last, Predicate pred) {
        for (; first != last; ++first) {
            if (!pred(*first)) {
                return false;
            }
        }
        return true;
    }
}  // namespace DSAA

#endif  // ALL_OF_HPP
