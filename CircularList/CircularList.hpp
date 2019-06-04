#ifndef CIRCULARLIST_HPP
#define CIRCULARLIST_HPP

#include "bits/stdc++.h"

#include "ChainNode.hpp"
#include "Exception.hpp"

namespace DSAA {

    template <typename T>
    class CircularList {
      public:
        CircularList();

        // ADT
        int size() const;
        int indexOf(const T &theElement) const;
        void insert(int theIndex, const T &theElement);
        void output(std::ostream &out) const;

      private:
        void checkIndex(int theIndex) const;

        ChainNode<T> *headerNode;
        int listSize;
    };

    /*!
     * \brief CircularList<T>::CircularList
     */
    template <typename T>
    inline CircularList<T>::CircularList() {
        headerNode = new ChainNode<T>();
        headerNode->next = headerNode;

        listSize = 0;
    }

    /*!
     * \brief CircularList<T>::size
     * \return
     */
    template <typename T>
    int CircularList<T>::size() const {
        return listSize;
    }

    /*!
     * \brief CircularList<T>::indexOf
     * \param theElement
     * \return
     */
    template <typename T>
    int CircularList<T>::indexOf(const T &theElement) const {
        headerNode->element = theElement;

        ChainNode<T> *currentNode = headerNode->next;
        int index = 0;
        while (currentNode->element != theElement) {
            currentNode = currentNode->next;
            ++index;
        }

        if (currentNode == headerNode) {
            return -1;
        }

        return index;
    }

    /*!
     * \brief CircularList<T>::insert
     * \param theIndex
     * \param theElement
     */
    template <typename T>
    void CircularList<T>::insert(int theIndex, const T &theElement) {
        if (theIndex < 0 || theIndex > listSize) {
            std::ostringstream s;
            s << "index = " << theIndex << " size = " << listSize;
            throw IllegalIndex(s.str());
        }

        ChainNode<T> *currentNode = headerNode;
        for (int i = 0; i != theIndex; ++i) {
            currentNode = currentNode->next;
        }
        currentNode->next = new ChainNode<T>(theElement, currentNode->next);

        ++listSize;
    }

    /*!
     * \brief CircularList<T>::output
     * \param out
     */
    template <typename T>
    void CircularList<T>::output(std::ostream &out) const {
        for (ChainNode<T> *currentNode = headerNode->next; currentNode != headerNode; currentNode = currentNode->next) {
            out << currentNode->element << "   ";
        }
    }

    /*!
     * \brief CircularList<T>::checkIndex
     * \param theIndex
     */
    template <typename T>
    void CircularList<T>::checkIndex(int theIndex) const {
        if (theIndex < 0 || theIndex >= listSize) {
            std::stringstream s;
            s << "index = " << theIndex << " size = " << listSize;
            throw IllegalIndex(s.str());
        }
    }

    /*!
     * \brief operator <<
     * \param out
     * \param circularList
     * \return
     */
    template <typename T>
    std::ostream &operator<<(std::ostream &out, const CircularList<T> &circularList) {
        circularList.output(out);
        return out;
    }
}  // namespace DSAA

#endif  // CIRCULARLIST_HPP
