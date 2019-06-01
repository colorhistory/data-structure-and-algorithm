#ifndef FOR_EACH_N_HPP
#define FOR_EACH_N_HPP

namespace DSAA {

    /*!
     * \brief for_each_n
     * \param first
     * \param n
     * \param f
     * \return
     */
    template <typename InputIterator, typename Size, typename Function>
    inline InputIterator for_each_n(InputIterator first, Size n, Function f) {
        n = static_cast<int>(n);

        while (n > 0) {
            f(*first);
            ++first;
            --n;
        }

        return first;
    }
}  // namespace DSAA

#endif  // FOR_EACH_N_HPP
