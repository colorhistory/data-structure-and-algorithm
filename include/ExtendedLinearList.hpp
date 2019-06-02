#ifndef EXTENDEDLINEARLIST_HPP
#define EXTENDEDLINEARLIST_HPP

#include "LinearList.hpp"

namespace DSAA {
    template <typename T>
    class ExtendedLinearList : public LinearList<T> {
      public:
        virtual ~ExtendedLinearList();

        // ADT
        virtual void clear() = 0;
        virtual void push_back(const T& theElement) = 0;
    };

    template <typename T>
    ExtendedLinearList<T>::~ExtendedLinearList() {
    }

}  // namespace DSAA

#endif  // EXTENDEDLINEARLIST_HPP
