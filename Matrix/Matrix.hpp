#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "bits/stdc++.h"

#include "Exception.hpp"

namespace DSAA {

    template <typename T>
    class Matrix {
        template <typename U>
        friend std::ostream &operator<<(std::ostream &out, const Matrix<U> &matrix);

      public:
        Matrix(int theRows = 0, int theColumns = 0);
        Matrix(const Matrix &x);
        ~Matrix();

        // ADT
        int rows() const;
        int columns() const;
        T &operator()(int i, int j) const;
        Matrix &operator=(const Matrix &matrix);
        Matrix operator+() const;
        Matrix operator+(const Matrix &matrix) const;
        Matrix operator-() const;
        Matrix operator-(const Matrix &matrix) const;
        Matrix operator*(const Matrix &matrix) const;
        Matrix &operator+=(const T &element);

      private:
        int theRows;
        int theColumns;
        T *element;
    };

    /*!
     * \brief Matrix<T>::Matrix
     * \param theRows
     * \param theColumns
     */
    template <typename T>
    Matrix<T>::Matrix(int theRows, int theColumns) {
        if (theRows < 0 || theColumns < 0) {
            std::ostringstream s;
            s << "Rows and coloums must be >= 0";
            throw IllegalParameterValue(s.str());
        }

        if ((theColumns == 0 || theRows == 0) && (theColumns != 0 || theRows != 0)) {
            throw IllegalParameterValue("Either both or neither rows and columns should be zero");
        }

        this->theRows = theRows;
        this->theColumns = theColumns;
        this->element = new T[theRows * theColumns];
    }

    /*!
     * \brief Matrix<T>::Matrix
     * \param x
     */
    template <typename T>
    Matrix<T>::Matrix(const Matrix &x) {
        this->theRows = x.theRows;
        this->theColumns = x.theColumns;
        this->element = new T[theRows * theColumns];

        std::copy(x.element, x.element + theRows * theColumns, element);
    }

    /*!
     * \brief Matrix<T>::~Matrix
     */
    template <typename T>
    Matrix<T>::~Matrix() {
        delete[] element;
    }

    /*!
     * \brief Matrix<T>::rows
     * \return
     */
    template <typename T>
    int Matrix<T>::rows() const {
        return theRows;
    }

    /*!
     * \brief Matrix<T>::columns
     * \return
     */
    template <typename T>
    int Matrix<T>::columns() const {
        return theColumns;
    }

    /*!
     * \brief Matrix<T>::operator ()
     * \param i
     * \param j
     * \return
     */
    template <typename T>
    T &Matrix<T>::operator()(int i, int j) const {
        if (i < 1 || j < 1 || i > theRows || j > theColumns) {
            std::ostringstream s;
            s << "i = " << i << " rows = " << theRows << "j = " << j << " columns = " << theColumns;
            throw MatrixIndexOutOfBounds(s.str());
        }

        return element[(i - 1) * theColumns + (j - 1)];
    }

    /*!
     * \brief Matrix<T>::operator =
     * \param matrix
     * \return
     */
    template <typename T>
    Matrix<T> &Matrix<T>::operator=(const Matrix &matrix) {
        if (this == &matrix) {
            return *this;
        }

        theRows = matrix.theRows;
        theColumns = matrix.theColumns;
        element = new T[theRows * theColumns];

        std::copy(matrix.element, matrix.element + theRows * theColumns, element);

        return *this;
    }

    /*!
     * \brief Matrix<T>::operator +
     * \return
     */
    template <typename T>
    Matrix<T> Matrix<T>::operator+() const {
    }

    /*!
     * \brief Matrix<T>::operator +
     * \param matrix
     * \return
     */
    template <typename T>
    Matrix<T> Matrix<T>::operator+(const Matrix &matrix) const {
        if (theRows != matrix.theRows || theColumns != matrix.theColumns) {
            throw MatrixSizeMismatch();
        }

        Matrix<T> w(theRows, theColumns);
        for (int i = 0; i != theRows * theColumns; ++i) {
            w.element[i] = element[i] + matrix.element[i];
        }

        return w;
    }

    /*!
     * \brief Matrix<T>::operator -
     * \return
     */
    template <typename T>
    Matrix<T> Matrix<T>::operator-() const {
        Matrix<T> w(theRows, theColumns);

        for (int i = 0; i != theRows * theColumns; ++i) {
            w.element[i] = -element[i];
        }

        return w;
    }

    /*!
     * \brief Matrix<T>::operator *
     * \param matrix
     * \return
     */
    template <typename T>
    Matrix<T> Matrix<T>::operator*(const Matrix &matrix) const {
        if (theColumns != matrix.theRows) {
            throw MatrixSizeMismatch();
        }

        Matrix<T> w(theRows, matrix.theColumns);

        /*! compute w(i, j) for all i and j */
        int ct = 0;
        int cm = 0;
        int cw = 0;

        /*! compute w(i, j) for all i and j */
        for (int iRow = 1; iRow <= theRows; ++iRow) {
            /*! compute row i of result */
            for (int iCol = 1; iCol <= matrix.theColumns; ++iCol) {
                /*! compute first term of w(i, j) */
                T sum = element[ct] * matrix.element[cm];

                /*! add in remaining terms */
                for (int k = 2; k <= theColumns; ++k) {
                    ++ct;                         //<! next term in row i of *this;
                    cm = cm + matrix.theColumns;  // next in column j of m
                    sum += element[ct] * matrix.element[cm];
                }

                // reset to start of row and next column
                ct -= theColumns - 1;
                cm = iCol;

                w.element[cw++] = sum;  // save w(i, j)
            }

            /*! reset to start of next row and first column */
            ct += theColumns;
            cm = 0;
        }

        return w;
    }

    /*!
     * \brief Matrix<T>::operator +=
     * \param element
     * \return
     */
    template <typename T>
    Matrix<T> &Matrix<T>::operator+=(const T &element) {
        for (int i = 0; i != theRows * theColumns; ++i) {
            this->element[i] += element;
        }

        return *this;
    }

    /*!
     * \brief operator <<
     * \param out
     * \param matrix
     * \return
     */
    template <typename U>
    std::ostream &operator<<(std::ostream &out, const Matrix<U> &matrix) {
        for (int i = 0; i != matrix.theRows; ++i) {
            for (int j = 0; j != matrix.theColumns; ++j) {
                out << matrix.element[i * matrix.theColumns + j] << "   ";
            }
            out << std::endl;
        }

        return out;
    }

}  // namespace DSAA

#endif  // MATRIX_HPP
