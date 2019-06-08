#ifndef DIAGONALMATRIX_HPP
#define DIAGONALMATRIX_HPP

#include "bits/stdc++.h"

#include "Exception.hpp"
#include "changeLength1D.hpp"

namespace DSAA {

    template <typename T>
    class DiagonalMatrix {
      public:
        DiagonalMatrix(int initialSize = 10);
        ~DiagonalMatrix();

        // ADT
        T get(int i, int j) const;
        void set(int i, int j, const T &theElement);

      private:
        int n;
        T *element;
    };

    /*!
     * \brief DiagonalMatrix<T>::DiagonalMatrix
     * \param initialSize
     */
    template <typename T>
    DiagonalMatrix<T>::DiagonalMatrix(int initialSize) {
        if (initialSize < 1) {
            throw IllegalParameterValue("Matrix size must be > 0");
        }
        this->n = initialSize;
        element = new T[n];
    }

    /*!
     * \brief DiagonalMatrix<T>::~DiagonalMatrix
     */
    template <typename T>
    DiagonalMatrix<T>::~DiagonalMatrix() {
        delete[] element;
    }

    /*!
     * \brief DiagonalMatrix<T>::get
     * \param i
     * \param j
     * \return
     */
    template <typename T>
    T DiagonalMatrix<T>::get(int i, int j) const {
        if (i < 1 || j < 1 || i > n || j > n) {
            throw MatrixIndexOutOfBounds();
        }
        if (i == j) {
            return element[i - 1];
        }
        return T{};
    }

    /*!
     * \brief DiagonalMatrix<T>::set
     * \param i
     * \param j
     * \param theElement
     */
    template <typename T>
    void DiagonalMatrix<T>::set(int i, int j, const T &theElement) {
        if (i < 1 || j < 1 || i > n || j > n) {
            throw MatrixIndexOutOfBounds();
        }
        if (i == j) {
            element[i - 1] = theElement;
        } else {
            if (theElement != 0) {
                throw IllegalParameterValue("nondiagonal elements must be zero");
            }
        }
    }

}  // namespace DSAA

#endif  // DIAGONALMATRIX_HPP
