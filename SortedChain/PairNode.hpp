#ifndef PAIRNODE_HPP
#define PAIRNODE_HPP

#include "bits/stdc++.h"

namespace DSAA {

    template <typename Key, typename Val>
    struct PairNode {
        typedef std::pair<const Key, Val> PairType;

        PairType element;
        PairNode<Key, Val>* next;

        PairNode(const PairType& thePair) : element(thePair) {
        }

        PairNode(const PairType& thePair, PairNode<Key, Val>* theNext) : element(thePair) {
            next = theNext;
        }
    };

}  // namespace DSAA
#endif  // PAIRNODE_HPP
