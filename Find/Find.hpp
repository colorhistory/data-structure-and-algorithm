#ifndef FIND_HPP
#define FIND_HPP

namespace DSAA {

    /*!
     * \brief find
     * \param first
     * \param last
     * \param value
     * \return
     */
    template <typename InputIterator, typename Tp>
    inline InputIterator find(InputIterator first, InputIterator last, const Tp& value) {
        for (; first != last; ++first) {
            if (*first == value) {
                break;
            }
        }
        return first;
    }

}  // namespace DSAA
#endif  // FIND_HPP
