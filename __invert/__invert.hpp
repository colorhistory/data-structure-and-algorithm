#ifndef __INVERT_HPP
#define __INVERT_HPP

namespace DSAA {
    template <typename Predicate>
    class __invert {
      public:
        __invert();
        __invert(Predicate p);

        template <typename T1>
        bool operator()(const T1& x);

        template <typename T1, typename T2>
        bool operator()(const T1& x, const T2& y);

      private:
        Predicate p;
    };

    /*!
     * \brief __invert<Predicate>::__invert
     */
    template <typename Predicate>
    inline __invert<Predicate>::__invert() {
    }

    /*!
     * \brief __invert<Predicate>::__invert
     * \param p
     */
    template <typename Predicate>
    inline __invert<Predicate>::__invert(Predicate p) {
        this->p = p;
    }

    /*!
     * \brief __invert<Predicate>::operator ()
     * \param x
     * \return
     */
    template <typename Predicate>
    template <typename T1>
    inline bool __invert<Predicate>::operator()(const T1& x) {
        return !p(x);
    }

    /*!
     * \brief __invert<Predicate>::operator ()
     * \param x
     * \param y
     * \return
     */
    template <typename Predicate>
    template <typename T1, typename T2>
    inline bool __invert<Predicate>::operator()(const T1& x, const T2& y) {
        return p(y, x);
    }

}  // namespace DSAA

#endif  // __INVERT_HPP
