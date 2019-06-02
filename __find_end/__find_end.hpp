#ifndef __FIND_END_HPP
#define __FIND_END_HPP

#include <iterator>
#include <type_traits>

#include "../__equal_to/__equal_to.hpp"

namespace DSAA {

    /*!
     * \brief __find_end
     * \param first1
     * \param last1
     * \param first2
     * \param last2
     * \param pred
     * \return
     */
    template <typename BinaryPredicate, typename ForwardIterator1, typename ForwardIterator2>
    ForwardIterator1 __find_end(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2,
                                ForwardIterator2 last2, BinaryPredicate pred, std::forward_iterator_tag,
                                std::forward_iterator_tag) {
        /*! last1 is the default answer */
        ForwardIterator1 r = last1;

        /*! the pattern is empty */
        if (first2 == last2) {
            return r;
        }

        while (true) {
            while (true) {
                /*! if source exhausted return last correct answer or last1 if never found */
                if (first1 == last1) {
                    return r;
                }
                /*! the pred is true */
                if (pred(*first1, *first2)) {
                    break;
                }
                ++first1;
            }

            /*! first1 matches first2, now match elements after here */
            ForwardIterator1 m1 = first1;
            ForwardIterator2 m2 = first2;

            while (true) {
                /*! Pattern exhausted, record answer and search for another one */
                if (++m2 == last2) {
                    r = first1;
                    ++first1;
                    break;
                }
                /*! source exhausted, return last answer */
                if (++m1 == last1) {
                    return r;
                }
                /*! mismatch, restart with a new first */
                if (!pred(*m1, *m2)) {
                    ++first1;
                    break;
                }
                // else there is a match, check next element
            }
        }
    }

    /*!
     * \brief __find_end
     * \param first1
     * \param last1
     * \param first2
     * \param last2
     * \param pred
     * \return
     */
    template <typename BinaryPrdicate, typename BidrectionalIterator1, typename BidrectionalIterator2>
    BidrectionalIterator1 __find_end(BidrectionalIterator1 first1, BidrectionalIterator1 last1,
                                     BidrectionalIterator2 first2, BidrectionalIterator2 last2,
                                     BinaryPrdicate pred, std::bidirectional_iterator_tag,
                                     std::bidirectional_iterator_tag) {
        /*! modeled after search algorithm (in reverse) */
        if (first2 == last2) {
            return last1;
        }

        BidrectionalIterator1 l1 = last1;
        BidrectionalIterator2 l2 = last2;
        --l2;

        while (true) {
            /*! find last element in sequence 1 that match *(last2-1), with a minimum of loop checks */
            while (true) {
                /*! return last1 if no element matches *first2 */
                if (first1 == l1) {
                    return last1;
                }
                if (pred(*--l1, *l2)) {
                    break;
                }
            }

            /*! l1 matches *l2, now match elements before here */
            BidrectionalIterator1 m1 = l1;
            BidrectionalIterator2 m2 = l2;

            while (true) {
                /*! if pattern exhausted, m1 is the anwser (works for 1 element pattern) */
                if (m2 == first2) {
                    return m1;
                }
                /*! otherwise if source exhausted, pattern not found */
                if (m1 == first1) {
                    return last1;
                }
                /*! if there is a mismatch, restart with a new l1 */
                if (!pred(*--m1, *--m2)) {
                    break;
                }
                /*! else there is a match, check next element */
            }
        }
    }

    template <typename BinaryPredicate, typename RandomAccessIterator1, typename RandomAccessIterator2>
    RandomAccessIterator1 __find_end(RandomAccessIterator1 first1, RandomAccessIterator1 last1,
                                     RandomAccessIterator2 first2, RandomAccessIterator2 last2,
                                     BinaryPredicate pred, std::random_access_iterator_tag,
                                     std::random_access_iterator_tag) {
        /*!
         * take advantage of knowing source and pattern lengths,
         * stop short when source is smaller thatn pattern
         */
        typename std::iterator_traits<RandomAccessIterator2>::difference_type len2 = last2 - first2;
        if (len2 == 0) {
            return last1;
        }
        typename std::iterator_traits<RandomAccessIterator1>::difference_type len1 = last1 - first1;
        if (len1 < len2) {
            return last1;
        }

        /*! end of pattern match can't go before here */
        const RandomAccessIterator1 s = first1 + (len2 - 1);
        RandomAccessIterator1 l1 = last1;
        RandomAccessIterator2 l2 = last2;
        --l2;

        while (true) {
            while (true) {
                if (s == l1) {
                    return last1;
                }
                if (pred(*--l1, *l2)) {
                    break;
                }

                RandomAccessIterator1 m1 = l1;
                RandomAccessIterator2 m2 = l2;

                while (true) {
                    if (m2 == first2) {
                        return m1;
                    }

                    /*! no need to check range on m1 because s guarantees we have enough source */
                    if (!pred(*--m1, *--m2)) {
                        break;
                    }
                }
            }
        }
    }

    /*!
     * \brief find_end
     * \param first1
     * \param last1
     * \param first2
     * \param last2
     * \param pred
     * \return
     */
    template <typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
    inline ForwardIterator1 find_end(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2,
                                     ForwardIterator2 last2, BinaryPredicate pred) {
        return __find_end<typename std::add_lvalue_reference<BinaryPredicate>::type>(
            first1, last1, first2, last2, pred,
            typename std::iterator_traits<ForwardIterator1>::iterator_category(),
            typename std::iterator_traits<ForwardIterator2>::iterator_category());
    }

    /*!
     * \brief find_end
     * \param first1
     * \param last1
     * \param first2
     * \param last2
     * \return
     */
    template <typename ForwardIterator1, typename ForwardIterator2>
    inline ForwardIterator1 find_end(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2,
                                     ForwardIterator2 last2) {
        typedef typename std::iterator_traits<ForwardIterator1>::value_type v1;
        using v2 = typename std::iterator_traits<ForwardIterator2>::value_type;

        return find_end(first1, last1, first2, last2, __equal_to<v1, v2>());
    }

}  // namespace DSAA
#endif  // __FIND_END_HPP
