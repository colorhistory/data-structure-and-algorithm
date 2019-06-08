#ifndef ARRAYQUEUE_HPP
#define ARRAYQUEUE_HPP

#include "bits/stdc++.h"

#include "Exception.hpp"
#include "Queue.hpp"

namespace DSAA {

    template <typename T>
    class ArrayQueue : public Queue<T> {
      public:
        ArrayQueue(int initialCapacity = 10);
        ~ArrayQueue();

        bool empty() const;
        int size() const;

        T& front();
        T& back();

        void pop();
        void push(const T& theElement);

      private:
        int theFront;
        int theBack;
        int arrayLength;
        T* queue;
    };

    /*!
     * \brief ArrayQueue<T>::ArrayQueue
     * \param initialCapacity
     */
    template <typename T>
    ArrayQueue<T>::ArrayQueue(int initialCapacity) {
        if (initialCapacity < 1) {
            std::ostringstream s;
            s << "Initial capacity = " << initialCapacity << " must be > 0";
            throw IllegalParameterValue(s.str());
        }

        theFront = 0;
        theBack = 0;
        arrayLength = initialCapacity;
        queue = new T[arrayLength];
    }

    /*!
     * \brief ArrayQueue<T>::~ArrayQueue
     */
    template <typename T>
    ArrayQueue<T>::~ArrayQueue() {
        delete[] queue;
    }

    /*!
     * \brief ArrayQueue<T>::empty
     * \return
     */
    template <typename T>
    bool ArrayQueue<T>::empty() const {
        return theFront == theBack;
    }

    /*!
     * \brief ArrayQueue<T>::size
     * \return
     */
    template <typename T>
    int ArrayQueue<T>::size() const {
        return (theBack - theFront + arrayLength) % arrayLength;
    }

    /*!
     * \brief ArrayQueue<T>::front
     * \return
     */
    template <typename T>
    T& ArrayQueue<T>::front() {
        if (theFront == theBack) {
            throw QueueEmpty();
        }
        return queue[(theFront + 1) % arrayLength];
    }

    /*!
     * \brief ArrayQueue<T>::back
     * \return
     */
    template <typename T>
    T& ArrayQueue<T>::back() {
        if (theFront == theBack) {
            throw QueueEmpty();
        }

        return queue[theBack];
    }

    /*!
     * \brief ArrayQueue<T>::pop
     */
    template <typename T>
    void ArrayQueue<T>::pop() {
        if (theFront == theBack) {
            throw QueueEmpty();
        }
        theFront = (theFront + 1) % arrayLength;
        queue[theFront].~T();
    }

    /*!
     * \brief ArrayQueue<T>::push
     */
    template <typename T>
    void ArrayQueue<T>::push(const T& theElement) {
        if (arrayLength - size() == 1) {
            T* newQueue = new T[2 * arrayLength];

            int start = (theFront + 1) % arrayLength;
            if (start < 2) {
                std::copy(queue + start, queue + start + arrayLength - 1, newQueue);
            } else {
                std::copy(queue + start, queue + arrayLength, newQueue);
                std::copy(queue, queue + theBack + 1, newQueue + arrayLength - start);
            }

            theFront = 2 * arrayLength - 1;
            theBack = arrayLength - 2;
            arrayLength *= 2;
            queue = newQueue;
        }

        theBack = (theBack + 1) % arrayLength;
        queue[theBack] = theElement;
    }

}  // namespace DSAA

#endif  // ARRAYQUEUE_HPP
