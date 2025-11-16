#include <bits/stdc++.h>
#include <iostream>

using namespace std;

class Solution {
    public:
        int maxVowels(string s, int k) {
            return 0;
        }
    };

    
int main() {


    string s = "aio hello";
    string* k = &s;
    int *p = reinterpret_cast<int*>(k);
    cout<<p<<endl;
    cout<<k<<endl;
    cout<<&p<<endl;



    return 0;
}
