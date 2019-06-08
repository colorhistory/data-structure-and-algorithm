#ifndef MATRIXTERM_HPP
#define MATRIXTERM_HPP

namespace DSAA {

    template <typename T>
    struct MatrixTerm {
        int row;
        int col;
        T value = T{};

        operator T() const;
    };

    /*!
     * \brief MatrixTerm<T>::operator T
     */
    template <typename T>
    inline MatrixTerm<T>::operator T() const {
        return value;
    }

}  // namespace DSAA
#endif  // MATRIXTERM_HPP
