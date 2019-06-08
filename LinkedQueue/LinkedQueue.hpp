#ifndef LINKEDQUEUE_HPP
#define LINKEDQUEUE_HPP

#include "bits/stdc++.h"

#include "ChainNode.hpp"
#include "Exception.hpp"
#include "Queue.hpp"

namespace DSAA {

    template <typename T>
    class LinkedQueue : public Queue<T> {
      public:
        LinkedQueue(int initialCapacity = 10);
        ~LinkedQueue();

        // ADT
        bool empty() const;
        int size() const;

        T& front();
        T& back();

        void pop();
        void push(const T&);

      private:
        ChainNode<T>* queueFront;
        ChainNode<T>* queueBack;
        int queueSize;
    };

    /*!
     * \brief LinkedQueue<T>::LinkedQueue
     * \param initialCapacity
     */
    template <typename T>
    LinkedQueue<T>::LinkedQueue(int /*initialCapacity*/) {
        queueFront = nullptr;
        queueSize = 0;
    }

    /*!
     * \brief LinkedQueue<T>::~LinkedQueue
     */
    template <typename T>
    LinkedQueue<T>::~LinkedQueue() {
        while (queueFront != nullptr) {
            ChainNode<T>* nextNode = queueFront->next;
            delete nextNode;
            queueFront = nextNode;
        }
    }

    /*!
     * \brief LinkedQueue<T>::empty
     * \return
     */
    template <typename T>
    bool LinkedQueue<T>::empty() const {
        return queueSize == 0;
    }

    /*!
     * \brief LinkedQueue<T>::size
     * \return
     */
    template <typename T>
    int LinkedQueue<T>::size() const {
        return queueSize;
    }

    /*!
     * \brief LinkedQueue<T>::front
     * \return
     */
    template <typename T>
    T& LinkedQueue<T>::front() {
        if (queueSize == 0) {
            throw QueueEmpty();
        }
        return queueFront->element;
    }

    /*!
     * \brief LinkedQueue<T>::back
     * \return
     */
    template <typename T>
    T& LinkedQueue<T>::back() {
        if (queueSize == 0) {
            throw QueueEmpty();
        }

        return queueBack->element;
    }

    /*!
     * \brief LinkedQueue<T>::pop
     */
    template <typename T>
    void LinkedQueue<T>::pop() {
        if (queueFront == nullptr) {
            throw QueueEmpty();
        }

        ChainNode<T>* nextNode = queueFront->next;
        delete queueFront;
        queueFront = nextNode;
        --queueSize;
    }

    /*!
     * \brief LinkedQueue<T>::push
     */
    template <typename T>
    void LinkedQueue<T>::push(const T& theElement) {
        ChainNode<T>* newNode = new ChainNode<T>(theElement, nullptr);

        if (queueSize == 0) {
            queueFront = newNode;
        } else {
            queueBack->next = newNode;
        }
        queueBack = newNode;

        ++queueSize;
    }

}  // namespace DSAA
#endif  // LINKEDQUEUE_HPP
