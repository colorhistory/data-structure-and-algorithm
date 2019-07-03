#ifndef HASH_HPP
#define HASH_HPP

#include <string>

namespace DSAA {

    int hash(const std::string &key, int tableSize) {
        return (key[0] + 27 * key[1] + 729 * key[2]) % tableSize;
    }

}  // namespace DSAA

#endif  // HASH_HPP
