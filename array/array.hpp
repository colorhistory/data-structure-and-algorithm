#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <algorithm>
#include <exception>

namespace DSAA {
    template <typename T, size_t Size>
    struct array {
        typedef array self;
        typedef T value_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef value_type* iterator;
        typedef const value_type* const_iterator;
        typedef value_type* pointer;
        typedef const value_type* const_pointer;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        // data
        T elems[Size];

        void fill(const value_type& u);
        void swap(array& a);

        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;

        reverse_iterator rbegin();
        const_reverse_iterator rbegin() const;
        reverse_iterator rend();
        const_reverse_iterator rend() const;

        const_iterator cbegin() const;
        const_iterator cend() const;
        const_reverse_iterator crbegin() const;
        const_reverse_iterator crend() const;

        /*! capacity */
        size_type size() const;
        size_type max_size() const;
        bool empty() const;

        reference operator[](size_type n);
        const_reference operator[](size_type n) const;

        reference at(size_type n);
        const_reference at(size_type n) const;

        reference front();
        const_reference front() const;
        reference back();
        const_reference back() const;

        pointer data();
        const pointer data() const;
    };

    /*!
     * \brief array<T, Size>::fill
     * \param u
     */
    template <typename T, size_t Size>
    inline void array<T, Size>::fill(const array::value_type& u) {
        std::fill_n(elems, Size, u);
    }

    /*!
     * \brief array<T, Size>::swap
     * \param a
     */
    template <typename T, size_t Size>
    void array<T, Size>::swap(array& a) {
        std::swap_ranges(elems, elems + Size, a.elems);
    }

    /*!
     * \brief array<T, Size>::begin
     * \return
     */
    template <typename T, size_t Size>
    typename array<T, Size>::iterator array<T, Size>::begin() {
        return iterator(data());
    }

    /*!
     * \brief array<T, Size>::cbegin
     * \return
     */
    template <typename T, size_t Size>
    typename array<T, Size>::const_iterator array<T, Size>::begin() const {
        return const_iterator(data());
    }

    /*!
     * \brief array<T, Size>::end
     * \return
     */
    template <typename T, size_t Size>
    typename array<T, Size>::iterator array<T, Size>::end() {
        return iterator(data() + Size);
    }

    /*!
     * \brief array<T, Size>::end
     * \return
     */
    template <typename T, size_t Size>
    typename array<T, Size>::const_iterator array<T, Size>::end() const {
        return const_iterator(data() + Size);
    }

    /*!
     * \brief array<T, Size>::rbegin
     * \return
     */
    template <typename T, size_t Size>
    typename array<T, Size>::reverse_iterator array<T, Size>::rbegin() {
        return reverse_iterator(end());
    }

    /*!
     * \brief array<T, Size>::rbegin
     * \return
     */
    template <typename T, size_t Size>
    typename array<T, Size>::const_reverse_iterator array<T, Size>::rbegin() const {
        return const_reverse_iterator(end());
    }

    /*!
     * \brief array<T, Size>::rend
     * \return
     */
    template <typename T, size_t Size>
    typename array<T, Size>::reverse_iterator array<T, Size>::rend() {
        return reverse_iterator(begin());
    }

    /*!
     * \brief array<T, Size>::rend
     * \return
     */
    template <typename T, size_t Size>
    typename array<T, Size>::const_reverse_iterator array<T, Size>::rend() const {
        return const_reverse_iterator(begin());
    }

    /*!
     * \brief array<T, Size>::cbegin
     * \return
     */
    template <typename T, size_t Size>
    typename array<T, Size>::const_iterator array<T, Size>::cbegin() const {
        return begin();
    }

    /*!
     * \brief array<T, Size>::cend
     * \return
     */
    template <typename T, size_t Size>
    typename array<T, Size>::const_iterator array<T, Size>::cend() const {
        return end();
    }

    /*!
     * \brief array<T, Size>::crbegin
     * \return
     */
    template <typename T, size_t Size>
    typename array<T, Size>::const_reverse_iterator array<T, Size>::crbegin() const {
        return rbegin();
    }

    /*!
     * \brief array<T, Size>::crend
     * \return
     */
    template <typename T, size_t Size>
    typename array<T, Size>::const_reverse_iterator array<T, Size>::crend() const {
        return rend();
    }

    /*!
     * \brief array<T, Size>::size
     * \return
     */
    template <typename T, size_t Size>
    typename array<T, Size>::size_type array<T, Size>::size() const {
        return Size;
    }

    /*!
     * \brief array<T, Size>::max_size
     * \return
     */
    template <typename T, size_t Size>
    typename array<T, Size>::size_type array<T, Size>::max_size() const {
        return Size;
    }

    /*!
     * \brief array<T, Size>::empty
     * \return
     */
    template <typename T, size_t Size>
    bool array<T, Size>::empty() const {
        return false;
    }

    /*!
     * \brief array<T, Size>::operator []
     * \param n
     * \return
     */
    template <typename T, size_t Size>
    typename array<T, Size>::reference array<T, Size>::operator[](array::size_type n) {
        return elems[n];
    }

    /*!
     * \brief array<T, Size>::operator []
     * \param n
     * \return
     */
    template <typename T, size_t Size>
    typename array<T, Size>::const_reference array<T, Size>::operator[](array::size_type n) const {
        return elems[n];
    }

    /*!
     * \brief array<T, Size>::at
     * \param n
     * \return
     */
    template <typename T, size_t Size>
    typename array<T, Size>::reference array<T, Size>::at(array::size_type n) {
        if (n >= Size) {
            throw std::out_of_range("array::at");
        }

        return elems[n];
    }

    /*!
     * \brief array<T, Size>::at
     * \param n
     * \return
     */
    template <typename T, size_t Size>
    typename array<T, Size>::const_reference array<T, Size>::at(array::size_type n) const {
        if (n >= Size) {
            throw std::out_of_range("array::at");
        }

        return elems[n];
    }

    /*!
     * \brief array<T, Size>::front
     * \return
     */
    template <typename T, size_t Size>
    typename array<T, Size>::reference array<T, Size>::front() {
        return elems[0];
    }

    /*!
     * \brief array<T, Size>::front
     * \return
     */
    template <typename T, size_t Size>
    typename array<T, Size>::const_reference array<T, Size>::front() const {
        return elems[0];
    }

    /*!
     * \brief array<T, Size>::back
     * \return
     */
    template <typename T, size_t Size>
    typename array<T, Size>::reference array<T, Size>::back() {
        return elems[Size - 1];
    }

    /*!
     * \brief array<T, Size>::back
     * \return
     */
    template <typename T, size_t Size>
    typename array<T, Size>::const_reference array<T, Size>::back() const {
        return elems[Size - 1];
    }

    /*!
     * \brief array<T, Size>::data
     * \return
     */
    template <typename T, size_t Size>
    typename array<T, Size>::pointer array<T, Size>::data() {
        return elems;
    }

    /*!
     * \brief array<T, Size>::data
     * \return
     */
    template <typename T, size_t Size>
    const typename array<T, Size>::pointer array<T, Size>::data() const {
        return elems;
    }

}  // namespace DSAA

#endif  // ARRAY_HPP
