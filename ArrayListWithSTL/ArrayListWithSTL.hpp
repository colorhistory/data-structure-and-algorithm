#ifndef ARRAYLISTWITHSTL_HPP
#define ARRAYLISTWITHSTL_HPP

#include "bits/stdc++.h"

#include "LinearList.hpp"
#include "changeLength1D.hpp"
#include "Exception.hpp"

namespace DSAA {

    template <typename T>
    class ArrayListWithSTL : public LinearList<T> {
      public:
        ArrayListWithSTL(int initialCapacity = 10);
        ArrayListWithSTL(const ArrayListWithSTL<T> &arrayList);
        ~ArrayListWithSTL();

        // ADT
        bool empty() const;
        int size() const;
        int capacity() const;

        T &get(int theIndex) const;
        int indexOf(const T &theElement) const;

        void erase(int theIndex);
        void insert(int theIndex, const T &theElement);
        void output(std::ostream &out) const;

      private:
        void checkIndex(int theIndex) const;

        int listSize;
        int arrayLength;
        T *elements;
    };

    template <typename T>
    ArrayListWithSTL<T>::ArrayListWithSTL(int initialCapacity) {
        if (initialCapacity < 1) {
            std::ostringstream s;
            s << "Initial capacity = " << initialCapacity << " Must be > 0";
            throw IllegalParameterValue(s.str());
        }

        listSize = 0;
        arrayLength = initialCapacity;
        elements = new T[arrayLength];
    }

    template <typename T>
    ArrayListWithSTL<T>::ArrayListWithSTL(const ArrayListWithSTL<T> &arrayList) {
        listSize = arrayList.listSize;
        arrayLength = arrayList.arrayLength;
        elements = new T[arrayLength];

        std::copy(arrayList.elements, arrayList.elements + listSize, elements);
    }

    template <typename T>
    ArrayListWithSTL<T>::~ArrayListWithSTL() {
        delete[] elements;
    }

    template <typename T>
    bool ArrayListWithSTL<T>::empty() const {
        return listSize == 0;
    }

    template <typename T>
    int ArrayListWithSTL<T>::size() const {
        return listSize;
    }

    template <typename T>
    int ArrayListWithSTL<T>::capacity() const {
        return arrayLength;
    }

    template <typename T>
    T &ArrayListWithSTL<T>::get(int theIndex) const {
        checkIndex(theIndex);

        return elements[theIndex];
    }

    template <typename T>
    int ArrayListWithSTL<T>::indexOf(const T &theElement) const {
        int pos = static_cast<int>(std::find(elements, elements + listSize, theElement) - elements);

        if (pos == listSize) {
            return -1;
        }

        return pos;
    }

    template <typename T>
    void ArrayListWithSTL<T>::erase(int theIndex) {
        checkIndex(theIndex);

        std::copy(elements + theIndex + 1, elements + listSize, elements + theIndex);

        elements[--listSize].~T();
    }

    template <typename T>
    void ArrayListWithSTL<T>::insert(int theIndex, const T &theElement) {
        if (theIndex < 0 || theIndex > listSize) {
            std::ostringstream s;
            s << "Index = " << theIndex << " size = " << listSize;
            throw IllegalIndex(s.str());
        }

        if (listSize == arrayLength) {
            changeLength1D(elements, arrayLength, 2 * arrayLength);
            arrayLength *= 2;  ////////////////////////////////
        }

        std::copy_backward(elements + theIndex, elements + listSize, elements + listSize + 1);
        elements[theIndex] = theElement;

        ++listSize;
    }

    template <typename T>
    void ArrayListWithSTL<T>::output(std::ostream &out) const {
        std::copy(elements, elements + listSize, std::ostream_iterator<T>(out, "   "));
    }

    template <typename T>
    void ArrayListWithSTL<T>::checkIndex(int theIndex) const {
        if (theIndex < 0 || theIndex >= listSize) {
            std::ostringstream s;
            s << "The index = " << theIndex << " size = " << listSize;
            throw IllegalIndex(s.str());
        }
    }

    template <typename T>
    std::ostream &operator<<(std::ostream &out, const ArrayListWithSTL<T> &arrayList) {
        arrayList.output(out);

        return out;
    }

}  // namespace DSAA

#endif  // ARRAYLISTWITHSTL_HPP
