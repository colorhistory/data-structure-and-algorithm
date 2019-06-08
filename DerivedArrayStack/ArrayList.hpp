#ifndef ARRAYLIST_HPP
#define ARRAYLIST_HPP

#include <iostream>
#include <sstream>

#include "Exception.hpp"
#include "LinearList.hpp"
#include "changeLength1D.hpp"

namespace DSAA {

    template <typename T>
    class ArrayList : public LinearList<T> {
      public:
        ArrayList(int initialCapacity = 10);
        ArrayList(const ArrayList<T> &arrayList);
        ~ArrayList();

        // ADT methods
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
        T *element;
    };
}  // namespace DSAA

/*!
 * \brief DSAA::ArrayList<T>::ArrayList
 * \param initialCapacity
 */
template <typename T>
inline DSAA::ArrayList<T>::ArrayList(int initialCapacity) {
    if (initialCapacity < 1) {
        std::ostringstream s;
        s << "Initial Capacity = " << initialCapacity << " Must be > 0";
        throw DSAA::IllegalParameterValue(s.str());
    }

    listSize = 0;
    arrayLength = initialCapacity;
    element = new T[arrayLength];
}

/*!
 * \brief DSAA::ArrayList<T>::ArrayList
 * \param arrayList
 */
template <typename T>
inline DSAA::ArrayList<T>::ArrayList(const ArrayList<T> &arrayList) {
    listSize = arrayList.listSize;
    arrayLength = arrayList.arrayLength;
    element = new T[arrayLength];
    std::copy(arrayList.element, arrayList.element + listSize, element);
}

/*!
 * \brief DSAA::ArrayList<T>::~ArrayList
 */
template <typename T>
inline DSAA::ArrayList<T>::~ArrayList() {
    delete[] element;
}

/*!
 * \brief DSAA::ArrayList<T>::emtpy
 * \return
 */
template <typename T>
inline bool DSAA::ArrayList<T>::empty() const {
    return listSize == 0;
}

/*!
 * \brief DSAA::ArrayList::size
 * \return
 */
template <typename T>
int DSAA::ArrayList<T>::size() const {
    return listSize;
}

/*!
 * \brief DSAA::ArrayList<T>::capacity
 * \return
 */
template <typename T>
int DSAA::ArrayList<T>::capacity() const {
    return arrayLength;
}

/*!
 * \brief DSAA::ArrayList<T>::get
 * \param theIndex
 * \return
 */
template <typename T>
T &DSAA::ArrayList<T>::get(int theIndex) const {
    checkIndex(theIndex);

    return element[theIndex];
}

/*!
 * \brief DSAA::ArrayList<T>::indexOf
 * \param theElement
 * \return
 */
template <typename T>
int DSAA::ArrayList<T>::indexOf(const T &theElement) const {
    for (int i = 0; i != listSize; ++i) {
        if (element[i] == theElement) {
            return i;
        }
    }
    return -1;
}

/*!
 * \brief DSAA::ArrayList<T>::erase
 * \param theIndex
 */
template <typename T>
void DSAA::ArrayList<T>::erase(int theIndex) {
    checkIndex(theIndex);

    for (int i = theIndex; i != listSize; ++i) {
        element[i] = element[i + 1];
    }
    element[--listSize].~T();
}

/*!
 * \brief DSAA::ArrayList<T>::insert
 * \param theIndex
 * \param theElement
 */
template <typename T>
void DSAA::ArrayList<T>::insert(int theIndex, const T &theElement) {
    if (theIndex < 0 || theIndex > listSize) {
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw DSAA::IllegalIndex(s.str());
    }

    if (listSize == arrayLength) {
        DSAA::changeLength1D(element, arrayLength, 2 * arrayLength);
        arrayLength = 2 * arrayLength;
    }

    T *temp = new T[listSize - theIndex];
    for (int i = theIndex; i != listSize; ++i) {
        temp[i - theIndex] = element[i];
    }
    element[theIndex] = theElement;
    for (int i = 0; i != listSize - theIndex; ++i) {
        element[theIndex + i + 1] = temp[i];
    }
    delete[] temp;

    ++listSize;
}

/*!
 * \brief DSAA::ArrayList<T>::output
 * \param out
 */
template <typename T>
void DSAA::ArrayList<T>::output(std::ostream &out) const {
    for (int i = 0; i != listSize; ++i) {
        out << element[i] << "   ";
    }
}

/*!
 * \brief DSAA::ArrayList<T>::checkIndex
 * \param theIndex
 */
template <typename T>
void DSAA::ArrayList<T>::checkIndex(int theIndex) const {
    if (theIndex < 0 || theIndex >= listSize) {
        std::ostringstream s;
        s << "Index = " << theIndex << " size = " << listSize;
        throw DSAA::IllegalIndex(s.str());
    }
}

/*!
 * \brief operator <<
 * \param out
 * \param arrayList
 * \return
 */
template <typename T>
std::ostream &operator<<(std::ostream &out, const DSAA::ArrayList<T> &arrayList) {
    arrayList.output(out);

    return out;
}

#endif  // ARRAYLIST_HPP
