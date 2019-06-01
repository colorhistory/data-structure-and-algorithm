#ifndef FOR_EACH_HPP
#define FOR_EACH_HPP

namespace DSAA {

    /*!
     * \brief for_each
     * \param first
     * \param last
     * \param f
     * \return
     */
    template <typename InputIterator, typename Function>
    inline Function for_each(InputIterator first, InputIterator last, Function f) {
        for (; first != last; ++first) {
            f(*first);
        }

        return f;
    }

}  // namespace DSAA

#endif  // FOR_EACH_HPP
