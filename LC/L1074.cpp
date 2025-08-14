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
        int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {

            int ans  = 0;

            for (int i = 0; i < matrix.size(); i++) {
                for (int j = 0; j < matrix[0].size(); j++) {
                    matrix[i][j] += matrix[i][j-1];
                }
            }

            for (int i = 0; i < matrix[0].size(); i++) {
                for (int j = i; j < matrix[0].size(); j++) {
                    unordered_map<int, int> mp;
                    int sum = 0;
                    mp.insert(0,1);

                    for (int k = 0; k < matrix.size(); k++) {

                        sum += matrix[k][j] - (i>0?matrix[k][j-1]:0);
                        ans+= mp.find(sum-target)!=mp.end()?mp[sum-target]:0;
                        mp[sum]++;

                    }

                }
            }


            return ans;
        }
    };

    
int main() {

    vector<vector<int>> given = {
        {0, 0, 0, 1, 1},
        {1, 1, 1, 0, 1},
        {1, 1, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 1, 1}
    };

    int target = 0;

    Solution s = Solution();
    cout << s.numSubmatrixSumTarget(given, target) << endl;

    return 0;
}
