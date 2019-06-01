#ifndef ARRAYLISTWITHITERATOR_HPP
#define ARRAYLISTWITHITERATOR_HPP

#include "bits/stdc++.h"

#include "LinearList.hpp"
#include "changeLength1D.hpp"
#include "Exception.hpp"

namespace DSAA {

    template <typename T>
    class ArrayListWithIterator {
      public:
        ArrayListWithIterator(int initialCapacity = 10);
        ArrayListWithIterator(const ArrayListWithIterator<T> &arrayList);
        ~ArrayListWithIterator();

        // ADT
        bool empty() const;
        int size() const;
        int capacity() const;

        T &get(int theIndex) const;
        int indexOf(const T &element) const;

        void erase(int theIndex);
        void insert(int theIndex, const T &element);
        void output(std::ostream &out) const;

        class iterator {
          public:
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = T *;
            using reference = T &;

            iterator(T *thePosition = nullptr);

            T &operator*() const;
            T *operator->() const;

            iterator &operator++();
            iterator operator++(int);

            iterator &operator--();
            iterator operator--(int);

            bool operator==(const iterator &rhs) const;
            bool operator!=(const iterator &rhs) const;

          private:
            T *position;
        };
        iterator begin();
        iterator end();

      private:
        void checkIndex(int theIndex) const;
        int listSize;
        int arrayLength;
        T *elements;
    };

    /*!
     * \brief ArrayListWithIterator<T>::ArrayListWithIterator
     * \param initialCapacity
     */
    template <typename T>
    inline ArrayListWithIterator<T>::ArrayListWithIterator(int initialCapacity) {
        if (initialCapacity < 0) {
            std::ostringstream s;
            s << "The initial size " << initialCapacity << " must be > 0";
            throw IllegalParameterValue(s.str());
        }

        listSize = 0;
        arrayLength = initialCapacity;
        elements = new T[arrayLength];
    }

    /*!
     * \brief ArrayListWithIterator<T>::ArrayListWithIterator
     * \param arrayList
     */
    template <typename T>
    inline ArrayListWithIterator<T>::ArrayListWithIterator(const ArrayListWithIterator<T> &arrayList) {
        listSize = arrayList.listSize;
        arrayLength = arrayList.arrayLength;
        elements = new T[arrayLength];

        std::copy(arrayList.elements, arrayList.elements + listSize, elements);
    }

    /*!
     * \brief ArrayListWithIterator<T>::~ArrayListWithIterator
     */
    template <typename T>
    inline ArrayListWithIterator<T>::~ArrayListWithIterator() {
        delete[] elements;
    }

    /*!
     * \brief ArrayListWithIterator<T>::empty
     * \return
     */
    template <typename T>
    inline bool ArrayListWithIterator<T>::empty() const {
        return listSize == 0;
    }

    /*!
     * \brief ArrayListWithIterator<T>::size
     * \return
     */
    template <typename T>
    inline int ArrayListWithIterator<T>::size() const {
        return listSize;
    }

    /*!
     * \brief ArrayListWithIterator<T>::capacity
     * \return
     */
    template <typename T>
    inline int ArrayListWithIterator<T>::capacity() const {
        return arrayLength;
    }

    /*!
     * \brief ArrayListWithIterator<T>::get
     * \param theIndex
     * \return
     */
    template <typename T>
    inline T &ArrayListWithIterator<T>::get(int theIndex) const {
        checkIndex(theIndex);

        return elements[theIndex];
    }

    /*!
     * \brief ArrayListWithIterator<T>::indexOf
     * \param element
     * \return
     */
    template <typename T>
    inline int ArrayListWithIterator<T>::indexOf(const T &element) const {
        int pos = static_cast<int>(std::find(elements, elements + listSize, element) - elements);
        if (pos != listSize) {
            return pos;
        }

        return -1;
    }

    /*!
     * \brief ArrayListWithIterator<T>::erase
     * \param theIndex
     */
    template <typename T>
    inline void ArrayListWithIterator<T>::erase(int theIndex) {
        checkIndex(theIndex);

        std::copy(elements + theIndex + 1, elements + listSize, elements + theIndex);

        elements[--listSize].~T();
    }

