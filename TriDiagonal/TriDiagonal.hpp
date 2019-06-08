#ifndef TRIDIAGONAL_HPP
#define TRIDIAGONAL_HPP

#include "Exception.hpp"

namespace DSAA {

    template <typename T>
    class TriDiagonal {
      public:
        TriDiagonal(int theN = 10);
        ~TriDiagonal();

        // ADT
        T get(int i, int j) const;
        void set(int i, int j, const T& theElement);

      private:
        int n;
        T* elements;
    };

    /*!
     * \brief TriDiagonal<T>::TriDiagonal
     * \param theN
     */
    template <typename T>
    TriDiagonal<T>::TriDiagonal(int theN) {
        if (theN < 1) {
            throw IllegalParameterValue("Matrix size must be > 0");
        }

        this->n = theN;
        elements = new T[3 * n + 2];
    }

    /*!
     * \brief TriDiagonal<T>::~TriDiagonal
     */
    template <typename T>
    TriDiagonal<T>::~TriDiagonal() {
        delete[] elements;
    }

    /*!
     * \brief TriDiagonal<T>::get
     * \param i
     * \param j
     * \return
     */
    template <typename T>
    T TriDiagonal<T>::get(int i, int j) const {
        if (i < 1 || j < 1 || i > n || j > n) {
            throw MatrixIndexOutOfBounds();
        }

        switch (i - j) {
            case 0: {
                return elements[3 * (i - 1) - 2 + 2];
                break;
            }
            case -1: {
                return elements[3 * (i - 1) - 2 + 1];
                break;
            }
            case 1: {
                return elements[3 * (i - 1) - 2 + 3];
                break;
            }
            default: {
                return T{};
                break;
            }
        }
    }

    /*!
     * \brief TriDiagonal<T>::set
     * \param i
     * \param j
     * \param theElement
     */
    template <typename T>
    void TriDiagonal<T>::set(int i, int j, const T& theElement) {
        if (i < 1 || j < 1 || i > n || j > n) {
            throw MatrixIndexOutOfBounds();
        }
        switch (i - j) {
            case 0: {
                elements[3 * (i - 1) - 2 + 2] = theElement;
                break;
            }
            case -1: {
                elements[3 * (i - 1) - 2 + 1] = theElement;
                break;
            }
            case 1: {
                elements[3 * (i - 1) - 2 + 3] = theElement;
                break;
            }
            default: {
                if (theElement != T{}) {
                    throw IllegalParameterValue("non-tridiagonal elements must be > 0");
                }
            }
        }
    }

}  // namespace DSAA
#endif  // TRIDIAGONAL_HPP
