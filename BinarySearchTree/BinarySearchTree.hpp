#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

#include "bits/stdc++.h"

namespace GP {

    template <typename Comparable>
    class BinarySearchTree {
      public:
        BinarySearchTree();
        BinarySearchTree(const BinarySearchTree &rhs);
        BinarySearchTree(BinarySearchTree &&rhs);
        ~BinarySearchTree();

        // ADT
        const Comparable &findMin() const;         // done
        const Comparable &findMax() const;         // done
        bool contains(const Comparable &x) const;  // done
        bool isEmpty() const;                      // done
        void printTree(std::ostream &out = std::cout) const;

        void makeEmpty();
        void insert(const Comparable &x);  // done
        void insert(Comparable &&x);       // done
        void remove(const Comparable &x);  // done

        BinarySearchTree &operator=(const BinarySearchTree &rhs);
        BinarySearchTree &operator=(BinarySearchTree &&rhs);

      private:
        struct BinaryNode;

        BinaryNode *root;
        void insert(const Comparable &x, BinaryNode *&subtree);
        void insert(Comparable &&x, BinaryNode *&subtree);
        void remove(const Comparable &x, BinaryNode *&subtree);
        BinaryNode *findMin(BinaryNode *subtree) const;
        BinaryNode *findMax(BinaryNode *subtree) const;
        bool contains(const Comparable &x, BinaryNode *t) const;
        void makeEmpty(BinaryNode *&subtree);
        void printTree(BinaryNode *subtree, std::ostream &out) const;
        BinaryNode *clone(BinaryNode *subtree) const;

        struct BinaryNode {
            BinaryNode(const Comparable &theElement, BinaryNode *leftSubtree, BinaryNode *rightSubTree);
            BinaryNode(Comparable &&theElement, BinaryNode *leftSubtree, BinaryNode *rightSubtree);

            Comparable element;
            BinaryNode *left;
            BinaryNode *right;
        };
    };

    template <typename Comparable>
    inline BinarySearchTree<Comparable>::BinaryNode::BinaryNode(const Comparable &theElement, BinaryNode *leftSubtree,
                                                                BinaryNode *rightSubTree)
        : element{theElement}, left{leftSubtree}, right{rightSubTree} {
    }

    template <typename Comparable>
    BinarySearchTree<Comparable>::BinaryNode::BinaryNode(Comparable &&theElement, BinaryNode *leftSubtree,
                                                         BinaryNode *rightSubtree)
        : element{std::move(theElement)}, left{leftSubtree}, right{rightSubtree} {
    }

    /*!
     * \brief BinarySearchTree<Comparable>::contains
     * \param x
     * \return
     */
    template <typename Comparable>
    bool BinarySearchTree<Comparable>::contains(const Comparable &x) const {
        return contains(x, root);
    }

    /*!
     * \brief BinarySearchTree<Comparable>::isEmpty
     * \return
     */
    template <typename Comparable>
    bool BinarySearchTree<Comparable>::isEmpty() const {
        return root == nullptr;
    }

    /*!
     * \brief BinarySearchTree<Comparable>::printTree
     * \param out
     */
    template <typename Comparable>
    void BinarySearchTree<Comparable>::printTree(std::ostream &out) const {
        printTree(root, out);
    }

    /*!
     * \brief BinarySearchTree<Comparable>::insert
     * \param x
     */
    template <typename Comparable>
    void BinarySearchTree<Comparable>::insert(const Comparable &x) {
        insert(x, root);
    }

    /*!
     * \brief BinarySearchTree<Comparable>::insert
     * \param x
     */
    template <typename Comparable>
    void BinarySearchTree<Comparable>::insert(Comparable &&x) {
        insert(x, root);
    }

    /*!
     * \brief BinarySearchTree<Comparable>::remove
     * \param x
     */
    template <typename Comparable>
    void BinarySearchTree<Comparable>::remove(const Comparable &x) {
        remove(x, root);
    }

