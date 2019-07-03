#ifndef HASH_SEPERATE_CHAIN_HPP
#define HASH_SEPERATE_CHAIN_HPP

#include "bits/stdc++.h"

namespace DSAA {

    ////////////////////////////////////////////////////////////
    /// \brief test if a positive number is prime
    /// \param n
    /// \return
    ///
    bool isPrime(int n) {
        if (n == 2 || n == 3) {
            return true;
        }
        if (n == 1 || n % 2 == 0) {
            return false;
        }
        for (int i = 3; i * i <= n; i += 2) {
            if (n % i == 0) {
                return false;
            }
        }

        return true;
    }

    ////////////////////////////////////////////////////////////
    /// \brief internal method to return a prime number at least
    ///        as large as n
    /// \param n
    /// \return
    ///
    int nextPrime(int n) {
        if (n % 2 == 0) {
            ++n;
        }

        for (; !isPrime(n); n += 2) {
            ;
        }

        return n;
    }

    ////////////////////////////////////////////////////////////
    /// \brief A hash routine for string objects
    /// \param key
    /// \return
    ///
    size_t hash(const std::string &key) {
        size_t hashVal = 0;
        for (auto ch : key) {
            hashVal = hashVal * 37 + ch;
        }

        return hashVal;
    }

    ////////////////////////////////////////////////////////////
    /// \brief A hash routine for ints
    /// \param key
    /// \return
    ///
    size_t hash(size_t key) {
        return key;
    }

    template <typename HashedObj>
    class HashTable {
      public:
        explicit HashTable(int size = 101);
        bool contains(const HashedObj &x) const;
        void makeEmpty();
        bool insert(const HashedObj &x);
        bool insert(HashedObj &&x);
        bool remove(const HashedObj &x);

      private:
        void rehash();
        size_t myHash(const HashedObj &x) const;

        std::vector<std::list<HashedObj>> theLists;
        int currentSize;
    };

    ////////////////////////////////////////////////////////////
    /// \brief HashTable<HashedObj>::HashTable
    /// \param size
    ///
    template <typename HashedObj>
    HashTable<HashedObj>::HashTable(int size) : currentSize{0} {
        theLists.resize(size);
    }

    ////////////////////////////////////////////////////////////
    /// \brief HashTable<HashedObj>::contains
    /// \param x
    /// \return
    ///
    template <typename HashedObj>
    bool HashTable<HashedObj>::contains(const HashedObj &x) const {
        auto &whichList = theLists[myHash(x)];
        return std::find(std::begin(whichList), std::end(whichList), x) != std::end(whichList);
    }

    ////////////////////////////////////////////////////////////
    /// \brief HashTable<HashedObj>::makeEmpty
    ///
    template <typename HashedObj>
    void HashTable<HashedObj>::makeEmpty() {
        for (auto &thisList : theLists) {
            thisList.clear();
        }
    }

    ////////////////////////////////////////////////////////////
    /// \brief HashTable<HashedObj>::insert
    /// \param x
    /// \return
    ///
    template <typename HashedObj>
    bool HashTable<HashedObj>::insert(const HashedObj &x) {
        auto &whichList = theLists[myHash(x)];
        if (find(std::begin(whichList), std::end(whichList), x) != std::end(whichList)) {
            return false;
        }
        whichList.push_back(x);

        if (++currentSize > static_cast<int>(theLists.size())) {
            rehash();
        }
        return true;
    }

    ////////////////////////////////////////////////////////////
    /// \brief HashTable<HashedObj>::insert
    /// \param x
    /// \return
    ///
    template <typename HashedObj>
    bool HashTable<HashedObj>::insert(HashedObj &&x) {
        auto &whichList = theLists[myHash(x)];
        if (std::find(whichList.begin(), whichList.end(), x) != whichList.end()) {
            return false;
        }
        whichList.push_back(std::move(x));

        if (++currentSize > static_cast<int>(theLists.size())) {
            rehash();
        }
        return true;
    }

    ////////////////////////////////////////////////////////////
    /// \brief HashTable<HashedObj>::remove
    /// \param x
    /// \return
    ///
    template <typename HashedObj>
    bool HashTable<HashedObj>::remove(const HashedObj &x) {
        auto &whichList = theLists[myHash(x)];
        auto iter = std::find(whichList.begin(), whichList.end(), x);

        if (iter == whichList.end()) {
            return false;
        }

        whichList.erase(iter);
        --currentSize;
        return true;
    }

    ////////////////////////////////////////////////////////////
    /// \brief HashTable<HashedObj>::rehash
    ///
    template <typename HashedObj>
    void HashTable<HashedObj>::rehash() {
        std::vector<std::list<HashedObj>> oldLists = theLists;
        theLists.resize(nextPrime(2 * theLists.size()));

        for (auto &thisList : theLists) {
            thisList.clear();
        }

        currentSize = 0;
        for (auto &thisList : oldLists) {
            for (auto &x : thisList) {
                insert(std::move(x));
            }
        }
    }

    ////////////////////////////////////////////////////////////
    /// \brief HashTable<HashedObj>::myHash
    /// \param x
    /// \return
    ///
    template <typename HashedObj>
    size_t HashTable<HashedObj>::myHash(const HashedObj &x) const {
        static std::hash<HashedObj> hf;
        return hf(x) % theLists.size();
    }

}  // namespace DSAA

#endif  // HASH_SEPERATE_CHAIN_HPP
