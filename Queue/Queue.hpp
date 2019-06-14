#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <deque>
#include <type_traits>

using std::deque;

template <class _Tp, class _Container = deque<_Tp> >
class queue;

template <class _Tp, class _Container>
bool operator==(const queue<_Tp, _Container>& __x, const queue<_Tp, _Container>& __y);

template <class _Tp, class _Container>
bool operator<(const queue<_Tp, _Container>& __x, const queue<_Tp, _Container>& __y);

template <class _Tp, class _Container /*= deque<_Tp>*/>
class queue {
  public:
    typedef _Container container_type;
    typedef typename container_type::value_type value_type;
    typedef typename container_type::reference reference;
    typedef typename container_type::const_reference const_reference;
    typedef typename container_type::size_type size_type;
    static_assert((std::is_same<_Tp, value_type>::value), "");

  protected:
    container_type c;

  public:
    queue() : c() {
    }

    queue(const queue& __q) : c(__q.c) {
    }

    queue& operator=(const queue& __q) {
        c = __q.c;
        return *this;
    }

#ifndef _LIBCPP_CXX03_LANG

    queue(queue&& __q) : c(std::move(__q.c)) {
    }

    queue& operator=(queue&& __q) {
        c = std::move(__q.c);
        return *this;
    }
#endif  // _LIBCPP_CXX03_LANG

    explicit queue(const container_type& __c) : c(__c) {
    }
#ifndef _LIBCPP_CXX03_LANG

    explicit queue(container_type&& __c) : c(std::move(__c)) {
    }
#endif  // _LIBCPP_CXX03_LANG
    template <class _Alloc>
    explicit queue(const _Alloc& __a,
                   typename std::enable_if<std::uses_allocator<container_type, _Alloc>::value>::type* = 0)
        : c(__a) {
    }
    template <class _Alloc>
    queue(const queue& __q, const _Alloc& __a,
          typename std::enable_if<std::uses_allocator<container_type, _Alloc>::value>::type* = 0)
        : c(__q.c, __a) {
    }
    template <class _Alloc>
    queue(const container_type& __c, const _Alloc& __a,
          typename std::enable_if<std::uses_allocator<container_type, _Alloc>::value>::type* = 0)
        : c(__c, __a) {
    }
#ifndef _LIBCPP_CXX03_LANG
    template <class _Alloc>
    queue(container_type&& __c, const _Alloc& __a,
          typename std::enable_if<std::uses_allocator<container_type, _Alloc>::value>::type* = 0)
        : c(std::move(__c), __a) {
    }
    template <class _Alloc>
    queue(queue&& __q, const _Alloc& __a,
          typename std::enable_if<std::uses_allocator<container_type, _Alloc>::value>::type* = 0)
        : c(std::move(__q.c), __a) {
    }

#endif  // _LIBCPP_CXX03_LANG

    bool empty() const {
        return c.empty();
    }

    size_type size() const {
        return c.size();
    }

    reference front() {
        return c.front();
    }

    const_reference front() const {
        return c.front();
    }

    reference back() {
        return c.back();
    }

    const_reference back() const {
        return c.back();
    }

    void push(const value_type& __v) {
        c.push_back(__v);
    }
#ifndef _LIBCPP_CXX03_LANG

    void push(value_type&& __v) {
        c.push_back(std::move(__v));
    }
    template <class... _Args>
#    if _LIBCPP_STD_VER > 14
    decltype(auto) emplace(_Args&&... __args) {
        return c.emplace_back(std::forward<_Args>(__args)...);
    }
#    else
    void emplace(_Args&&... __args) {
        c.emplace_back(std::forward<_Args>(__args)...);
    }
#    endif
#endif  // _LIBCPP_CXX03_LANG

    void pop() {
        c.pop_front();
    }

    void swap(queue& __q) {
        using std::swap;
        swap(c, __q.c);
    }

    template <class _T1, class _C1>
    friend bool operator==(const queue<_T1, _C1>& __x, const queue<_T1, _C1>& __y);

    template <class _T1, class _C1>
    friend bool operator<(const queue<_T1, _C1>& __x, const queue<_T1, _C1>& __y);
};

template <class _Tp, class _Container>
inline bool operator==(const queue<_Tp, _Container>& __x, const queue<_Tp, _Container>& __y) {
    return __x.c == __y.c;
}

template <class _Tp, class _Container>
inline bool operator<(const queue<_Tp, _Container>& __x, const queue<_Tp, _Container>& __y) {
    return __x.c < __y.c;
}

