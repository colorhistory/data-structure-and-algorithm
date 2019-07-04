#ifndef QUADRATICPROBING_HPP
#define QUADRATICPROBING_HPP

#include "bits/stdc++.h"

namespace DSAA {
    int nextPrime(int n);

    template <typename HashObj>
    class HashTable {
      public:
        explicit HashTable(int size = 101) : array(nextPrime(size)) {
            makeEmpty();
        }

        // ADT
        bool contains(const HashObj &x) const;
        void makeEmpty();
        bool insert(const HashObj &x);
        bool insert(HashObj &&x);
        bool remove(const HashObj &x);

        enum EntryType { ACTIVE = 0, EMPTY = 1, DELETED = 2 };

      private:
        struct HashEntry;
        std::vector<HashEntry> array;
        int currentSize;

        struct HashEntry {
            HashObj element;
            EntryType info;

            HashEntry(const HashObj &e = HashObj{}, EntryType i = EMPTY);
            HashEntry(HashObj &&e, EntryType i = EMPTY);
        };

        bool isActive(int currentPos) const;
        int findPos(const HashObj &x) const;

        void rehash();
        size_t Myhash(const HashObj &x) const;
    };

    ////////////////////////////////////////////////////////////
    /// \brief HashTable<HashObj>::contains
    /// \param x
    /// \return
    ///
    template <typename HashObj>
    bool HashTable<HashObj>::contains(const HashObj &x) const {
        return isActive(findPos(x));
    }

    ////////////////////////////////////////////////////////////
    /// \brief HashTable<HashObj>::makeEmpty
    ///
    template <typename HashObj>
    void HashTable<HashObj>::makeEmpty() {
        currentSize = 0;
        for (auto &entry : array) {
            entry.info = EMPTY;
        }
    }

    ////////////////////////////////////////////////////////////
    /// \brief HashTable<HashObj>::insert
    /// \param x
    /// \return
    ///
    template <typename HashObj>
    bool HashTable<HashObj>::insert(const HashObj &x) {
        int currentPos = findPos(x);
        if (isActive(currentPos)) {
            return false;
        }

        if (array[currentPos].info != DELETED) {
            ++currentSize;
        }

        array[currentPos].element = x;
        array[currentPos].info = ACTIVE;

        if (currentPos > array.size() / 2) {
            rehash();
        }
        return true;
    }

    ////////////////////////////////////////////////////////////
    /// \brief HashTable<HashObj>::insert
    /// \param x
    /// \return
    ///
    template <typename HashObj>
    bool HashTable<HashObj>::insert(HashObj &&x) {
        int currentPos = findPos(x);
        if (isActive(currentPos)) {
            return false;
        }

        if (array[currentPos].info != DELETED) {
            ++currentSize;
        }

        array[currentPos] = std::move(x);
        array[currentPos].info = ACTIVE;

        if (currentSize > array.size() / 2) {
            rehash();
        }
        return true;
    }

    ////////////////////////////////////////////////////////////
    /// \brief HashTable<HashObj>::remove
    /// \param x
    /// \return
    ///
    template <typename HashObj>
    bool HashTable<HashObj>::remove(const HashObj &x) {
        int currentPos = findPos(x);
        if (!isActive(currentPos)) {
            return false;
        }

        array[currentPos].info = DELETED;
        return true;
    }

    ////////////////////////////////////////////////////////////
    /// \brief HashTable<HashObj>::HashEntry::HashEntry
    /// \param e
    /// \param i
    ///
    template <typename HashObj>
    HashTable<HashObj>::HashEntry::HashEntry(const HashObj &e, EntryType i) : element{e}, info{i} {
    }

    ////////////////////////////////////////////////////////////
    /// \brief HashTable<HashObj>::HashEntry::HashEntry
    /// \param e
    /// \param i
    ///
    template <typename HashObj>
    HashTable<HashObj>::HashEntry::HashEntry(HashObj &&e, HashTable::EntryType i) : element{std::move(e)}, info{i} {
    }

    ////////////////////////////////////////////////////////////
    /// \brief HashTable<HashObj>::isActive
    /// \param currentPos
    /// \return
    ///
    template <typename HashObj>
    bool HashTable<HashObj>::isActive(int currentPos) const {
        return array[currentPos].info == ACTIVE;
    }

    ////////////////////////////////////////////////////////////
    /// \brief HashTable<HashObj>::findPos
    /// \param x
    /// \return
    ///
    template <typename HashObj>
    int HashTable<HashObj>::findPos(const HashObj &x) const {
        int offset = 1;
        int currentPos = Myhash(x);

        while (array[currentPos].info != EMPTY && array[currentPos].element != x) {
            currentPos += offset;
            offset += 2;

            if (currentPos >= array.size()) {
                currentPos -= array.size();
            }

            return currentPos;
        }
    }

    ////////////////////////////////////////////////////////////
    /// \brief HashTable<HashObj>::rehash
    ///
    template <typename HashObj>
    void HashTable<HashObj>::rehash() {
        std::vector<HashEntry> oldArray = array;

        array.resize(nextPrime(2 * oldArray.size()));
        for (auto &entry : array) {
            entry.info = EMPTY;
        }

        currentSize = 0;
        for (auto &entry : oldArray) {
            if (entry.info == ACTIVE) {
                insert(std::move(entry.element));
            }
        }
    }

    ////////////////////////////////////////////////////////////
    /// \brief HashTable<HashObj>::Myhash
    /// \param x
    /// \return
    ///
    template <typename HashObj>
    size_t HashTable<HashObj>::Myhash(const HashObj &x) const {
        static std::hash<HashObj> hf;
        return hf(x) % array.size();
    }

}  // namespace DSAA

#endif  // QUADRATICPROBING_HPP