    /*!
     * \brief BinarySearchTree<Comparable>::insert
     * \param x
     * \param subtree
     */
    template <typename Comparable>
    void BinarySearchTree<Comparable>::insert(const Comparable &x, BinaryNode *&subtree) {
        if (subtree == nullptr) {
            subtree = new BinaryNode{x, nullptr, nullptr};
        } else if (x < subtree->element) {
            insert(x, subtree->left);
        } else if (subtree->element < x) {
            insert(x, subtree->right);
        }
    }

    /*!
     * \brief BinarySearchTree<Comparable>::insert
     * \param x
     * \param subtree
     */
    template <typename Comparable>
    void BinarySearchTree<Comparable>::insert(Comparable &&x, BinaryNode *&subtree) {
        if (subtree == nullptr) {
            subtree = new BinaryNode{std::move(x), nullptr, nullptr};
        } else if (x < subtree->left) {
            insert(std::move(x), subtree->left);
        } else if (subtree->right < x) {
            insert(std::move(x), subtree->right);
        }
    }

    /*!
     * \brief BinarySearchTree<Comparable>::remove
     * \param x
     * \param subtree
     */
    template <typename Comparable>
    void BinarySearchTree<Comparable>::remove(const Comparable &x, BinaryNode *&subtree) {
        if (subtree == nullptr) {
            return;
        }

        if (x < subtree->element) {
            remove(x, subtree->left);
        } else if (subtree->element < x) {
            remove(x, subtree->right);
        } else if (subtree->left != nullptr && subtree->right != nullptr) {
            subtree->element = findMin(subtree->right)->element;
            remove(subtree->element, subtree->right);
        } else {
            BinaryNode *oldNode = subtree;
            subtree = (subtree->left != nullptr) ? subtree->left : subtree->right;
            delete oldNode;
        }
    }

    /*!
     * \brief BinarySearchTree<Comparable>::findMin
     * \return
     */
    template <typename Comparable>
    const Comparable &BinarySearchTree<Comparable>::findMin() const {
        if (isEmpty()) {
            throw std::runtime_error("");
        }
        return findMin(root)->element;
    }

    /*!
     * \brief BinarySearchTree<Comparable>::findMin
     * \param subtree
     * \return
     */
    template <typename Comparable>
    typename BinarySearchTree<Comparable>::BinaryNode *BinarySearchTree<Comparable>::findMin(
        BinarySearchTree::BinaryNode *subtree) const {
        if (subtree == nullptr) {
            return nullptr;
        }

        if (subtree->left == nullptr) {
            return subtree;
        }

        return findMin(subtree->left);
    }

    /*!
     * \brief BinarySearchTree<Comparable>::findMax
     * \return
     */
    template <typename Comparable>
    const Comparable &BinarySearchTree<Comparable>::findMax() const {
        if (isEmpty()) {
            throw std::runtime_error("");
        }
        findMax(root)->element;
    }

    /*!
     * \brief BinarySearchTree<Comparable>::findMax
     * \param subtree
     * \return
     */
    template <typename Comparable>
    typename BinarySearchTree<Comparable>::BinaryNode *BinarySearchTree<Comparable>::findMax(
        BinaryNode *subtree) const {
        if (subtree != nullptr) {
            while (subtree->right != nullptr) {
                subtree = subtree->right;
            }
        }
        return subtree;
    }

    /*!
     * \brief BinarySearchTree<Comparable>::contains
     * \param x
     * \param t
     * \return
     */
    template <typename Comparable>
    bool BinarySearchTree<Comparable>::contains(const Comparable &x, BinaryNode *t) const {
        if (t == nullptr) {
            return false;
        } else if (x < t->element) {
            return contains(x, t->left);
        } else if (t->element < x) {
            return contains(x, t->right);
        } else {
            return true;
        }
        return false;
    }

    /*!
     * \brief BinarySearchTree<Comparable>::printTree
     * \param subtree
     * \param out
     */
    template <typename Comparable>
    void BinarySearchTree<Comparable>::printTree(BinaryNode *subtree, std::ostream &out) const {
        if (subtree != nullptr) {
            printTree(subtree->left, out);
            out << subtree->element << std::endl;
            printTree(subtree->right, out);
        }
    }

}  // namespace GP

#endif  // BINARYSEARCHTREE_HPP
