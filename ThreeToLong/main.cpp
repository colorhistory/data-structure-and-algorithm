#include "bits/stdc++.h"

using namespace std;

long ThreeToLong(std::string s) {
    long anwser = s.at(0);

    anwser = (anwser << 8) + s.at(1);

    return (anwser << 8) + s.at(2);
}

int main() {
    std::string s = "xiaohaijin";

    for (std::string::size_type i = 0; i != 3; ++i) {
        std::cout << s.at(i) << static_cast<int>(s.at(i)) << std::endl;
    }

    std::cout << ThreeToLong(s) << std::endl;
    return 0;
}
