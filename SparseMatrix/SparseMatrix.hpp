#ifndef SPARSEMATRIX_HPP
#define SPARSEMATRIX_HPP

#include "bits/stdc++.h"

#include "Exception.hpp"
#include "ExtendedArrayList.hpp"
#include "MatrixTerm.hpp"

namespace DSAA {
    template <typename T>
    class SparseMatrix;

    template <typename T>
    std::ostream &operator<<(std::ostream &out, const SparseMatrix<T> &matrix);

    template <typename T>
    std::istream &operator>>(std::istream &in, SparseMatrix<T> &matrix);

    template <typename T>
    class SparseMatrix {
        friend std::ostream &operator<<(std::ostream &out, const SparseMatrix<T> &matrix);
        friend std::istream &operator>>(std::istream &in, SparseMatrix<T> &matrix);

      public:
        void transpose(SparseMatrix &b);
        void add(SparseMatrix &b, SparseMatrix &c);

      private:
        int rows;
        int cols;

        ExtendedArrayList<MatrixTerm<T>> terms;
    };

    /*!
     * \brief operator <<
     * \param out
     * \param matrix
     * \return
     */
    template <typename T>
    std::ostream &operator<<(std::ostream &out, const SparseMatrix<T> &matrix) {
        out << "rows = " << matrix.rows << " columns = " << matrix.cols << std::endl;
        out << "nonzero terms = " << matrix.terms.size() << std::endl;

        for (typename ExtendedArrayList<MatrixTerm<T>>::iterator item = terms.begin(); item != terms.end(); item++) {
            out << "a(" << item.row << ", " << item.col << ") =" << item.value << std::endl;
        }

        return out;
    }

    /*!
     * \brief operator >>
     * \param in
     * \param matrix
     * \return
     */
    template <typename T>
    std::istream &operator>>(std::istream &in, SparseMatrix<T> &matrix) {
        int numberOfTerms;
        std::cout << "Enter number of rows, columns, and #term" << std::endl;

        in >> matrix.rows >> matrix.cols >> numberOfTerms;

        matrix.terms.reset(numberOfTerms);

        MatrixTerm<T> mTerm;
        for (int i = 0; i != numberOfTerms; ++i) {
            std::cout << "Enter row, column, and value of term " << (i + 1) << std::endl;
            in >> mTerm.row >> mTerm.col >> mTerm.value;
            matrix.terms.set(i, mTerm);
        }

        return in;
    }

    template <class T>
    void SparseMatrix<T>::transpose(SparseMatrix<T> &b) {  // Return transpose of *this in b.

        // set transpose characteristics
        b.cols = rows;
        b.rows = cols;
        b.terms.reset(terms.size());

        // initialize to compute transpose
        int *colSize = new int[cols + 1];
        int *rowNext = new int[cols + 1];

        // find number of entries in each column of *this
        for (int i = 1; i <= cols; i++)  // initialize
            colSize[i] = 0;
        for (typename ExtendedArrayList<MatrixTerm<T>>::iterator i = terms.begin(); i != terms.end(); i++) {
            colSize[(*i).col]++;
        }

        // find the starting point of each row of b
        rowNext[1] = 0;
        for (int i = 2; i <= cols; i++) {
            rowNext[i] = rowNext[i - 1] + colSize[i - 1];
        }

        // perform the transpose copying from *this to b
        MatrixTerm<T> mTerm;
        for (typename ExtendedArrayList<MatrixTerm<T>>::iterator i = terms.begin(); i != terms.end(); i++) {
            int j = rowNext[(*i).col]++;  // position in b
            mTerm.row = (*i).col;
            mTerm.col = (*i).row;
            mTerm.value = (*i).value;
            b.terms.set(j, mTerm);
        }
    }

    template <class T>
    void SparseMatrix<T>::add(SparseMatrix<T> &b, SparseMatrix<T> &c) {  // Compute c = (*this) + b.

        // verify compatibility
        if (rows != b.rows || cols != b.cols)
            throw MatrixSizeMismatch();  // incompatible matrices

        // set characteristics of result c
        c.rows = rows;
        c.cols = cols;
        c.terms.clear();
        int cSize = 0;

        // define iterators for *this and b
        typename ExtendedArrayList<MatrixTerm<T>>::iterator it = terms.begin();
        typename ExtendedArrayList<MatrixTerm<T>>::iterator ib = b.terms.begin();
        typename ExtendedArrayList<MatrixTerm<T>>::iterator itEnd = terms.end();
        typename ExtendedArrayList<MatrixTerm<T>>::iterator ibEnd = b.terms.end();

        // move through *this and b adding like terms
        while (it != itEnd && ib != ibEnd) {
            // row-major index plus cols of each term
            int tIndex = (*it).row * cols + (*it).col;
            int bIndex = (*ib).row * cols + (*ib).col;

            if (tIndex < bIndex) {  // b term comes later
                c.terms.insert(cSize++, *it);
                it++;
            } else {
                if (tIndex == bIndex) {  // both in same position

                    // append to c only if sum not zero
                    if ((*it).value + (*ib).value != 0) {
                        MatrixTerm<T> mTerm;
                        mTerm.row = (*it).row;
                        mTerm.col = (*it).col;
                        mTerm.value = (*it).value + (*ib).value;
                        c.terms.insert(cSize++, mTerm);
                    }

                    it++;
                    ib++;
                } else {  // a term comes later
                    c.terms.insert(cSize++, *ib);
                    ib++;
                }
            }
        }

        // copy over remaining terms
        for (; it != itEnd; it++) {
            c.terms.insert(cSize++, *it);
        }
        for (; ib != ibEnd; ib++) {
            c.terms.insert(cSize++, *ib);
        }
    }

}  // namespace DSAA
#endif  // SPARSEMATRIX_HPP
