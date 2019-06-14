#ifndef MAXHEAP_HPP
#define MAXHEAP_HPP

#include "bits/stdc++.h"

#include "Exception.hpp"
#include "changeLength1D.hpp"

#include "MaxPriority.hpp"

namespace DSAA {

    template <typename T>
    class MaxHeap : public MaxPriorityQueue<T> {
      public:
        MaxHeap(int initialCapacity = 10);
        ~MaxHeap();

        // ADT
        bool empty() const;
        int size() const;

        const T& top();

        void pop();
        void push(const T& theElement);
        void initialize(T*, int);
        void deactivateArray();
        void output(std::ostream& out) const;

      private:
        int heapSize;
        int arrayLength;
        T* heap;
    };

    /*!
     * \brief MaxHeap<T>::MaxHeap
     * \param initialCapacity
     */
    template <typename T>
    MaxHeap<T>::MaxHeap(int initialCapacity) {
        if (initialCapacity < 1) {
            std::ostringstream s;
            s << "Initial capacity = " << initialCapacity << " must be > 0";
            throw IllegalParameterValue(s.str());
        }

        heapSize = 0;
        arrayLength = initialCapacity + 1;
        heap = new T[arrayLength];
    }

    /*!
     * \brief MaxHeap<T>::~MaxHeap
     */
    template <typename T>
    MaxHeap<T>::~MaxHeap() {
        delete[] heap;
    }

    /*!
     * \brief MaxHeap<T>::empty
     * \return
     */
    template <typename T>
    bool MaxHeap<T>::empty() const {
        return heapSize == 0;
    }

    /*!
     * \brief MaxHeap<T>::size
     * \return
     */
    template <typename T>
    int MaxHeap<T>::size() const {
        return heapSize;
    }

    /*!
     * \brief MaxHeap<T>::top
     * \return
     */
    template <typename T>
    const T& MaxHeap<T>::top() {
        if (heapSize == 0) {
            throw QueueEmpty();
        }
        return heap[1];
    }

    /*!
     * \brief MaxHeap<T>::pop
     */
    template <typename T>
    void MaxHeap<T>::pop() {
        if (heapSize == 0) {
            throw QueueEmpty();
        }

        /*! delete the max element */
        heap[1].~T();

        /*! remove last element and reheapify */
        T lastElement = heap[heapSize--];

        /*! find place for lastElement starting at root */
        int currentNode = 1, child = 2;
        while (child <= heapSize) {
            // heap[child] should be larger child of currentNode
            if (child < heapSize && heap[child] < heap[child + 1]) {
                ++child;
            }
            /* can we put lastElement in heap[currentNode] */
            if (lastElement >= heap[child]) {
                break;  // yes
            }

            // no
            heap[currentNode] = heap[child];
            currentNode = child;
            child *= 2;
        }

        heap[currentNode] = lastElement;
    }

    /*!
     * \brief MaxHeap<T>::push
     * \param theElement
     */
    template <typename T>
    void MaxHeap<T>::push(const T& theElement) {
        // increase array length is necessary
        if (heapSize == arrayLength - 1) {
            changeLength1D(heap, arrayLength, 2 * arrayLength);
            arrayLength *= 2;
        }

        // find place for theElement currentNode starts at new leaf and moves up tree
        int currentNode = ++heapSize;
        while (currentNode != 1 && heap[currentNode / 2] < theElement) {
            // cannot put theElement in heap[currentNode]
            heap[currentNode] = heap[currentNode / 2];  // move element down
            currentNode /= 2;                           // move to parent
        }

        heap[currentNode] = theElement;
    }

    /*!
     * \brief MaxHeap<T>::initialize
     * \param theHeap
     * \param theSize
     */
    template <typename T>
    void MaxHeap<T>::initialize(T* theHeap, int theSize) {
        // initialize max heap to element array theHeap[1:theSize]
        delete[] heap;
        heap = theHeap;
        heapSize = theSize;

        for (int root = heapSize / 2; root >= 1; --root) {
            T rootElement = heap[root];

            int child = 2 * root;
            while (child <= heapSize) {
                if (child < heapSize && heap[child] < heap[child + 1]) {
                    ++child;
                }

                if (rootElement >= heap[child]) {
                    break;
                }

                heap[child / 2] = heap[child];
                child *= 2;
            }
            heap[child / 2] = rootElement;
        }
    }

    /*!
     * \brief MaxHeap<T>::deactivateArray
     */
    template <typename T>
    void MaxHeap<T>::deactivateArray() {
        heap = nullptr;
        arrayLength = heapSize = 0;
    }

    /*!
     * \brief MaxHeap<T>::output
     * \param out
     */
    template <typename T>
    void MaxHeap<T>::output(std::ostream& out) const {
        std::copy(heap + 1, heap + heapSize + 1, std::ostream_iterator<T>(out, "   "));
    }

    /*!
     * \brief operator <<
     * \param out
     * \param x
     * \return
     */
    template <typename T>
    std::ostream& operator<<(std::ostream& out, const MaxHeap<T>& x) {
        x.output(out);
        return out;
    }

}  // namespace DSAA

#endif  // MAXHEAP_HPP