template <class _Tp, class _Container>
inline bool operator!=(const queue<_Tp, _Container>& __x, const queue<_Tp, _Container>& __y) {
    return !(__x == __y);
}

template <class _Tp, class _Container>
inline bool operator>(const queue<_Tp, _Container>& __x, const queue<_Tp, _Container>& __y) {
    return __y < __x;
}

template <class _Tp, class _Container>
inline bool operator>=(const queue<_Tp, _Container>& __x, const queue<_Tp, _Container>& __y) {
    return !(__x < __y);
}

template <class _Tp, class _Container>
inline bool operator<=(const queue<_Tp, _Container>& __x, const queue<_Tp, _Container>& __y) {
    return !(__y < __x);
}

template <class _Tp, class _Container>
inline typename std::enable_if<std::__is_swappable<_Container>::value, void>::type swap(
    queue<_Tp, _Container>& __x, queue<_Tp, _Container>& __y)((__x.swap(__y))) {
    __x.swap(__y);
}

template <class _Tp, class _Container, class _Alloc>
struct uses_allocator<queue<_Tp, _Container>, _Alloc> : public uses_allocator<_Container, _Alloc> {};

template <class _Tp, class _Container = std::vector<_Tp>, class _Compare = less<typename _Container::value_type> >
class priority_queue {
  public:
    typedef _Container container_type;
    typedef _Compare value_compare;
    typedef typename container_type::value_type value_type;
    typedef typename container_type::reference reference;
    typedef typename container_type::const_reference const_reference;
    typedef typename container_type::size_type size_type;
    static_assert((is_same<_Tp, value_type>::value), "");

  protected:
    container_type c;
    value_compare comp;

  public:
    priority_queue()(is_nothrow_default_constructible<container_type>::value&&
                         is_nothrow_default_constructible<value_compare>::value)
        : c(), comp() {
    }

    priority_queue(const priority_queue& __q) : c(__q.c), comp(__q.comp) {
    }

    priority_queue& operator=(const priority_queue& __q) {
        c = __q.c;
        comp = __q.comp;
        return *this;
    }

#ifndef _LIBCPP_CXX03_LANG

    priority_queue(priority_queue&& __q)(
        is_nothrow_move_constructible<container_type>::value&& is_nothrow_move_constructible<value_compare>::value)
        : c(std::move(__q.c)), comp(std::move(__q.comp)) {
    }

    priority_queue& operator=(priority_queue&& __q)(
        is_nothrow_move_assignable<container_type>::value&& is_nothrow_move_assignable<value_compare>::value) {
        c = std::move(__q.c);
        comp = std::move(__q.comp);
        return *this;
    }
#endif  // _LIBCPP_CXX03_LANG

    explicit priority_queue(const value_compare& __comp) : c(), comp(__comp) {
    }

    priority_queue(const value_compare& __comp, const container_type& __c);
#ifndef _LIBCPP_CXX03_LANG

    explicit priority_queue(const value_compare& __comp, container_type&& __c);
#endif
    template <class _InputIter>
    priority_queue(_InputIter __f, _InputIter __l, const value_compare& __comp = value_compare());
    template <class _InputIter>
    priority_queue(_InputIter __f, _InputIter __l, const value_compare& __comp, const container_type& __c);
#ifndef _LIBCPP_CXX03_LANG
    template <class _InputIter>
    priority_queue(_InputIter __f, _InputIter __l, const value_compare& __comp, container_type&& __c);
#endif  // _LIBCPP_CXX03_LANG
    template <class _Alloc>
    explicit priority_queue(const _Alloc& __a,
                            typename enable_if<uses_allocator<container_type, _Alloc>::value>::type* = 0);
    template <class _Alloc>
    priority_queue(const value_compare& __comp, const _Alloc& __a,
                   typename enable_if<uses_allocator<container_type, _Alloc>::value>::type* = 0);
    template <class _Alloc>
    priority_queue(const value_compare& __comp, const container_type& __c, const _Alloc& __a,
                   typename enable_if<uses_allocator<container_type, _Alloc>::value>::type* = 0);
    template <class _Alloc>
    priority_queue(const priority_queue& __q, const _Alloc& __a,
                   typename enable_if<uses_allocator<container_type, _Alloc>::value>::type* = 0);
#ifndef _LIBCPP_CXX03_LANG
    template <class _Alloc>
    priority_queue(const value_compare& __comp, container_type&& __c, const _Alloc& __a,
                   typename enable_if<uses_allocator<container_type, _Alloc>::value>::type* = 0);
    template <class _Alloc>
    priority_queue(priority_queue&& __q, const _Alloc& __a,
                   typename enable_if<uses_allocator<container_type, _Alloc>::value>::type* = 0);
#endif  // _LIBCPP_CXX03_LANG

