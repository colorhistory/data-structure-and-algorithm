#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <algorithm>
#include <exception>

template <typename Object>
class Vector {
  public:
    explicit Vector(int initSize = 0);
    Vector(const Vector &rhs);
    Vector &operator=(const Vector &rhs);
    ~Vector();
    Vector(Vector &&rhs);
    Vector &operator=(Vector &&rhs);

    // ADT
    void resize(int newSize);
    void reserve(int newCapacity);

    Object &operator[](int index);
    const Object &operator[](int index) const;

    bool empty() const;
    int size() const;
    int capacity() const;

    void push_back(const Object &object);
    void push_back(Object &&object);

    void pop_back();
    const Object &back() const;

    using iterator = Object *;
    using const_iterator = const Object *;

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

  private:
    static const int SPACE_CAPACITY = 16;
    int theSize;
    int theCapacity;
    Object *objects;
};

template <typename Object>
inline Vector<Object>::Vector(int initSize) : theSize{initSize}, theCapacity{theSize + SPACE_CAPACITY} {
    objects = new Object[theCapacity];
}

template <typename Object>
inline Vector<Object>::Vector(const Vector &rhs)
    : theSize{rhs.theSize}, theCapacity{rhs.theCapacity}, objects{nullptr} {
    objects = new Object[theCapacity];
    for (int idata = 0; idata != theSize; ++idata) {
        objects[idata] = rhs.objects[idata];
    }
}

template <typename Object>
inline Vector<Object> &Vector<Object>::operator=(const Vector &rhs) {
    if (this == &rhs) {
        return;
    }

    delete[] objects;

    theSize = rhs.theSize;
    theCapacity = rhs.theCapacity;
    for (int iData = 0; iData != theSize; ++iData) {
        objects[iData] = rhs.objects[iData];
    }

    return *this;
}

template <typename Object>
inline Vector<Object>::~Vector() {
    delete[] objects;
}

/*!
 * \brief move copy constructor
 */
template <typename Object>
inline Vector<Object>::Vector(Vector &&rhs)
    : theSize{rhs.theSize}, theCapacity{rhs.theCapacity}, objects{rhs.objects} {
    rhs.theSize = 0;
    rhs.theCapacity = 0;
    rhs.objects = nullptr;
}

/*!
 * \brief move
 */
template <typename Object>
inline Vector<Object> &Vector<Object>::operator=(Vector &&rhs) {
    std::swap(theSize, rhs.theSize);
    std::swap(theCapacity, rhs.theCapacity);
    std::swap(objects, rhs.objects);

    return *this;
}

/*!
 * \brief Why don't we delete the object that newSize < theSize ?
 */
template <typename Object>
inline void Vector<Object>::resize(int newSize) {
    if (newSize > theCapacity) {
        reserve(2 * newSize);
    }

    theSize = newSize;
}

template <typename Object>
inline void Vector<Object>::reserve(int newCapacity) {
    if (newCapacity < theSize) {
        return;
    }

    Object *tempArray = new Object[newCapacity];
    for (int iData = 0; iData != theSize; ++iData) {
        tempArray[iData] = std::move(objects[iData]);
    }

    theCapacity = newCapacity;
    std::swap(tempArray, objects);
    delete[] tempArray;
}

template <typename Object>
inline Object &Vector<Object>::operator[](int index) {
    if (index >= theSize) {
        //
    }
    return objects[index];
}

template <typename Object>
inline const Object &Vector<Object>::operator[](int index) const {
    if (index >= theSize) {
        //
    }
    return objects[index];
}

template <typename Object>
inline bool Vector<Object>::empty() const {
    return theSize == 0;
}

template <typename Object>
inline int Vector<Object>::size() const {
    return theSize;
}

template <typename Object>
inline int Vector<Object>::capacity() const {
    return theCapacity;
}

template <typename Object>
inline void Vector<Object>::push_back(const Object &object) {
    if (theSize == theCapacity) {
        reserve(2 * theCapacity + 1);
    }
    objects[theSize] = object;
    ++theSize;
}

template <typename Object>
inline void Vector<Object>::push_back(Object &&object) {
    if (theSize == theCapacity) {
        reserve(2 * theCapacity + 1);
    }
    objects[theSize] = std::move(object);
    ++theSize;
}

template <typename Object>
inline void Vector<Object>::pop_back() {
    --theSize;
}

template <typename Object>
inline const Object &Vector<Object>::back() const {
    return objects[theSize - 1];
}

template <typename Object>
inline typename Vector<Object>::iterator Vector<Object>::begin() {
    return objects;
}

template <typename Object>
inline typename Vector<Object>::const_iterator Vector<Object>::begin() const {
    return objects;
}

template <typename Object>
inline typename Vector<Object>::iterator Vector<Object>::end() {
    return &objects[theSize];
}

template <typename Object>
inline typename Vector<Object>::const_iterator Vector<Object>::end() const {
    return &objects[theSize];
}

#endif  // VECTOR_HPP
