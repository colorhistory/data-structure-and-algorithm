#include "bits/stdc++.h"

#include "ChainWithIterator.hpp"
#include "Exception.hpp"
#include "LinearList.hpp"
#include "StudentRecord.hpp"

using namespace std;
using namespace DSAA;

void BinSort(ChainWithIterator<StudentRecord> &chain, int range);

int main(int, char **) {
    StudentRecord s;
    ChainWithIterator<StudentRecord> c;
    for (int i = 1; i <= 20; i++) {
        s.score = i / 2;
        s.name = new string(s.score, 'a');
        c.insert(0, s);
    }
    cout << "The unsorted chain is" << endl;
    cout << "  " << c << endl;
    BinSort(c, 10);
    cout << "The sorted chain is" << endl;
    cout << "  " << c << endl;

    return 0;
}

void BinSort(ChainWithIterator<StudentRecord> &chain, int range) {
    ChainWithIterator<StudentRecord> *bin;
    bin = new ChainWithIterator<StudentRecord>[range + 1];

    int numberOfElements = chain.size();
    for (int i = 0; i != numberOfElements; ++i) {
        StudentRecord x = chain.get(0);
        chain.erase(0);
        bin[x.score].insert(0, x);
    }

    for (int j = range; j >= 0; --j) {
        while (!bin[j].empty()) {
            StudentRecord x = bin[j].get(0);
            bin[j].erase(0);
            chain.insert(0, x);
        }
    }
    delete[] bin;
}
