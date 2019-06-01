#ifndef FIND_HPP
#define FIND_HPP

namespace ALGO {

    /*!
     * \brief find
     * \param first
     * \param last
     * \param value
     * \return
     */
    template <typename InputIterator, typename T>
    InputIterator find(InputIterator first, InputIterator last, const T& value) {
        for (; first != last; ++first) {
            if (*first == value) {
                return first;
            }
        }
        return last;
    }
}  // namespace ALGO

#endif  // FIND_HPP
