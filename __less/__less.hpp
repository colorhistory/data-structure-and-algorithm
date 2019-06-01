#ifndef __LESS_HPP
#define __LESS_HPP

namespace DSAA {

    template <typename T1, typename T2 = T1>
    struct __less {
        bool operator()(const T1& x, const T1& y) const {
            return x < y;
        }
    };

}  // namespace DSAA

#endif  // __LESS_HPP
