#ifndef __LESS_HPP
#define __LESS_HPP

namespace DSAA {

    template <typename T1, typename T2 = T1>
    struct __less {
        /*!
         * \brief operator ()
         * \param x
         * \param y
         * \return
         */
        bool operator()(const T1& x, const T1& y) const {
            return x < y;
        }

        /*!
         * \brief operator ()
         * \param x
         * \param y
         * \return
         */
        bool operator()(const T1& x, const T2& y) const {
            return x < y;
        }

        /*!
         * \brief operator ()
         * \param x
         * \param y
         * \return
         */
        bool operator()(const T2& x, const T1& y) const {
            return x < y;
        }

        /*!
         * \brief operator ()
         * \param x
         * \param y
         * \return
         */
        bool operator()(const T2& x, const T2& y) const {
            return x < y;
        }
    };

    template <typename T1>
    struct __less<T1, T1> {
        /*!
         * \brief operator ()
         * \param x
         * \param y
         * \return
         */
        bool operator()(const T1& x, const T1& y) const {
            return x < y;
        }
    };

    template <typename T1>
    struct __less<const T1, T1> {
        /*!
         * \brief operator ()
         * \param x
         * \param y
         * \return
         */
        bool operator()(const T1& x, const T1& y) const {
            return x < y;
        }
    };

    template <typename T1>
    struct __less<T1, const T1> {
        /*!
         * \brief operator ()
         * \param x
         * \param y
         * \return
         */
        bool operator()(const T1& x, const T1& y) const {
            return x < y;
        }
    };

}  // namespace DSAA

#endif  // __LESS_HPP
