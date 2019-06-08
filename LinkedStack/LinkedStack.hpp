#ifndef LINKEDSTACK_HPP
#define LINKEDSTACK_HPP

#include "bits/stdc++.h"

#include "ChainNode.hpp"
#include "Exception.hpp"
#include "Stack.hpp"

namespace DSAA {

    template <typename T>
    class LinkedStack : public Stack<T> {
      public:
        LinkedStack(int initialCapacity = 10);
        ~LinkedStack();

        // ADT
        bool empty() const;
        int size() const;

        T& top();

        void pop();
        void push(const T& theElement);

      private:
        ChainNode<T>* stackTop;
        int stackSize;
    };

    /*!
     * \brief LinkedStack<T>::LinkedStack
     * \param initialCapacity
     */
    template <typename T>
    LinkedStack<T>::LinkedStack(int /*initialCapacity*/) : stackTop(nullptr), stackSize(0) {
    }

    /*!
     * \brief LinkedStack<T>::~LinkedStack
     */
    template <typename T>
    LinkedStack<T>::~LinkedStack() {
        while (stackTop != nullptr) {
            ChainNode<T>* nextNode = stackTop->next;
            delete stackTop;
            stackTop = nextNode;
        }
    }

    /*!
     * \brief LinkedStack<T>::empty
     * \return
     */
    template <typename T>
    bool LinkedStack<T>::empty() const {
        return stackSize == 0;
    }

    /*!
     * \brief LinkedStack<T>::size
     * \return
     */
    template <typename T>
    int LinkedStack<T>::size() const {
        return stackSize;
    }

    /*!
     * \brief LinkedStack<T>::top
     * \return
     */
    template <typename T>
    T& LinkedStack<T>::top() {
        return stackTop->element;
    }

    /*!
     * \brief LinkedStack<T>::pop
     */
    template <typename T>
    void LinkedStack<T>::pop() {
        if (stackSize == 0) {
            throw StackEmpty();
        }
        ChainNode<T>* nextNode = stackTop->next;
        delete stackTop;
        stackTop = nextNode;
        --stackSize;
    }

    /*!
     * \brief LinkedStack<T>::push
     * \param theElement
     */
    template <typename T>
    void LinkedStack<T>::push(const T& theElement) {
        ChainNode<T>* currentNode = new ChainNode<T>(theElement, stackTop);
        stackTop = currentNode;
        ++stackSize;
    }

}  // namespace DSAA
#endif  // LINKEDSTACK_HPP
