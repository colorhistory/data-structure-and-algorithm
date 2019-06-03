#ifndef EXTENDEDCHAIN_HPP
#define EXTENDEDCHAIN_HPP

#include "bits/stdc++.h"

#include "BaseChain.hpp"
#include "ChainNode.hpp"
#include "Exception.hpp"
#include "ExtendedLinearList.hpp"
#include "changeLength1D.hpp"

namespace DSAA {

    template <typename T>
    class ExtendedChain : public ExtendedLinearList<T>, public ChainWithIterator<T> {
      public:
        ExtendedChain(int initialCapacity = 10);
        ExtendedChain(const ExtendedChain<T> &chain);

        // ADT
        bool empty() const;
        int size() const;

        const T &get(int theIndex) const;
        int indexOf(const T &theElement) const;

        void erase(int theIndex);
        void insert(int theIndex, const T &theElement);
        void clear();
        void push_back(const T &theElement);

        void output(std::ostream &out) const;
        void zero();

      private:
        ChainNode<T> *lastNode;
    };

    /*!
     * \brief ExtendedChain<T>::ExtendedChain
     * \param initialCapacity
     */
    template <typename T>
    ExtendedChain<T>::ExtendedChain(int initialCapacity) : ChainWithIterator<T>(initialCapacity) {
    }

    /*!
     * \brief ExtendedChain<T>::ExtendedChain
     * \param chain
     */
    template <typename T>
    ExtendedChain<T>::ExtendedChain(const ExtendedChain<T> &chain) : ChainWithIterator<T>(chain) {
    }

    /*!
     * \brief ExtendedChain<T>::empty
     * \return
     */
    template <typename T>
    bool ExtendedChain<T>::empty() const {
        return ChainWithIterator<T>::empty();
    }

    /*!
     * \brief ExtendedChain<T>::size
     * \return
     */
    template <typename T>
    int ExtendedChain<T>::size() const {
        return ChainWithIterator<T>::size();
    }

    /*!
     * \brief ExtendedChain<T>::get
     * \param theIndex
     * \return
     */
    template <typename T>
    const T &ExtendedChain<T>::get(int theIndex) const {
        return ChainWithIterator<T>::get(theIndex);
    }

    /*!
     * \brief ExtendedChain<T>::indexOf
     * \param theElement
     * \return
     */
    template <typename T>
    int ExtendedChain<T>::indexOf(const T &theElement) const {
        return ChainWithIterator<T>::indexOf(theElement);
    }

    /*!
     * \brief ExtendedChain<T>::erase
     * \param theIndex
     */
    template <typename T>
    void ExtendedChain<T>::erase(int theIndex) {
        checkIndex(theIndex);

        ChainNode<T> *deleteNode;
        if (theIndex == 0) {
            deleteNode = firstNode;
            firstNode = firstNode->next;
        } else {
            ChainNode<T> *currentNode = firstNode;
            for (int i = 0; i != theIndex - 1; ++i) {
                currentNode = currentNode->next;
            }
            deleteNode = currentNode->next;
            currentNode->next = currentNode->next->next;

            if (deleteNode == lastNode) {
                lastNode = currentNode;
            }
            --listSize;
            delete deleteNode;
        }
    }

    /*!
     * \brief ExtendedChain<T>::insert
     * \param theIndex
     * \param theElement
     */
    template <typename T>
    void ExtendedChain<T>::insert(int theIndex, const T &theElement) {
        if (theIndex < 0 || theIndex > listSize) {
            std::ostringstream s;
            s << "index = " << theIndex << " size = " << listSize;
            throw IllegalIndex(s.str());
        }

        if (theIndex == 0) {
            firstNode = new ChainNode<T>(theElement, firstNode);
            if (listSize == 0)
                lastNode = firstNode;
        } else {
            ChainNode<T> *p = firstNode;
            for (int i = 0; i < theIndex - 1; i++) p = p->next;

            p->next = new ChainNode<T>(theElement, p->next);
            if (listSize == theIndex)
                lastNode = p->next;
        }
        listSize++;
    }

    /*!
     * \brief ExtendedChain<T>::clear
     */
    template <typename T>
    void ExtendedChain<T>::clear() {
        while (firstNode != nullptr) {
            ChainNode<T> *nextNode = firstNode->next;
            delete firstNode;
            firstNode = nextNode;
        }
        listSize = 0;
    }

    /*!
     * \brief ExtendedChain<T>::push_back
     * \param theElement
     */
    template <typename T>
    void ExtendedChain<T>::push_back(const T &theElement) {
        ChainNode<T> *newNode = new ChainNode<T>(theElement, nullptr);
        if (firstNode == nullptr) {
            firstNode = lastNode = newNode;
        } else {
            lastNode->next = newNode;
            lastNode = newNode;
        }
        ++listSize;
    }

    /*!
     * \brief ExtendedChain<T>::output
     * \param out
     */
    template <typename T>
    void ExtendedChain<T>::output(std::ostream &out) const {
        ChainWithIterator<T>::output(out);
    }

    /*!
     * \brief ExtendedChain<T>::zero
     */
    template <typename T>
    void ExtendedChain<T>::zero() {
        firstNode = nullptr;
        listSize = 0;
    }
}  // namespace DSAA
#endif  // EXTENDEDCHAIN_HPP
