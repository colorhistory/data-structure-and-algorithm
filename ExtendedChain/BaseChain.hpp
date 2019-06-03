#ifndef CHAIN_HPP
#define CHAIN_HPP

#include "bits/stdc++.h"

#include "ChainNode.hpp"
#include "Exception.hpp"
#include "LinearList.hpp"
#include "changeLength1D.hpp"

namespace DSAA {

    template <typename T>
    class ChainWithIterator : public LinearList<T> {
      public:
        ChainWithIterator(int initialCapacity = 10);
        ChainWithIterator(const ChainWithIterator<T>& theChain);
        ~ChainWithIterator();

        // ADT
        bool empty() const;
        int size() const;

        T& get(int theIndex) const;
        int indexOf(const T& theElement) const;

        void erase(int theIndex);
        void insert(int theIndex, const T& theElement);

        void output(std::ostream& out) const;

        class iterator;
        iterator begin();
        iterator end();

        class iterator {
          public:
            using iterator_category = std::forward_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = T*;
            using reference = T&;

            iterator(ChainNode<T>* theNode = nullptr);

            T& operator*() const;
            T* operator->() const;

            iterator& operator++();
            iterator operator++(int);

            bool operator==(const iterator rhs) const;
            bool operator!=(const iterator rhs) const;

          private:
            ChainNode<T>* node;
        };

      protected:
        virtual void checkIndex(int theIndex) const;

        int listSize;
        ChainNode<T>* firstNode;
    };

    /*!
     * \brief ChainWithIterator<T>::ChainWithIterator
     * \param initialCapacity
     */
    template <typename T>
    inline ChainWithIterator<T>::ChainWithIterator(int initialCapacity) {
        if (initialCapacity < 1) {
            std::stringstream s;
            s << "The initialCapacity " << initialCapacity << " must be > 0";
            throw IllegalParameterValue(s.str());
        }

        listSize = 0;
        firstNode = nullptr;
    }

    /*!
     * \brief ChainWithIterator<T>::ChainWithIterator
     * \param theChain
     */
    template <typename T>
    inline ChainWithIterator<T>::ChainWithIterator(const ChainWithIterator<T>& theChain) {
        listSize = theChain.listSize;

        /*! the chain is empty */
        if (listSize == 0) {
            firstNode = nullptr;
            return;
        }

        /*! the chain is not empty */
        ChainNode<T>* sourceNode = theChain.firstNode;
        firstNode = new ChainNode<T>(sourceNode->element);

        sourceNode = sourceNode->next;
        ChainNode<T>* targetNode = firstNode;

        /*! copy elements to destination */
        while (sourceNode != nullptr) {
            targetNode->next = new ChainNode<T>(sourceNode->element);
            targetNode = targetNode->next;
            sourceNode = sourceNode->next;
        }

        targetNode->next = nullptr;
    }

    /*!
     * \brief Chain<T>::~Chain
     */
    template <typename T>
    inline ChainWithIterator<T>::~ChainWithIterator() {
        while (firstNode != nullptr) {
            ChainNode<T>* nextNode = firstNode->next;
            delete firstNode;
            firstNode = nextNode;
        }
    }

    /*!
     * \brief ChainWithIterator<T>::empty
     * \return
     */
    template <typename T>
    inline bool ChainWithIterator<T>::empty() const {
        return listSize == 0;
    }

    /*!
     * \brief ChainWithIterator<T>::size
     * \return
     */
    template <typename T>
    inline int ChainWithIterator<T>::size() const {
        return listSize;
    }

    /*!
     * \brief ChainWithIterator<T>::get
     * \param theIndex
     * \return
     */
    template <typename T>
    inline T& ChainWithIterator<T>::get(int theIndex) const {
        checkIndex(theIndex);

        ChainNode<T>* currentNode = firstNode;
        for (int i = 0; i != theIndex; ++i) {
            currentNode = currentNode->next;
        }
        return currentNode->element;
    }

    /*!
     * \brief ChainWithIterator<T>::indexOf
     * \param theElement
     * \return
     */
    template <typename T>
    inline int ChainWithIterator<T>::indexOf(const T& theElement) const {
        ChainNode<T>* currentNode = firstNode;
        for (int i = 0; i != listSize; ++i) {
            if (currentNode->element == theElement) {
                return i;
            }
            currentNode = currentNode->next;
        }
        return -1;
    }

