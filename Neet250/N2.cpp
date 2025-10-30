// C++ program to illustrate the
// iterators in vector
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <complex>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>


#define ll long long
#define all(c) c.begin(), c.end()
#define ff first
#define ss second
const int32_t M = 1e9 + 7;

using namespace std;

class Solution {
    public:
        vector<int> maxSlidingWindow(vector<int>& nums, int k) {
          priority_queue<pair<int, int>> q;

            for (int i = 0; i <k; i++) {
                q.push({nums[i], i});
            }
            vector<int> res = {};
            // cout << q.top().first << " " << q.top().second << endl;
            res.push_back(q.top().first);
            cout << res.at(0) << endl;
            for (int i = k; i < nums.size(); i++) {
                q.push({nums[i], i});
                while (q.top().second <= i-k) {
                    // cout << q.top().first << " " << q.top().second << endl;
                    q.pop();
                }
                res.push_back(q.top().first);
            }
            return res;
        }
    };

    
int main() {
    vector<int> v = {1,2,1,0,4,2,6};
    Solution s;
    vector<int> res = s.maxSlidingWindow(v, 3);
    for (int a:res) {
        cout<<a<<" ";
    }
    cout<<endl;

    return 0;
}
