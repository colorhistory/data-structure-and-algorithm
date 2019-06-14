#ifndef LINKEDBINARYTREE_HPP
#define LINKEDBINARYTREE_HPP

#include "bits/stdc++.h"

#include "Exception.hpp"
#include "changeLength1D.hpp"

#include "BinaryTree.hpp"
#include "BinaryTreeNode.hpp"
#include "Booster.hpp"

namespace DSAA {

    template <typename T>

    class LinkedBinaryTree : public BinaryTree<BinaryTreeNode<T>> {
      public:
        LinkedBinaryTree();
        ~LinkedBinaryTree();

        // ADT
        virtual bool empty() const override;
        virtual int size() const override;

        T *rootElement() const;
        void makeTree(const T &theElement, LinkedBinaryTree &leftChildTree, LinkedBinaryTree &rightChildTree);
        LinkedBinaryTree &removeLeftSubtree();
        LinkedBinaryTree &removeRightSubtree();

        virtual void preOrder(void (*theVisit)(BinaryTreeNode<T> *)) override;
        virtual void inOrder(void (*theVisit)(BinaryTreeNode<T> *)) override;
        virtual void postOrder(void (*theVisit)(BinaryTreeNode<T> *)) override;
        virtual void levelOrder(void (*)(BinaryTreeNode<T> *)) override;

        void preOrderOutput();
        void inOrderOutput();
        void postOrderOutput();
        void levelOrderOutput();

        void erase();

      private:
        static void (*visit)(BinaryTreeNode<T> *t);

        static void preOrder(BinaryTreeNode<T> *t);
        static void inOrder(BinaryTreeNode<T> *t);
        static void postOrder(BinaryTreeNode<T> *t);

        static void countNodes(BinaryTreeNode<T> *t);

        static void dispose(BinaryTreeNode<T> *t);
        static void output(BinaryTreeNode<T> *t);
        static void addToCount(BinaryTreeNode<T> *t);
        static void height(BinaryTreeNode<T> *t);

        BinaryTreeNode<T> *root;
        int treeSize;

        static int count;
    };

    /*!
     * \brief LinkedBinaryTree<T>::LinkedBinaryTree
     */
    template <typename T>
    LinkedBinaryTree<T>::LinkedBinaryTree() {
        root = nullptr;
        treeSize = 0;
    }

    /*!
     * \brief LinkedBinaryTree<T>::empty
     * \return
     */
    template <typename T>
    bool LinkedBinaryTree<T>::empty() const {
        return treeSize == 0;
    }

    /*!
     * \brief LinkedBinaryTree<T>::size
     * \return
     */
    template <typename T>
    int LinkedBinaryTree<T>::size() const {
        return treeSize;
    }

    /*!
     * \brief LinkedBinaryTree<T>::rootElement return nullptr is no root,
     *        Otherwise, return pointer to root element.
     * \return
     */
    template <typename T>
    T *LinkedBinaryTree<T>::rootElement() const {
        if (treeSize == 0) {
            return nullptr;
        }
        return &(root->element);
    }

    /*!
     * \brief LinkedBinaryTree<T>::makeTree
     * \param theElement
     * \param leftChildTree
     * \param rightChildTree
     */
    template <typename T>
    void LinkedBinaryTree<T>::makeTree(const T &theElement, LinkedBinaryTree &leftChildTree,
                                       LinkedBinaryTree &rightChildTree) {
        root = new BinaryTreeNode<T>(theElement, leftChildTree, rightChildTree);
        treeSize = leftChildTree.treeSize + rightChildTree.treeSize + 1;

        leftChildTree.root = nullptr;
        rightChildTree.root = nullptr;
        leftChildTree.treeSize = 0;
        rightChildTree.treeSize = 0;
    }

    /*!
     * \brief LinkedBinaryTree<T>::removeRightSubtree
     * \return
     */
    template <typename T>
    LinkedBinaryTree<T> &LinkedBinaryTree<T>::removeRightSubtree() {
        if (treeSize == 0) {
            std::cout << "The tree is empty."
                      << "\n";
        }

        LinkedBinaryTree rightSubTree;
        rightSubTree.root = root->rightChild;
        count = 0;
        rightSubTree.treeSize = countNodes(rightSubTree.root);
        root->rightChild = nullptr;

        return rightSubTree;
    }

    /*!
     * \brief LinkedBinaryTree<T>::removeLeftSubtree
     * \return
     */
    template <typename T>
    LinkedBinaryTree<T> &LinkedBinaryTree<T>::removeLeftSubtree() {
        if (treeSize == 0) {
            std::cout << "The tree is empty."
                      << "\n";
        }

        LinkedBinaryTree leftSubtree;
        leftSubtree.root = root->leftChild;

        count = 0;
        leftSubtree.treeSize = countNodes(leftSubtree.root);
        root->leftChild = nullptr;

        treeSize -= leftSubtree.treeSize;

        return leftSubtree;
    }

}  // namespace DSAA
#endif  // LINKEDBINARYTREE_HPP
