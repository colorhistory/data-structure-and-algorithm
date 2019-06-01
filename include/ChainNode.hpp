#ifndef CHAINNODE_HPP
#define CHAINNODE_HPP

namespace DSAA {

    template <typename T>
    struct ChainNode {
        ChainNode();
        ChainNode(const T& element);
        ChainNode(const T& element, ChainNode<T>* next);

        T element;
        ChainNode<T>* next;
    };

    /*!
     * \brief ChainNode<T>::ChainNode
     */
    template <typename T>
    inline ChainNode<T>::ChainNode() {
    }

    /*!
     * \brief ChainNode<T>::ChainNode
     * \param element
     */
    template <typename T>
    inline ChainNode<T>::ChainNode(const T& element) {
        this->element = element;
    }

    /*!
     * \brief ChainNode<T>::ChainNode
     * \param element
     * \param next
     */
    template <typename T>
    ChainNode<T>::ChainNode(const T& element, ChainNode<T>* next) {
        this->element = element;
        this->next = next;
    }

}  // namespace DSAA
#endif  // CHAINNODE_HPP
