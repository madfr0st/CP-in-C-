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
        int appendCharacters(string s, string t) {
            int ans = 0;
            int k = 0;
            for (int i = 0; i < s.length(); i++) {
                if (s[i] == t[k]) {
                    k++;
                }
                if (k==t.length()) {
                    break;
                }
            }
            return t.length() - k;
        }
    };

    
int main() {
    Solution solution = Solution();
    int a = solution.appendCharacters("abcd","a");
    cout << a << endl;
    return 0;
}
