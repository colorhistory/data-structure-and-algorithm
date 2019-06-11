#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include "bits/stdc++.h"

template <typename Key, typename Val>
class Dictionary {
  public:
    virtual ~Dictionary() {
    }

    // ADT
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual std::pair<const Key, Val> *find(const Key &key) const = 0;
    virtual void erase(const Key &key) = 0;
    virtual void insert(const std::pair<const Key, Val> &element) = 0;
};

#endif  // DICTIONARY_HPP
