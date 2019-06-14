#ifndef BINARYTREENODE_HPP
#define BINARYTREENODE_HPP

namespace DSAA {

    template <typename T>
    struct BinaryTreeNode {
        BinaryTreeNode();
        BinaryTreeNode(const T &theElement);
        BinaryTreeNode(const T &theElement, BinaryTreeNode *theLeftChild, BinaryTreeNode *theRightChild);

        T element;
        BinaryTreeNode leftChild;
        BinaryTreeNode rightChild;
    };

    /*!
     * \brief BinaryTreeNode<T>::BinaryTreeNode
     */
    template <typename T>
    BinaryTreeNode<T>::BinaryTreeNode() {
        leftChild = nullptr;
        rightChild = nullptr;
    }

    /*!
     * \brief BinaryTreeNode<T>::BinaryTreeNode
     * \param theElement
     */
    template <typename T>
    BinaryTreeNode<T>::BinaryTreeNode(const T &theElement) : element{theElement} {
        leftChild = nullptr;
        rightChild = nullptr;
    }

    /*!
     * \brief BinaryTreeNode<T>::BinaryTreeNode
     * \param theElement
     * \param theLeftChild
     * \param theRightChild
     */
    template <typename T>
    BinaryTreeNode<T>::BinaryTreeNode(const T &theElement, BinaryTreeNode *theLeftChild, BinaryTreeNode *theRightChild)
        : element(theElement), leftChild(theLeftChild), rightChild(theRightChild) {
    }

}  // namespace DSAA

#endif  // BINARYTREENODE_HPP
