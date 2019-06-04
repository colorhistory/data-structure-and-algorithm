#ifndef CHAIN_HPP
#define CHAIN_HPP

#include "bits/stdc++.h"

#include "ChainNode.hpp"
#include "Exception.hpp"
#include "LinearList.hpp"
#include "changeLength1D.hpp"

namespace DSAA {

    template <typename T>
    class Chain : public LinearList<T> {
      public:
        Chain(int initialCapacity = 10);
        Chain(const Chain<T>& theChain);
        ~Chain();

        // ADT
        bool empty() const;
        int size() const;

        T& get(int theIndex) const;
        int indexOf(const T& theElement) const;

        void erase(int theIndex);
        void insert(int theIndex, const T& theElement);

        void output(std::ostream& out) const;

      protected:
        virtual void checkIndex(int theIndex) const;

        int listSize;
        ChainNode<T>* firstNode;
    };

    /*!
     * \brief Chain<T>::Chain
     * \param initialCapacity
     */
    template <typename T>
    Chain<T>::Chain(int initialCapacity) {
        if (initialCapacity < 1) {
            std::stringstream s;
            s << "The initialCapacity " << initialCapacity << " must be > 0";
            throw IllegalParameterValue(s.str());
        }

        listSize = 0;
        firstNode = nullptr;
    }

    /*!
     * \brief Chain<T>::Chain
     * \param theChain
     */
    template <typename T>
    Chain<T>::Chain(const Chain<T>& theChain) {
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
    Chain<T>::~Chain() {
        while (firstNode != nullptr) {
            ChainNode<T>* nextNode = firstNode->next;
            delete firstNode;
            firstNode = nextNode;
        }
    }

    /*!
     * \brief Chain<T>::empty
     * \return
     */
    template <typename T>
    bool Chain<T>::empty() const {
        return listSize == 0;
    }

    /*!
     * \brief Chain<T>::size
     * \return
     */
    template <typename T>
    int Chain<T>::size() const {
        return listSize;
    }

    /*!
     * \brief Chain<T>::get
     * \param theIndex
     * \return
     */
    template <typename T>
    T& Chain<T>::get(int theIndex) const {
        checkIndex(theIndex);

        ChainNode<T>* currentNode = firstNode;
        for (int i = 0; i != theIndex; ++i) {
            currentNode = currentNode->next;
        }
        return currentNode->element;
    }

    /*!
     * \brief Chain<T>::indexOf
     * \param theElement
     * \return
     */
    template <typename T>
    int Chain<T>::indexOf(const T& theElement) const {
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
     * \brief Chain<T>::erase
     * \param theIndex
     */
    template <typename T>
    void Chain<T>::erase(int theIndex) {
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
     * \brief Chain<T>::insert
     * \param theIndex
     * \param theElement
     */
    template <typename T>
    void Chain<T>::insert(int theIndex, const T& theElement) {
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
     * \brief Chain<T>::output
     */
    template <typename T>
    void Chain<T>::output(std::ostream& out) const {
        for (ChainNode<T>* currentNode = firstNode; currentNode != nullptr; currentNode = currentNode->next) {
            out << currentNode->element << "   ";
        }
    }

    /*!
     * \brief Chain<T>::checkIndex
     * \param theIndex
     */
    template <typename T>
    void Chain<T>::checkIndex(int theIndex) const {
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
    std::ostream& operator<<(std::ostream& out, const Chain<T>& theChain) {
        theChain.output(out);
        return out;
    }

}  // namespace DSAA

#endif  // CHAIN_HPP
