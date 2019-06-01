#ifndef VECTORLIST_HPP
#define VECTORLIST_HPP

#include "bits/stdc++.h"

#include "Exception.hpp"
#include "LinearList.hpp"
#include "changeLength1D.hpp"

namespace DSAA {

    template <typename T>
    class VectorList : public LinearList<T> {
      public:
        VectorList(int initialCapacity = 10);
        VectorList(const VectorList<T> &vectorList);
        ~VectorList();

        // ADT
        bool empty() const;
        int size() const;
        int capacity() const;

        T &get(int theIndex) const;
        int indexOf(const T &theElement) const;

        void erase(int theIndex);
        void insert(int theIndex, const T &theElement);

        void output(std::ostream &out) const;

        using iterator = typename std::vector<T>::iterator;
        iterator begin() const;
        iterator end() const;

      private:
        void checkIndex(int theIndex) const;
        std::vector<T> *elements;
    };

    /*!
     * \brief VectorList<T>::VectorList
     * \param initialCapacity
     */
    template <typename T>
    VectorList<T>::VectorList(int initialCapacity) {
        if (initialCapacity < 1) {
            std::stringstream s;
            s << "Initial Capacity = " << initialCapacity << " Must be > 0";
            throw IllegalParameterValue(s.str());
        }

        elements = new std::vector<T>;
        elements->reserve(initialCapacity);
    }

    /*!
     * \brief VectorList<T>::VectorList
     * \param vectorList
     */
    template <typename T>
    VectorList<T>::VectorList(const VectorList<T> &vectorList) {
        elements = new std::vector<T>(*vectorList.elements);
    }

    /*!
     * \brief VectorList<T>::~VectorList
     */
    template <typename T>
    VectorList<T>::~VectorList() {
        delete elements;
    }

    /*!
     * \brief VectorList<T>::empty
     * \return
     */
    template <typename T>
    bool VectorList<T>::empty() const {
        return elements->empty();
    }

    /*!
     * \brief VectorList<T>::size
     * \return
     */
    template <typename T>
    int VectorList<T>::size() const {
        return elements->size();
    }

    /*!
     * \brief VectorList<T>::capacity
     * \return
     */
    template <typename T>
    int VectorList<T>::capacity() const {
        return elements->capacity();
    }

    /*!
     * \brief VectorList<T>::get
     * \param theIndex
     * \return
     */
    template <typename T>
    T &VectorList<T>::get(int theIndex) const {
        checkIndex(theIndex);

        return (*elements)[theIndex];
    }

    /*!
     * \brief VectorList<T>::indexOf
     * \param theElement
     * \return
     */
    template <typename T>
    int VectorList<T>::indexOf(const T &theElement) const {
        int pos = static_cast<int>(std::find(elements->begin(), elements->end(), theElement) - elements->begin());

        if (pos == size()) {
            return -1;
        }

        return pos;
    }

    /*!
     * \brief VectorList<T>::erase
     * \param theIndex
     */
    template <typename T>
    void VectorList<T>::erase(int theIndex) {
        checkIndex(theIndex);

        elements->erase(theIndex + begin());
    }

    /*!
     * \brief VectorList<T>::insert
     * \param theIndex
     * \param theElement
     */
    template <typename T>
    void VectorList<T>::insert(int theIndex, const T &theElement) {
        if (theIndex < 0 || theIndex > size()) {
            std::stringstream s;
            s << "index = " << theIndex << " size = " << size();
            throw IllegalIndex(s.str());
        }

        elements->insert(elements->begin() + theIndex, theElement);
    }

    /*!
     * \brief VectorList<T>::output
     * \param out
     */
    template <typename T>
    void VectorList<T>::output(std::ostream &out) const {
        std::copy(begin(), end(), std::ostream_iterator<T>(out, "   "));
    }

    /*!
     * \brief VectorList<T>::begin
     * \return
     */
    template <typename T>
    typename VectorList<T>::iterator VectorList<T>::begin() const {
        return elements->begin();
    }

    /*!
     * \brief VectorList<T>::end
     * \return
     */
    template <typename T>
    typename VectorList<T>::iterator VectorList<T>::end() const {
        return elements->end();
    }

    /*!
     * \brief VectorList<T>::checkIndex
     * \param theIndex
     */
    template <typename T>
    void VectorList<T>::checkIndex(int theIndex) const {
        if (theIndex < 0 || theIndex >= size()) {
            std::ostringstream s;
            s << "The index = " << theIndex << " size = " << size();
            throw IllegalIndex(s.str());
        }
    }

    /*!
     * \brief operator <<
     * \param out
     * \param vectorList
     * \return
     */
    template <typename T>
    std::ostream &operator<<(std::ostream &out, const VectorList<T> vectorList) {
        vectorList.output(out);

        return out;
    }

}  // namespace DSAA
#endif  // VECTORLIST_HPP
