// C++ program to illustrate the
// iterators in vector
#include <algorithm>
#include <iostream>
#include <set>
#include <string>

#include <bits/stdc++.h>


#define ll long long
#define all(c) c.begin(), c.end()
#define ff first
#define ss second
const int32_t M = 1e9 + 7;

using namespace std;

class Solution {
    public:
        int maxVowels(string s, int k) {
            
            set<char> vowels;

            vowels.insert('a');
            vowels.insert('e');
            vowels.insert('i');
            vowels.insert('o');
            vowels.insert('u');


            
            int max = 0;
            int size = s.size();
            int l = 0;
            int r = 0;

            int R = min(k,size);

         
            for(int i=0;i<R;i++){

            }
            for(int i=0;i<size;++i){
                
            }


            return 0;
        }
    };

    
int main() {

    string s = "abciiidef";
    int k = 3;
    Solution sol;
    sol.maxVowels(s,  k);

    return 0;
}