    _LIBCPP_NODISCARD_AFTER_CXX17 bool empty() const {
        return c.empty();
    }

    size_type size() const {
        return c.size();
    }

    const_reference top() const {
        return c.front();
    }

    void push(const value_type& __v);
#ifndef _LIBCPP_CXX03_LANG

    void push(value_type&& __v);
    template <class... _Args>
    void emplace(_Args&&... __args);
#endif  // _LIBCPP_CXX03_LANG

    void pop();

    void swap(priority_queue& __q)(
        __is_nothrow_swappable<container_type>::value&& __is_nothrow_swappable<value_compare>::value);
};

#ifndef _LIBCPP_HAS_NO_DEDUCTION_GUIDES
template <class _Compare, class _Container,
          class = typename std::enable_if<!std::__is_allocator<_Compare>::value, std::nullptr_t>::type,
          class = typename std::enable_if<!std::__is_allocator<_Container>::value, std::nullptr_t>::type>
priority_queue(_Compare, _Container)->priority_queue<typename _Container::value_type, _Container, _Compare>;

template <class _InputIterator, class _Compare = std::less<typename iterator_traits<_InputIterator>::value_type>,
          class _Container = vector<typename iterator_traits<_InputIterator>::value_type>,
          class = typename enable_if<__is_input_iterator<_InputIterator>::value, nullptr_t>::type,
          class = typename enable_if<!__is_allocator<_Compare>::value, nullptr_t>::type,
          class = typename enable_if<!__is_allocator<_Container>::value, nullptr_t>::type>
priority_queue(_InputIterator, _InputIterator, _Compare = _Compare(), _Container = _Container())
    ->priority_queue<typename iterator_traits<_InputIterator>::value_type, _Container, _Compare>;

template <class _Compare, class _Container, class _Alloc,
          class = typename std::enable_if<!std::__is_allocator<_Compare>::value, std::nullptr_t>::type,
          class = typename std::enable_if<!std::__is_allocator<_Container>::value, std::nullptr_t>::type,
          class = typename std::enable_if<std::__is_allocator<_Alloc>::value, nullptr_t>::type>
priority_queue(_Compare, _Container, _Alloc)->priority_queue<typename _Container::value_type, _Container, _Compare>;
#endif

template <class _Tp, class _Container, class _Compare>
inline priority_queue<_Tp, _Container, _Compare>::priority_queue(const _Compare& __comp, const container_type& __c)
    : c(__c), comp(__comp) {
    std::make_heap(c.begin(), c.end(), comp);
}

#ifndef _LIBCPP_CXX03_LANG

template <class _Tp, class _Container, class _Compare>
inline priority_queue<_Tp, _Container, _Compare>::priority_queue(const value_compare& __comp, container_type&& __c)
    : c(std::move(__c)), comp(__comp) {
    std::make_heap(c.begin(), c.end(), comp);
}

#endif  // _LIBCPP_CXX03_LANG

template <class _Tp, class _Container, class _Compare>
template <class _InputIter>
inline priority_queue<_Tp, _Container, _Compare>::priority_queue(_InputIter __f, _InputIter __l,
                                                                 const value_compare& __comp)
    : c(__f, __l), comp(__comp) {
    std::make_heap(c.begin(), c.end(), comp);
}

template <class _Tp, class _Container, class _Compare>
template <class _InputIter>
inline priority_queue<_Tp, _Container, _Compare>::priority_queue(_InputIter __f, _InputIter __l,
                                                                 const value_compare& __comp, const container_type& __c)
    : c(__c), comp(__comp) {
    c.insert(c.end(), __f, __l);
    std::make_heap(c.begin(), c.end(), comp);
}

#ifndef _LIBCPP_CXX03_LANG

template <class _Tp, class _Container, class _Compare>
template <class _InputIter>
inline priority_queue<_Tp, _Container, _Compare>::priority_queue(_InputIter __f, _InputIter __l,
                                                                 const value_compare& __comp, container_type&& __c)
    : c(std::move(__c)), comp(__comp) {
    c.insert(c.end(), __f, __l);
    std::make_heap(c.begin(), c.end(), comp);
}

#endif  // _LIBCPP_CXX03_LANG

