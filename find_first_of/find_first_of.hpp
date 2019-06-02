#ifndef FIND_FIRST_OF_HPP
#define FIND_FIRST_OF_HPP

#include <iterator>
#include <type_traits>

#include "../__equal_to/__equal_to.hpp"

namespace DSAA {

    /*!
     * \brief __find_first_of_ce
     * \param first1
     * \param last1
     * \param first2
     * \param last2
     * \param pred
     * \return
     */
    template <class ForwardIterator1, class ForwardIterator2, typename BinaryPredicate>
    ForwardIterator1 __find_first_of_ce(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2,
                                        ForwardIterator2 last2, BinaryPredicate pred) {
        for (; first1 != last1; ++first1) {
            for (ForwardIterator2 j = first2; j != last2; ++j) {
                if (pred(*first1, *j)) {
                    return first1;
                }
            }
        }
        return last1;
    }

    /*!
     * \brief find_first_of
     * \param first1
     * \param last1
     * \param first2
     * \param last2
     * \param pred
     * \return
     */
    template <typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
    inline ForwardIterator1 find_first_of(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2,
                                          ForwardIterator2 last2, BinaryPredicate pred) {
        return __find_first_of_ce(first1, last1, first2, last2, pred);
    }

    /*!
     * \brief find_first_of
     * \param first1
     * \param last1
     * \param first2
     * \param last2
     * \return
     */
    template <typename ForwardIterator1, typename ForwardIterator2>
    inline ForwardIterator1 find_first_of(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2,
                                          ForwardIterator2 last2) {
        using v1 = typename std::iterator_traits<ForwardIterator1>::value_type;
        using v2 = typename std::iterator_traits<ForwardIterator2>::value_type;
        return __find_first_of_ce(first1, last1, first2, last2, __equal_to<v1, v2>());
    }

}  // namespace DSAA

#endif  // FIND_FIRST_OF_HPP
