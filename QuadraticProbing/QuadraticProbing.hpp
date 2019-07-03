#ifndef QUADRATICPROBING_HPP
#define QUADRATICPROBING_HPP

#include "bits/stdc++.h"

namespace DSAA {
    int nextPrime(int n);

    template <typename HashObj>
    class HashTable {
      public:
        explicit HashTable(int size = 101);
        bool contains(const HashObj &x) const;

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
    };

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

}  // namespace DSAA

#endif  // QUADRATICPROBING_HPP
