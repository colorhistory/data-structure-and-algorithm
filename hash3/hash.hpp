#ifndef HASH_HPP
#define HASH_HPP

#include <string>

namespace DSAA {

    unsigned int hash(const std::string &key, unsigned int tableSize) {
        unsigned int hashVal = 0;
        for (auto ch : key) {
            hashVal = 37 * hashVal + static_cast<unsigned int>(ch);
        }

        return hashVal % tableSize;
    }

}  // namespace DSAA

#endif  // HASH_HPP
