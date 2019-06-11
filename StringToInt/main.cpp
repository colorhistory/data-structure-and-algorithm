#include "bits/stdc++.h"

using namespace std;

int StringToInt(std::string s) {
    int length = static_cast<int>(s.length());
    int answer = 0;
    if (length % 2 == 1) {
        answer = s.at(length - 1);
        --length;
    }

    for (int i = 0; i != length; i += 2) {
        answer += s.at(i);
        answer += ((int)s.at(i + 1)) << 8;
    }

    return (answer < 0) ? -answer : answer;
}

int main() {
    std::cout << StringToInt("xiaohaijin") << std::endl;

    return 0;
}
