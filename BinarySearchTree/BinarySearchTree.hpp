#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

#include "bits/stdc++.h"

namespace DSAA {

    template <typename Comparable>
    class BinarySearchTree {
      public:
        BinarySearchTree();                             // done
        BinarySearchTree(const BinarySearchTree &rhs);  // done
        BinarySearchTree(BinarySearchTree &&rhs);       // done
        ~BinarySearchTree();                            // done

        // ADT
        const Comparable &findMin() const;                    // done
        const Comparable &findMax() const;                    // done
        bool contains(const Comparable &x) const;             // done
        bool isEmpty() const;                                 // done
        void printTree(std::ostream &out = std::cout) const;  // done

        void makeEmpty();                  // done
        void insert(const Comparable &x);  // done
        void insert(Comparable &&x);       // done
        void remove(const Comparable &x);  // done

        BinarySearchTree &operator=(const BinarySearchTree &rhs);  // done
        BinarySearchTree &operator=(BinarySearchTree &&rhs);       // done

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

    /*!
     * \brief BinarySearchTree<Comparable>::BinaryNode::BinaryNode
     * \param theElement
     * \param leftSubtree
     * \param rightSubTree
     */
    template <typename Comparable>
    inline BinarySearchTree<Comparable>::BinaryNode::BinaryNode(const Comparable &theElement,
                                                                BinaryNode *leftSubtree, BinaryNode *rightSubTree)
        : element{theElement}, left{leftSubtree}, right{rightSubTree} {
    }

    /*!
     * \brief BinarySearchTree<Comparable>::BinaryNode::BinaryNode
     * \param theElement
     * \param leftSubtree
     * \param rightSubtree
     */
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
     * \brief BinarySearchTree<Comparable>::makeEmpty
     */
    template <typename Comparable>
    void BinarySearchTree<Comparable>::makeEmpty() {
        makeEmpty(root);
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
     * \brief BinarySearchTree<Comparable>::operator =
     * \param rhs
     * \return
     */
    template <typename Comparable>
    BinarySearchTree<Comparable> &BinarySearchTree<Comparable>::operator=(const BinarySearchTree &rhs) {
        BinarySearchTree copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    /*!
     * \brief BinarySearchTree<Comparable>::operator =
     * \param rhs
     * \return
     */
    template <typename Comparable>
    BinarySearchTree<Comparable> &BinarySearchTree<Comparable>::operator=(BinarySearchTree &&rhs) {
        std::swap(root, rhs.root);
        return *this;
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
     * \brief BinarySearchTree<Comparable>::BinarySearchTree
     */
    template <typename Comparable>
    BinarySearchTree<Comparable>::BinarySearchTree() : root{nullptr} {
    }

    /*!
     * \brief BinarySearchTree<Comparable>::BinarySearchTree
     * \param rhs
     */
    template <typename Comparable>
    BinarySearchTree<Comparable>::BinarySearchTree(const BinarySearchTree &rhs) {
        root = clone(rhs.root);
    }

    /*!
     * \brief BinarySearchTree<Comparable>::BinarySearchTree
     * \param rhs
     */
    template <typename Comparable>
    BinarySearchTree<Comparable>::BinarySearchTree(BinarySearchTree &&rhs) : root{rhs.root} {
        rhs.root = nullptr;
    }

    /*!
     * \brief BinarySearchTree<Comparable>::~BinarySearchTree
     */
    template <typename Comparable>
    BinarySearchTree<Comparable>::~BinarySearchTree() {
        makeEmpty();
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
        return findMax(root)->element;
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
     * \brief BinarySearchTree<Comparable>::makeEmpty
     * \param subtree
     */
    template <typename Comparable>
    void BinarySearchTree<Comparable>::makeEmpty(BinaryNode *&subtree) {
        if (subtree != nullptr) {
            makeEmpty(subtree->left);
            makeEmpty(subtree->right);
            delete subtree;
        }
        subtree = nullptr;
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

    /*!
     * \brief BinarySearchTree<Comparable>::clone
     * \param subtree
     * \return
     */
    template <typename Comparable>
    typename BinarySearchTree<Comparable>::BinaryNode *BinarySearchTree<Comparable>::clone(
        BinaryNode *subtree) const {
        if (subtree == nullptr) {
            return nullptr;
        } else {
            return new BinaryNode{subtree->element, clone(subtree->left), clone(subtree->right)};
        }
    }

}  // namespace DSAA

#endif  // BINARYSEARCHTREE_HPP
