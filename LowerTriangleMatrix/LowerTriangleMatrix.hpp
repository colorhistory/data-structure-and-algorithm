#ifndef LOWERTRIANGLEMATRIX_HPP
#define LOWERTRIANGLEMATRIX_HPP

#include "Exception.hpp"

namespace DSAA {

    template <typename T>
    class LowerTriangleMatrix {
      public:
        LowerTriangleMatrix(int theN = 10);
        ~LowerTriangleMatrix();

        // ADT
        T get(int i, int j) const;
        void set(int i, int j, const T& theElement);

      private:
        int n;
        T* elements;
    };

    /*!
     * \brief LowerTriangleMatrix<T>::LowerTriangleMatrix
     * \param theN
     */
    template <typename T>
    LowerTriangleMatrix<T>::LowerTriangleMatrix(int theN) {
        if (theN < 1) {
            throw IllegalParameterValue();
        }

        n = theN;
        elements = new T[n * (n + 1) / 2];
    }

    /*!
     * \brief LowerTriangleMatrix<T>::~LowerTriangleMatrix
     */
    template <typename T>
    LowerTriangleMatrix<T>::~LowerTriangleMatrix() {
        delete[] elements;
    }

    /*!
     * \brief LowerTriangleMatrix<T>::get
     * \param i
     * \param j
     * \return
     */
    template <typename T>
    T LowerTriangleMatrix<T>::get(int i, int j) const {
        if (i < 1 || j < 1 || i > n || j > n) {
            throw MatrixIndexOutOfBounds();
        }

        if (i >= j) {
            return elements[(i - 1) * (i) / 2 + (j - 1)];
        }
        return T{};
    }

    /*!
     * \brief LowerTriangleMatrix<T>::set
     * \param i
     * \param j
     * \param theElement
     */
    template <typename T>
    void LowerTriangleMatrix<T>::set(int i, int j, const T& theElement) {
        if (i < 1 || j < 1 || i > n || j > n) {
            throw IllegalParameterValue();
        }

        if (i >= j) {
            elements[(i - 1) * (i) / 2 + (j - 1)] = theElement;
        } else {
            throw IllegalParameterValue("elements not in lower triangle must be zero");
        }
    }

}  // namespace DSAA

#endif  // LOWERTRIANGLEMATRIX_HPP
