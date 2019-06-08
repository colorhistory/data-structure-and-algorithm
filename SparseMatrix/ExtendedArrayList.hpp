#ifndef EXTENDEDARRAYLIST_HPP
#define EXTENDEDARRAYLIST_HPP

#include "bits/stdc++.h"

#include "Exception.hpp"
#include "ExtendedLinearList.hpp"
#include "changeLength1D.hpp"

namespace DSAA {

    template <typename T>
    class ExtendedArrayList : public ExtendedLinearList<T> {
      public:
        ExtendedArrayList(int initialCapacity = 10);
        ExtendedArrayList(const T& arrayList);
        ~ExtendedArrayList();

        // ADT
        bool empty() const;
        int size() const;
        int capacity() const;

        T& get(int theIndex) const;
        int indexOf(const T& theElement) const;

        void erase(int theIndex);
        void insert(int theIndex, const T& theElement);
        void output(std::ostream& out) const;
        virtual void push_back(const T& /*theElement*/) override {
        }

        void reset(int arrayLength);
        void set(int theIndex, const T& theElement);
        void clear();

        class iterator;
        iterator begin();
        iterator end();

        class iterator {
          public:
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = T*;
            using reference = T&;

            iterator(T* thePosition = nullptr);

            // ADT
            T& operator*() const;
            T* operator->() const;

            iterator& operator++();
            iterator operator++(int);

            iterator& operator--();
            iterator operator--(int);

            bool operator==(const iterator& rhs) const;
            bool operator!=(const iterator& rhs) const;

          private:
            T* position;
        };

      private:
        void checkIndex(int theIndex) const;

        int arrayLength;
        int listSize;
        T* elements;
    };

    /*!
     * \brief ExtendedArrayList<T>::ExtendedArrayList
     * \param initialCapacity
     */
    template <typename T>
    inline ExtendedArrayList<T>::ExtendedArrayList(int initialCapacity) {
        if (initialCapacity < 1) {
            std::ostringstream s;
            s << "The initialCapacity = " << initialCapacity << " must be > 0";
            throw IllegalParameterValue(s.str());
        }

        arrayLength = initialCapacity;
        listSize = 0;
        elements = new T[arrayLength];
    }

    /*!
     * \brief ExtendedArrayList<T>::ExtendedArrayList
     * \param arrayList
     */
    template <typename T>
    inline ExtendedArrayList<T>::ExtendedArrayList(const T& arrayList) {
        arrayLength = arrayList.arrayLength;
        listSize = arrayList.listSize;
        elements = new T[arrayLength];

        std::copy(arrayList.elements, arrayList.elements + listSize, elements);
    }

    /*!
     * \brief ExtendedArrayList<T>::~ExtendedArrayList
     */
    template <typename T>
    ExtendedArrayList<T>::~ExtendedArrayList() {
        delete[] elements;
    }

    /*!
     * \brief ExtendedArrayList<T>::empty
     * \return
     */
    template <typename T>
    bool ExtendedArrayList<T>::empty() const {
        return listSize == 0;
    }

    /*!
     * \brief ExtendedArrayList<T>::size
     * \return
     */
    template <typename T>
    int ExtendedArrayList<T>::size() const {
        return listSize;
    }

    /*!
     * \brief ExtendedArrayList<T>::capacity
     * \return
     */
    template <typename T>
    int ExtendedArrayList<T>::capacity() const {
        return arrayLength;
    }

    /*!
     * \brief ExtendedArrayList<T>::get
     * \param theIndex
     * \return
     */
    template <typename T>
    T& ExtendedArrayList<T>::get(int theIndex) const {
        checkIndex(theIndex);

        return elements[theIndex];
    }

    /*!
     * \brief ExtendedArrayList<T>::indexOf
     * \param theElement
     * \return
     */
    template <typename T>
    int ExtendedArrayList<T>::indexOf(const T& theElement) const {
        for (int i = 0; i != listSize; ++i) {
            if (elements[i] == theElement) {
                break;
            }
            return i;
        }
        return -1;
    }

    /*!
     * \brief ExtendedArrayList<T>::erase
     * \param theIndex
     */
    template <typename T>
    void ExtendedArrayList<T>::erase(int theIndex) {
        checkIndex(theIndex);

        std::copy(elements + theIndex + 1, elements + listSize, elements + theIndex);

        elements[--listSize].~T();
    }

    /*!
     * \brief ExtendedArrayList<T>::insert
     * \param theIndex
     * \param theElement
     */
    template <typename T>
    void ExtendedArrayList<T>::insert(int theIndex, const T& theElement) {
        if (theIndex < 0 || theIndex > listSize) {
            std::ostringstream s;
            s << "index = " << theIndex << " size = " << listSize;
            throw IllegalIndex(s.str());
        }

        if (listSize == arrayLength) {
            changeLength1D(elements, arrayLength, 2 * arrayLength);
            arrayLength = 2 * arrayLength;
        }

        std::copy_backward(elements + theIndex, elements + listSize, elements + listSize + 1);
        elements[theIndex] = theElement;
        ++listSize;
    }

