#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

#include "bits/stdc++.h"

namespace DSAA {

    template <typename T>
    class BinaryTree {
      public:
        virtual ~BinaryTree() = 0;

        // ADT
        virtual bool empty() const = 0;
        virtual int size() const = 0;

        virtual void preOrder(void (*)(T*)) = 0;
        virtual void inOrder(void (*)(T*)) = 0;
        virtual void postOrder(void (*)(T*)) = 0;
        virtual void levelOrder(void (*)(T*)) = 0;
    };

    /*!
     * \brief BinaryTree<T>::~BinaryTree
     */
    template <typename T>
    BinaryTree<T>::~BinaryTree() {
    }

}  // namespace DSAA
#endif  // BINARYTREE_HPP
