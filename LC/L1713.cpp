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
        int minOperations(vector<int>& target, vector<int>& arr) {
            unordered_map<int, int> map = {};
            for (int i = 0; i < target.size(); i++) {
                map.insert({target[i], i+1});
            }

            vector<int> res;

            for (int i = 0; i < arr.size(); i++) {
                arr[i] = map.find(arr[i])!=map.end() ? map[arr[i]] : 0;
                if (arr[i] !=0) {
                    res.push_back(arr[i]);
                    // cout << res.back() << " ";
                }
            }

            unordered_map<int, int> map2 = {};
            vector<int> temp = {};

            for (int i = 0; i < res.size(); i++) {
                int a = res[i];
                auto it = lower_bound(temp.begin(), temp.end(), a);
                if (it == temp.end()) {
                    temp.push_back(a);
                }
                else {
                    *it = a;
                }
            }

            return target.size()-temp.size();


        }
    };

    
int main() {

    Solution solution = Solution();

    vector<int> target = {6,4,8,1,3,2};
    vector<int> arr = {4,7,6,2,3,8,6,1};

    cout << solution.minOperations(target, arr)<< " ";

    return 0;
}
