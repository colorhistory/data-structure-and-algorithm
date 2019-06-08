#ifndef DERIVEDARRAYSTACK_HPP
#define DERIVEDARRAYSTACK_HPP

#include "bits/stdc++.h"

#include "ArrayList.hpp"
#include "Stack.hpp"

namespace DSAA {

    template <typename T>
    class DerivedArrayStack : private ArrayList<T>, public Stack<T> {
      public:
        DerivedArrayStack(int initialCapacity = 10);

        // ADT
        bool empty() const;
        int size() const;

        T& top();

        void pop();
        void push(const T& theElement);
    };

    /*!
     * \brief DerivedArrayStack<T>::DerivedArrayStack
     * \param initialCapacity
     */
    template <typename T>
    DerivedArrayStack<T>::DerivedArrayStack(int initialCapacity) : ArrayList<T>(initialCapacity) {
    }

    /*!
     * \brief DerivedArrayStack<T>::empty
     * \return
     */
    template <typename T>
    bool DerivedArrayStack<T>::empty() const {
        return ArrayList<T>::empty();
    }

    /*!
     * \brief DerivedArrayStack::size
     * \return
     */
    template <typename T>
    int DerivedArrayStack<T>::size() const {
        return ArrayList<T>::size();
    }

    /*!
     * \brief DerivedArrayStack<T>::top
     * \return
     */
    template <typename T>
    T& DerivedArrayStack<T>::top() {
        if (empty()) {
            throw StackEmpty();
        }
        return ArrayList<T>::get(size() - 1);
    }

    /*!
     * \brief DerivedArrayStack<T>::pop
     */
    template <typename T>
    void DerivedArrayStack<T>::pop() {
        if (empty()) {
            throw StackEmpty();
        }
        ArrayList<T>::erase(size() - 1);
    }

    /*!
     * \brief DerivedArrayStack<T>::push
     * \param theElement
     */
    template <typename T>
    void DerivedArrayStack<T>::push(const T& theElement) {
        ArrayList<T>::insert(size(), theElement);
    }

}  // namespace DSAA

#endif  // DERIVEDARRAYSTACK_HPP
