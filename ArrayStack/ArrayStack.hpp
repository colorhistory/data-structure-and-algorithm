#ifndef ARRAYSTACK_HPP
#define ARRAYSTACK_HPP

#include "bits/stdc++.h"

#include "Exception.hpp"
#include "Stack.hpp"
#include "changeLength1D.hpp"

namespace DSAA {

    template <typename T>
    class ArrayStack : public Stack<T> {
      public:
        ArrayStack(int initialCapacity = 10);
        ~ArrayStack();

        // ADT
        bool empty() const;
        int size() const;

        T& top();

        void pop();
        void push(const T& theElement);

      private:
        int stackTop;
        int arrayLength;
        T* stack;
    };

    /*!
     * \brief ArrayStack<T>::ArrayStack
     * \param initialCapacity
     */
    template <typename T>
    inline ArrayStack<T>::ArrayStack(int initialCapacity) {
        if (initialCapacity < 1) {
            std::ostringstream s;
            s << "Initial capacity = " << initialCapacity << " must be > 0";
            throw IllegalParameterValue(s.str());
        }

        stackTop = -1;
        arrayLength = initialCapacity;
        stack = new T[arrayLength];
    }

    /*!
     * \brief ArrayStack<T>::~ArrayStack
     */
    template <typename T>
    inline ArrayStack<T>::~ArrayStack() {
        delete[] stack;
    }

    /*!
     * \brief ArrayStack<T>::empty
     * \return
     */
    template <typename T>
    inline bool ArrayStack<T>::empty() const {
        return stackTop == -1;
    }

    /*!
     * \brief ArrayStack<T>::size
     * \return
     */
    template <typename T>
    int ArrayStack<T>::size() const {
        return stackTop + 1;
    }

    /*!
     * \brief ArrayStack<T>::top
     * \return
     */
    template <typename T>
    T& ArrayStack<T>::top() {
        if (empty()) {
            throw StackEmpty();
        }
        return stack[stackTop];
    }

    /*!
     * \brief ArrayStack<T>::pop
     */
    template <typename T>
    void ArrayStack<T>::pop() {
        if (empty()) {
            throw StackEmpty();
        }
        stack[stackTop--].~T();
    }

    /*!
     * \brief ArrayStack<T>::push
     * \param theElement
     */
    template <typename T>
    void ArrayStack<T>::push(const T& theElement) {
        if (size() == arrayLength) {
            changeLength1D(stack, arrayLength, 2 * arrayLength);
            arrayLength = 2 * arrayLength;
        }
        stack[++stackTop] = theElement;
    }

}  // namespace DSAA
#endif  // ARRAYSTACK_HPP