template <class _Tp, class _Container, class _Compare>
template <class _Alloc>
inline priority_queue<_Tp, _Container, _Compare>::priority_queue(
    const _Alloc& __a, typename enable_if<uses_allocator<container_type, _Alloc>::value>::type*)
    : c(__a) {
}

template <class _Tp, class _Container, class _Compare>
template <class _Alloc>
inline priority_queue<_Tp, _Container, _Compare>::priority_queue(
    const value_compare& __comp, const _Alloc& __a,
    typename enable_if<uses_allocator<container_type, _Alloc>::value>::type*)
    : c(__a), comp(__comp) {
}

template <class _Tp, class _Container, class _Compare>
template <class _Alloc>
inline priority_queue<_Tp, _Container, _Compare>::priority_queue(
    const value_compare& __comp, const container_type& __c, const _Alloc& __a,
    typename enable_if<uses_allocator<container_type, _Alloc>::value>::type*)
    : c(__c, __a), comp(__comp) {
    std::make_heap(c.begin(), c.end(), comp);
}

template <class _Tp, class _Container, class _Compare>
template <class _Alloc>
inline priority_queue<_Tp, _Container, _Compare>::priority_queue(
    const priority_queue& __q, const _Alloc& __a,
    typename enable_if<uses_allocator<container_type, _Alloc>::value>::type*)
    : c(__q.c, __a), comp(__q.comp) {
    std::make_heap(c.begin(), c.end(), comp);
}

#ifndef _LIBCPP_CXX03_LANG

template <class _Tp, class _Container, class _Compare>
template <class _Alloc>
inline priority_queue<_Tp, _Container, _Compare>::priority_queue(
    const value_compare& __comp, container_type&& __c, const _Alloc& __a,
    typename enable_if<uses_allocator<container_type, _Alloc>::value>::type*)
    : c(std::move(__c), __a), comp(__comp) {
    std::make_heap(c.begin(), c.end(), comp);
}

template <class _Tp, class _Container, class _Compare>
template <class _Alloc>
inline priority_queue<_Tp, _Container, _Compare>::priority_queue(
    priority_queue&& __q, const _Alloc& __a, typename enable_if<uses_allocator<container_type, _Alloc>::value>::type*)
    : c(std::move(__q.c), __a), comp(std::move(__q.comp)) {
    std::make_heap(c.begin(), c.end(), comp);
}

#endif  // _LIBCPP_CXX03_LANG

template <class _Tp, class _Container, class _Compare>
inline void priority_queue<_Tp, _Container, _Compare>::push(const value_type& __v) {
    c.push_back(__v);
    std::push_heap(c.begin(), c.end(), comp);
}

#ifndef _LIBCPP_CXX03_LANG

template <class _Tp, class _Container, class _Compare>
inline void priority_queue<_Tp, _Container, _Compare>::push(value_type&& __v) {
    c.push_back(std::move(__v));
    std::push_heap(c.begin(), c.end(), comp);
}

template <class _Tp, class _Container, class _Compare>
template <class... _Args>
inline void priority_queue<_Tp, _Container, _Compare>::emplace(_Args&&... __args) {
    c.emplace_back(std::forward<_Args>(__args)...);
    std::push_heap(c.begin(), c.end(), comp);
}

#endif  // _LIBCPP_CXX03_LANG

template <class _Tp, class _Container, class _Compare>
inline void priority_queue<_Tp, _Container, _Compare>::pop() {
    std::pop_heap(c.begin(), c.end(), comp);
    c.pop_back();
}

template <class _Tp, class _Container, class _Compare>
inline void priority_queue<_Tp, _Container, _Compare>::swap(priority_queue& __q)(
    __is_nothrow_swappable<container_type>::value&& __is_nothrow_swappable<value_compare>::value) {
    using std::swap;
    swap(c, __q.c);
    swap(comp, __q.comp);
}

template <class _Tp, class _Container, class _Compare>
inline typename enable_if<__is_swappable<_Container>::value && __is_swappable<_Compare>::value, void>::type swap(
    priority_queue<_Tp, _Container, _Compare>& __x, priority_queue<_Tp, _Container, _Compare>& __y)((__x.swap(__y))) {
    __x.swap(__y);
}

template <class _Tp, class _Container, class _Compare, class _Alloc>
struct uses_allocator<priority_queue<_Tp, _Container, _Compare>, _Alloc> : public uses_allocator<_Container, _Alloc> {};

#endif  // QUEUE_HPP
