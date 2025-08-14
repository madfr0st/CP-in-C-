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
        long long distinctNames(vector<string>& ideas) {
            long long ans = 0;

            unordered_map<string, vector<char>> map = {};
            int count[26]={};
            vector<string> combined = {};

            for (string idea : ideas) {
                char a = idea[0];
                string b = idea.substr(1,idea.size()-1);

                if (map.find(b) != map.end()) {
                    vector<char> &c = map[b];
                    c.push_back(a);
                    map.insert({b, c});
                }
                else {
                    vector<char> c = {a};
                    map.insert({b, c});
                }
                count[a-'a']++;
                // cout << a << endl;
            }

            int sum = 0;
            for (int a:count) {
                // cout << a << '\n';
                sum += a;
            }

            for (const auto& [key, value] : map) {
                int temp_count = 0;
                // std::cout << key << ' ';
                for (char ch : value) {
                    temp_count += count[ch-'a'];
                    cout <<"::"<< temp_count << '\n';
                }
                ans+= (sum - temp_count);

            }


            return ans;
        }
    };

    
int main() {

    Solution solution = Solution();
    vector<string> ideas = {"coffee","donuts","time","toffee"};

    cout << solution.distinctNames(ideas)<< " ";

    return 0;
}
