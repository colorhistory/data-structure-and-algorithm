#ifndef STUDENTRECORD_HPP
#define STUDENTRECORD_HPP

#include "bits/stdc++.h"

struct StudentRecord {
    bool operator!=(const StudentRecord &x) const;
    bool operator==(const StudentRecord &x) const;

    int score;
    std::string *name;
};

std::ostream &operator<<(std::ostream &out, const StudentRecord &x) {
    out << x.score << "   " << *(x.name) << std::endl;
    return out;
}

inline bool StudentRecord::operator!=(const StudentRecord &x) const {
    return score != x.score;
}

inline bool StudentRecord::operator==(const StudentRecord &x) const {
    return score == x.score;
}

#endif  // STUDENTRECORD_HPP
