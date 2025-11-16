// C++ program to illustrate the
// iterators in vector
#include <bits/stdc++.h>
#include <mutex>

using namespace std;


// int counter = 0;
mutex mx_1,mx_2,mx_3;

// void f() {
//     lock_guard<mutex> lock(mx);
//     counter++;
//     cout << counter << endl;
// }

atomic<int> counter(0);
condition_variable cond_1;



int main() {

    unique_lock<mutex> ul(mx_1);


    cond_1.wait(ul,true);



    function<void()> f = []() -> void {
        // lock_guard<mutex> lock(mx_1, adopt_lock);
        for (int i=0;i<10;i++) {
            counter++;
            cout << counter << endl;
        }
    };

    // mx_1.lock();

    cout << counter << endl;
    thread t_1(f);
    thread t_2(f);

    t_1.join();
    t_2.join();

    cout << counter << endl;



    // t_1.join();
    // t_2.join();

    return 0;

}
