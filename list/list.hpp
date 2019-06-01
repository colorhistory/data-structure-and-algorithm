#ifndef LIST_HPP
#define LIST_HPP

#include <algorithm>

namespace XIAOHAI {

    template <typename T>
    class list {
      public:
        class iterator;
        class const_iterator;

      private:
        struct Node;

      public:
        list() {
            init();
        }
        ~list() {
            clear();
            delete head;
            delete tail;
        }
        list(const list &rhs) {
            init();
            for (auto &x : rhs) push_back(x);
        }
        list &operator=(const list &rhs) {
            list copy = rhs;
            std::swap(*this, copy);
            return *this;
        }
        list(list &&rhs)
            : theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail} {
            rhs.theSize = 0;
            rhs.head = nullptr;
            rhs.tail = nullptr;
        }
        list &operator=(list &&rhs) {
            std::swap(theSize, rhs.theSize);
            std::swap(head, rhs.head);
            std::swap(tail, rhs.tail);
            return *this;
        }

        // ADT
        iterator begin() {
            return {head->next};
        }
        const_iterator begin() const {
            return {head->next};
        }
        iterator end() {
            return {tail};
        }
        const_iterator end() const {
            return {tail};
        }
        int size() const {
            return theSize;
        }
        bool empty() const {
            return size() == 0;
        }
        void clear() {
            while (!empty()) {
                pop_front();
            }
        }
        T &front() {
            return *begin();
        }
        const T &front() const {
            return *begin();
        }
        T &back() {
            return *--end();
        }
        const T &back() const {
            return *--end();
        }
        void push_front(const T &x) {
            insert(begin(), x);
        }
        void push_front(T &&x) {
            insert(begin(), std::move(x));
        }
        void push_back(const T &x) {
            insert(end(), x);
        }
        void push_back(T &&x) {
            insert(end(), std::move(x));
        }
        void pop_front() {
            erase(begin());
        }
        void pop_back() {
            erase(--end());
        }

        // Insert x before itr.
        iterator insert(iterator itr, const T &x) {
            Node *p = itr.current;
            theSize++;
            return {p->prev = p->prev->next = new Node{x, p->prev, p}};
        }
        // Insert x before itr.
        iterator insert(iterator itr, T &&x) {
            Node *p = itr.current;
            theSize++;
            return {p->prev = p->prev->next =
                        new Node{std::move(x), p->prev, p}};
        }

        // Erase item at itr.
        iterator erase(iterator itr) {
            Node *p = itr.current;
            iterator retVal{p->next};
            p->prev->next = p->next;
            p->next->prev = p->prev;
            delete p;
            theSize--;
            return retVal;
        }
        iterator erase(iterator from, iterator to) {
            for (iterator itr = from; itr != to;) {
                itr = erase(itr);
            }
            return to;
        }

      public:
        class const_iterator {
            friend class list<T>;

          public:
            const_iterator() : current{nullptr} {
            }

            const T &operator*() const {
                return retrieve();
            }

            const_iterator &operator++() {
                current = current->next;
                return *this;
            }

            const_iterator &operator++(int) {
                const_iterator old = *this;
                ++(*this);
                return old;
            }

            bool operator==(const const_iterator &rhs) const {
                return current == rhs.current;
            }

            bool operator!=(const_iterator &rhs) const {
                return !(*this == rhs);
            }

          protected:
            Node *current;

            T &retrieve() const {
                return current->data;
            }
            const_iterator(Node *p) : current{p} {
            }
        };

        class iterator : public const_iterator {
            friend class list<T>;

          public:
            iterator() {
            }

            T &operator*() {
                return const_iterator::retrieve();
            }

            const T &operator*() const {
                return const_iterator::operator();
            }

            iterator &operator++() {
                this->current = this->current->next;
                return *this;
            }

            iterator operator++(int) {
                iterator old = *this;
                ++(*this);
                return old;
            }

          protected:
            iterator(Node *p) : const_iterator{p} {
            }
        };

      private:
        struct Node {
            Node(const T &d = T{}, Node *p = nullptr, Node *n = nullptr)
                : data{d}, prev{p}, next{n} {
            }

            Node(T &&d, Node *p = nullptr, Node *n = nullptr)
                : data{std::move(d)}, prev{p}, next{n} {
            }
            T data;
            Node *prev;
            Node *next;
        };

      private:
        void init() {
            theSize = 0;
            head = new Node;
            tail = new Node;
            head->next = tail;
            tail->next = nullptr;
        }

        int theSize;
        Node *head;
        Node *tail;
    };

}  // namespace XIAOHAI

#endif  // LIST_HPP
