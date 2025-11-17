#include <bits/stdc++.h>

using namespace std;

// to do implementation

class A;

class DB {
    std::mutex mx;
    string s = "suman";

public:
    friend class A;

};

class A {
public:
    A(){};

    friend void check(DB& db) {
        cout << db.s << endl;
    }
    friend class DB;
};

int main() {

    A a;
    DB db;

    A::check


    return 0;
}