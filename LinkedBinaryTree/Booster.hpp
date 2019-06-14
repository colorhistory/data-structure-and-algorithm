#ifndef BOOSTER_HPP
#define BOOSTER_HPP

#include "bits/stdc++.h"

namespace DSAA {

    struct Booster {
        void output(std::ostream &out) const;

        int degradeToLeft;
        int degradeFromParent;

        bool boosterHere;
    };

    /*!
     * \brief Booster::output
     * \param out
     */
    void Booster::output(std::ostream &out) const {
        out << boosterHere << "   " << degradeToLeft << "   " << degradeFromParent << "   ";
    }

    /*!
     * \brief operator <<
     * \param out
     * \param x
     * \return
     */
    std::ostream &operator<<(std::ostream &out, const Booster &x) {
        x.output(out);
        return out;
    }

}  // namespace DSAA

#endif  // BOOSTER_HPP
