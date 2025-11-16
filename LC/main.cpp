// C++ program to illustrate the
// iterators in vector
#include <bits/stdc++.h>

using namespace std;


void delts(shared_ptr<vector<int>> &check) {

    auto kk = check;

    cout << "shared" << endl;
    for (int a: *kk) {
        cout << a << endl;
    }
}

void delts(unique_ptr<vector<int>> &check) {

    // auto kk = move(check);
    cout << "unique" << endl;
    for (int a: *check) {
        cout << a << endl;
    }
}

int main() {

    // auto p = make_unique<vector<int>>();
    // auto k = make_shared<vector<int>>();
    //
    // k->emplace_back(11);
    // k->emplace_back(123);
    // k->emplace_back(12345);
    //
    // p->push_back(10);
    // p->emplace_back(1000);
    //
    // cout << "p "<<p << endl;
    //
    // delts(p);
    // // delts(k);
    //
    // cout << "p "<< p << endl;





    // for (int a:*p) {
    //     cout << a << endl;
    // }
    //
    // char* buf;
    // buf = (char*) malloc(10);
    //
    // for (int i=0;i<10;i++) {
    //     buf[i] = 'a'+i;
    // }
    //
    // memcpy(buf,buf+2,10);
    //
    // for (auto i=buf;i<buf+10;i++) {
    //     cout << *i << " ";
    // }
    // cout << endl;

    // delete(buf);

    // int a[10];
    // int *b = new int[100];
    //
    // b[1] = 1;
    // delete b;


    // double aa = 3.12;
    // int kk = static_cast<int>(aa);
    // cout << kk << endl;
    //
    // char* p = (char*) malloc(4);
    // p[0] = 'a';
    // p[1] = 'b';
    // p[2] = 'c';
    // p[3] = 'd';
    //
    // int a = static_cast<int>(p[1]);
    // cout << a << endl;


        int x = 10;
    int& y = x;
    int *z = &x;
    int **k = &z;


    cout << x <<" " << y << " " << z << " " << k << " " << *k  << " " << **k << endl;
    cout << &x <<" " << &y << endl;
    cout << x <<" " << y << endl;






    return 0;

}