    /*!
     * \brief ChainWithIterator<T>::erase
     * \param theIndex
     */
    template <typename T>
    inline void ChainWithIterator<T>::erase(int theIndex) {
        checkIndex(theIndex);

        ChainNode<T>* deleteNode;
        if (theIndex == 0) {
            deleteNode = firstNode;
            firstNode = firstNode->next;
        } else {
            ChainNode<T>* currentNode = firstNode;
            for (int i = 0; i != theIndex - 1; ++i) {
                currentNode = currentNode->next;
            }
            deleteNode = currentNode->next;
            currentNode->next = currentNode->next->next;
        }
        --listSize;
        delete deleteNode;
    }

    /*!
     * \brief ChainWithIterator<T>::insert
     * \param theIndex
     * \param theElement
     */
    template <typename T>
    inline void ChainWithIterator<T>::insert(int theIndex, const T& theElement) {
        if (theIndex < 0 || theIndex > listSize) {
            std::ostringstream s;
            s << "index = " << theIndex << " size = " << listSize;
            throw IllegalIndex(s.str());
        }

        if (theIndex == 0) {
            firstNode = new ChainNode<T>(theElement, firstNode);
        } else {
            ChainNode<T>* p = firstNode;
            for (int i = 0; i != theIndex - 1; ++i) {
                p = p->next;
            }
            p->next = new ChainNode<T>(theElement, p->next);
        }
        ++listSize;
    }

    /*!
     * \brief ChainWithIterator<T>::output
     */
    template <typename T>
    inline void ChainWithIterator<T>::output(std::ostream& out) const {
        for (ChainNode<T>* currentNode = firstNode; currentNode != nullptr; currentNode = currentNode->next) {
            out << currentNode->element << "   ";
        }
    }

    /*!
     * \brief ChainWithIterator<T>::begin
     * \return
     */
    template <typename T>
    inline typename ChainWithIterator<T>::iterator ChainWithIterator<T>::begin() {
        return iterator(firstNode);
    }

    /*!
     * \brief ChainWithIterator<T>::end
     * \return
     */
    template <typename T>
    inline typename ChainWithIterator<T>::iterator ChainWithIterator<T>::end() {
        return iterator(nullptr);
    }

    /*!
     * \brief ChainWithIterator<T>::checkIndex
     * \param theIndex
     */
    template <typename T>
    inline void ChainWithIterator<T>::checkIndex(int theIndex) const {
        if (theIndex < 0 || theIndex >= listSize) {
            std::stringstream s;
            s << "The index = " << theIndex << " Size = " << listSize;
            throw IllegalIndex(s.str());
        }
    }

    /*!
     * \brief operator <<
     * \param out
     * \param theChain
     * \return
     */
    template <typename T>
    inline std::ostream& operator<<(std::ostream& out, const ChainWithIterator<T>& theChain) {
        theChain.output(out);
        return out;
    }

    /*!
     * \brief ChainWithIterator<T>::iterator::iterator
     * \param theNode
     */
    template <typename T>
    inline ChainWithIterator<T>::iterator::iterator(ChainNode<T>* theNode) {
        node = theNode;
    }

    /*!
     * \brief ChainWithIterator<T>::iterator::operator *
     * \return
     */
    template <typename T>
    inline T& ChainWithIterator<T>::iterator::operator*() const {
        return node->element;
    }

    /*!
     * \brief ChainWithIterator<T>::iterator::operator ->
     * \return
     */
    template <typename T>
    inline T* ChainWithIterator<T>::iterator::operator->() const {
        return &(node->element);
    }

    /*!
     * \brief ChainWithIterator<T>::iterator::operator ++
     * \return
     */
    template <typename T>
    inline typename ChainWithIterator<T>::iterator& ChainWithIterator<T>::iterator::operator++() {
        node = node->next;
        return *this;
    }

    /*!
     * \brief ChainWithIterator<T>::iterator::operator ++
     * \return
     */
    template <typename T>
    inline typename ChainWithIterator<T>::iterator ChainWithIterator<T>::iterator::operator++(int) {
        iterator old = *this;
        node = node->next;
        return old;
    }

    /*!
     * \brief ChainWithIterator<T>::iterator::operator ==
     * \param rhs
     * \return
     */
    template <typename T>
    inline bool ChainWithIterator<T>::iterator::operator==(const ChainWithIterator<T>::iterator rhs) const {
        return node == rhs.node;
    }

    /*!
     * \brief ChainWithIterator<T>::iterator::operator !=
     * \param rhs
     * \return
     */
    template <typename T>
    inline bool ChainWithIterator<T>::iterator::operator!=(const ChainWithIterator<T>::iterator rhs) const {
        return node != rhs.node;
    }

}  // namespace DSAA

#endif  // CHAIN_HPP
