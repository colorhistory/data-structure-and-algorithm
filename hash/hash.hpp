#ifndef HASH_HPP
#define HASH_HPP

#include <string>

namespace DSAA {

    unsigned int hash(const std::string &key, unsigned int tableSize) {
        unsigned int hashValue = 0;

        for (auto ch : key) {
            hashValue += static_cast<unsigned int>(ch);
        }

        return hashValue % tableSize;
    }

}  // namespace DSAA

#endif  // HASH_HPP
