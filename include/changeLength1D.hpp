#ifndef CHANGELENGTH_HPP
#define CHANGELENGTH_HPP

#include "Exception.hpp"

namespace DSAA {

    template <typename T>
    void changeLength1D(T *&array, int oldLength, int newLenght) {
        if (newLenght < 0) {
            throw IllegalParameterValue("new length must be >= 0");
        }

        T *temp = new T[newLenght];
        int number = std::min(oldLength, newLenght);
        std::copy(array, array + number, temp);
        delete[] array;
        array = temp;
    }
}  // namespace DSAA

#endif  // CHANGELENGTH_HPP