    /*!
     * \brief ArrayListWithIterator<T>::insert
     * \param theIndex
     * \param element
     */
    template <typename T>
    inline void ArrayListWithIterator<T>::insert(int theIndex, const T &element) {
        if (theIndex < 0 || theIndex > listSize) {
            std::ostringstream s;
            s << "index = " << theIndex << " size = " << listSize;
            throw IllegalIndex(s.str());
        }

        if (arrayLength == listSize) {
            changeLength1D(elements, arrayLength, 2 * arrayLength);
            arrayLength = 2 * arrayLength;
        }

        std::copy_backward(elements + theIndex, elements + listSize, elements + listSize + 1);
        elements[theIndex] = element;

        ++listSize;
    }

    /*!
     * \brief ArrayListWithIterator<T>::output
     * \param out
     */
    template <typename T>
    inline void ArrayListWithIterator<T>::output(std::ostream &out) const {
        std::copy(elements, elements + listSize, std::ostream_iterator<T>(out, "   "));
    }

    /*!
     * \brief ArrayListWithIterator<T>::begin
     * \return
     */
    template <typename T>
    inline typename ArrayListWithIterator<T>::iterator ArrayListWithIterator<T>::begin() {
        return iterator(elements);
    }

    /*!
     * \brief ArrayListWithIterator<T>::end
     * \return
     */
    template <typename T>
    inline typename ArrayListWithIterator<T>::iterator ArrayListWithIterator<T>::end() {
        return iterator(elements + listSize);
    }

    /*!
     * \brief ArrayListWithIterator<T>::checkIndex
     * \param theIndex
     */
    template <typename T>
    inline void ArrayListWithIterator<T>::checkIndex(int theIndex) const {
        if (theIndex < 0 || theIndex >= listSize) {
            std::ostringstream s;
            s << "The index " << theIndex << " size = " << listSize;
            throw IllegalIndex(s.str());
        }
    }

    /*!
     * \brief ArrayListWithIterator<T>::iterator::iterator
     * \param thePosition
     */
    template <typename T>
    inline ArrayListWithIterator<T>::iterator::iterator(T *thePosition) {
        position = thePosition;
    }

    /*!
     * \brief ArrayListWithIterator<T>::iterator::operator *
     * \return
     */
    template <typename T>
    inline T &ArrayListWithIterator<T>::iterator::operator*() const {
        return *position;
    }

    /*!
     * \brief ArrayListWithIterator<T>::iterator::operator ->
     * \return
     */
    template <typename T>
    inline T *ArrayListWithIterator<T>::iterator::operator->() const {
        return &operator*();
    }

    /*!
     * \brief ArrayListWithIterator<T>::iterator::operator ++
     * \return
     */
    template <typename T>
    inline typename ArrayListWithIterator<T>::iterator &ArrayListWithIterator<T>::iterator::operator++() {
        ++position;

        return *this;
    }

    /*!
     * \brief ArrayListWithIterator<T>::iterator::operator ++
     * \return
     */
    template <typename T>
    inline typename ArrayListWithIterator<T>::iterator ArrayListWithIterator<T>::iterator::operator++(int) {
        iterator oldIterator = *this;
        ++position;

        return oldIterator;
    }

    /*!
     * \brief ArrayListWithIterator<T>::iterator::operator --
     * \return
     */
    template <typename T>
    inline typename ArrayListWithIterator<T>::iterator &ArrayListWithIterator<T>::iterator::operator--() {
        --position;

        return *this;
    }

    /*!
     * \brief ArrayListWithIterator<T>::iterator::operator --
     * \return
     */
    template <typename T>
    inline typename ArrayListWithIterator<T>::iterator ArrayListWithIterator<T>::iterator::operator--(int) {
        iterator oldIterator = *this;
        --position;

        return oldIterator;
    }

    /*!
     * \brief ArrayListWithIterator<T>::iterator::operator ==
     * \param rhs
     * \return
     */
    template <typename T>
    inline bool ArrayListWithIterator<T>::iterator::operator==(const ArrayListWithIterator<T>::iterator &rhs) const {
        return position == rhs.position;
    }

    /*!
     * \brief ArrayListWithIterator::iterator::operator !=
     * \param rhs
     * \return
     */
    template <typename T>
    inline bool ArrayListWithIterator<T>::iterator::operator!=(const ArrayListWithIterator<T>::iterator &rhs) const {
        return !this->operator==(rhs);
    }

    /*!
     * \brief operator <<
     * \param out
     * \param arrayList
     * \return
     */
    template <typename T>
    inline std::ostream &operator<<(std::ostream &out, const ArrayListWithIterator<T> &arrayList) {
        arrayList.output(out);

        return out;
    }

}  // namespace DSAA
#endif  // ARRAYLISTWITHITERATOR_HPP
