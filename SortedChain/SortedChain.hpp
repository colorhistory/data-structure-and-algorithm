#ifndef SORTEDCHAIN_HPP
#define SORTEDCHAIN_HPP

#include "bits/stdc++.h"

#include "ChainNode.hpp"
#include "Dictionary.hpp"
#include "Exception.hpp"
#include "PairNode.hpp"

namespace DSAA {

    template <typename Key, typename Val>
    class SortedChain : public Dictionary<Key, Val> {
      public:
        SortedChain();
        ~SortedChain();

        // ADT
        virtual bool empty() const override;
        virtual int size() const override;
        virtual PairNode<const Key, Val> *find(const Key &key) const override;
        virtual void erase(const Key &key) override;
        virtual void insert(const PairNode<const Key, Val> &element) override;

        void output(std::ostream &out) const;

      private:
        PairNode<Key, Val> *firstNode;
        int dSize;
    };

    /*!
     * \brief SortedChain<Key, Val>::SortedChain
     */
    template <typename Key, typename Val>
    SortedChain<Key, Val>::SortedChain() {
        firstNode = nullptr;
        dSize = 0;
    }

    template <typename Key, typename Val>
    SortedChain<Key, Val>::~SortedChain() {
        while (firstNode != nullptr) {
            PairNode<Key, Val> *nextNode = firstNode->next;
            delete firstNode;
            firstNode = nextNode;
        }
    }

    /*!
     * \brief SortedChain<Key, Val>::empty
     * \return
     */
    template <typename Key, typename Val>
    bool SortedChain<Key, Val>::empty() const {
        return dSize == 0;
    }

    /*!
     * \brief SortedChain<Key, Val>::size
     * \return
     */
    template <typename Key, typename Val>
    int SortedChain<Key, Val>::size() const {
        return dSize;
    }

    /*!
     * \brief SortedChain<Key, Val>::find
     * \param key
     * \return
     */
    template <typename Key, typename Val>
    PairNode<const Key, Val> *SortedChain<Key, Val>::find(const Key &key) const {
        PairNode<Key, Val> *currentNode = firstNode;

        while (currentNode != nullptr && currentNode->element.first != key) {
            currentNode = currentNode->next;
        }

        if (currentNode != nullptr && currentNode->element.first == key) {
            return &currentNode->element;
        }

        return nullptr;
    }

    /*!
     * \brief SortedChain<Key, Val>::erase
     * \param key
     */
    template <typename Key, typename Val>
    void SortedChain<Key, Val>::erase(const Key &key) {
        PairNode<Key, Val> *p = firstNode;
        PairNode<Key, Val> *tp = nullptr;

        while (p != nullptr && p->element.first < key) {
            tp = p;
            p = p->next;
        }

        if (p != nullptr && p->element.first == key) {
            if (tp == nullptr) {
                firstNode = p->next;
            } else {
                tp->next = p->next;
            }

            delete p;
            --dSize;
        }
    }

    /*!
     * \brief SortedChain<Key, Val>::insert
     * \param element
     */
    template <typename Key, typename Val>
    void SortedChain<Key, Val>::insert(const PairNode<const Key, Val> &element) {
        PairNode<Key, Val> *p = firstNode, *tp = NULL;

        while (p != nullptr && p->element.first < element.first) {
            tp = p;
            p = p->next;
        }

        if (p != nullptr && p->element.first == element.first) {  // replace old value
            p->element.second = element.second;
            return;
        }

        PairNode<Key, Val> *newNode = new PairNode<Key, Val>(element, p);

        if (tp == nullptr) {
            firstNode = newNode;
        } else {
            tp->next = newNode;
        }

        dSize++;
        return;
    }

    /*!
     * \brief SortedChain<Key, Val>::output
     * \param out
     */
    template <typename Key, typename Val>
    void SortedChain<Key, Val>::output(std::ostream &out) const {
        for (PairNode<Key, Val> *currentNode = firstNode; currentNode != nullptr; currentNode = currentNode->next) {
            out << currentNode->element.first << "   " << currentNode->element.second << "   ";
        }
    }

    /*!
     * \brief operator <<
     * \param out
     * \param x
     * \return
     */
    template <typename Key, typename Val>
    std::ostream &operator<<(std::ostream &out, const SortedChain<Key, Val> &x) {
        x.output(out);
        return out;
    }

}  // namespace DSAA

#endif  // SORTEDCHAIN_HPP