    /*!
     * \brief ExtendedArrayList<T>::output
     * \param out
     */
    template <typename T>
    void ExtendedArrayList<T>::output(std::ostream& out) const {
        std::copy(elements, elements + listSize, std::ostream_iterator<T>(out, "   "));
    }

    /*!
     * \brief ExtendedArrayList<T>::reset
     * \param arrayLength
     */
    template <typename T>
    void ExtendedArrayList<T>::reset(int theSize) {
        if (theSize < 0) {
            std::stringstream s;
            s << "Requested size = " << theSize << " must be >= 0";
            throw IllegalIndex(s.str());
        }

        if (theSize > arrayLength) {
            delete[] elements;
            elements = new T[theSize];
            arrayLength = theSize;
        }

        listSize = theSize;
    }

    /*!
     * \brief ExtendedArrayList<T>::set
     * \param theIndex
     * \param theElement
     */
    template <typename T>
    void ExtendedArrayList<T>::set(int theIndex, const T& theElement) {
        checkIndex(theIndex);

        elements[theIndex] = theElement;
    }

    /*!
     * \brief ExtendedArrayList::clear
     */
    template <typename T>
    void ExtendedArrayList<T>::clear() {
        for (int i = 0; i != listSize; ++i) {
            elements[i].~T();
        }
        listSize = 0;
    }

    /*!
     * \brief ExtendedArrayList<T>::begin
     * \return
     */
    template <typename T>
    typename ExtendedArrayList<T>::iterator ExtendedArrayList<T>::begin() {
        return iterator(elements);
    }

    /*!
     * \brief ExtendedArrayList<T>::end
     * \return
     */
    template <typename T>
    typename ExtendedArrayList<T>::iterator ExtendedArrayList<T>::end() {
        return iterator(elements + listSize);
    }

    /*!
     * \brief ExtendedArrayList<T>::checkIndex
     * \param theIndex
     */
    template <typename T>
    void ExtendedArrayList<T>::checkIndex(int theIndex) const {
        if (theIndex < 0 || theIndex >= listSize) {
            std::stringstream s;
            s << "The index = " << theIndex << " size = " << listSize;
            throw IllegalIndex(s.str());
        }
    }

    /*!
     * \brief ExtendedArrayList<T>::iterator::iterator
     * \param thePosition
     */
    template <typename T>
    ExtendedArrayList<T>::iterator::iterator(T* thePosition) {
        position = thePosition;
    }

    /*!
     * \brief ExtendedArrayList<T>::iterator::operator *
     * \return
     */
    template <typename T>
    T& ExtendedArrayList<T>::iterator::operator*() const {
        return *position;
    }

    /*!
     * \brief ExtendedArrayList<T>::iterator::operator ->
     * \return
     */
    template <typename T>
    T* ExtendedArrayList<T>::iterator::operator->() const {
        return &(*position);
    }

    /*!
     * \brief ExtendedArrayList<T>::iterator::operator ++
     * \return
     */
    template <typename T>
    typename ExtendedArrayList<T>::iterator& ExtendedArrayList<T>::iterator::operator++() {
        ++position;
        return *this;
    }

    /*!
     * \brief ExtendedArrayList<T>::iterator::operator ++
     * \return
     */
    template <typename T>
    typename ExtendedArrayList<T>::iterator ExtendedArrayList<T>::iterator::operator++(int) {
        iterator old = *this;
        ++position;
        return old;
    }

    /*!
     * \brief ExtendedArrayList<T>::iterator::operator --
     * \return
     */
    template <typename T>
    typename ExtendedArrayList<T>::iterator& ExtendedArrayList<T>::iterator::operator--() {
        --position;
        return *this;
    }

    /*!
     * \brief ExtendedArrayList<T>::iterator::operator --
     * \return
     */
    template <typename T>
    typename ExtendedArrayList<T>::iterator ExtendedArrayList<T>::iterator::operator--(int) {
        iterator old = *this;
        --position;
        return old;
    }

    /*!
     * \brief ExtendedArrayList<T>::iterator::operator ==
     * \param rhs
     * \return
     */
    template <typename T>
    bool ExtendedArrayList<T>::iterator::operator==(const ExtendedArrayList<T>::iterator& rhs) const {
        return position == rhs.position;
    }

    /*!
     * \brief ExtendedArrayList<T>::iterator::operator !=
     * \param rhs
     * \return
     */
    template <typename T>
    bool ExtendedArrayList<T>::iterator::operator!=(const ExtendedArrayList<T>::iterator& rhs) const {
        return !(operator==(rhs));
    }

}  // namespace DSAA
#endif  // EXTENDEDARRAYLIST_HPP
