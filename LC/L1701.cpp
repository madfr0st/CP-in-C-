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

#include <bits/stdc++.h>


#define ll long long
#define all(c) c.begin(), c.end()
#define ff first
#define ss second
const int32_t M = 1e9 + 7;

using namespace std;

class Solution {
    public:
        vector<int> findClosestElements(vector<int>& arr, int k, int x) {
            vector<int> ans = {};

            auto pos = lower_bound(arr.begin(),arr.end(), x);

            int a = pos - arr.begin();

            int aaa = 0;
            int bbb = 0;
            if (a>0) {
                aaa = abs(arr[a-1]-x);
            }

            if (a<arr.size()-1) {
                bbb = abs(arr[a]-x);
            }

            int l = pos - arr.begin()-1;
            int r = pos-arr.begin();


            if (aaa<bbb) {
                l = pos-arr.begin();
                r = pos-arr.begin()+1;
            }



            // cout<< l<< ": " << r << endl;
            //
            // cout << *pos << endl;

            while (k>0) {
                int l_diff = INFINITY;
                int r_diff = INFINITY;
                if (l>=0) {
                    l_diff = abs(arr[l] - x);

                }
                if (r<arr.size()) {
                    r_diff = abs(arr[r] - x);
                }
                // printf("left %d, right %d\n",l,r);
                // printf("left_d %d, right_d %d\n",l_diff,r_diff);

                if (r_diff==l_diff) {
                    ans.push_back(arr[l]);
                    l--;
                }
                else if (l_diff>r_diff) {
                    ans.push_back(arr[r]);
                    r++;
                }
                else {
                    ans.push_back(arr[l]);
                    l--;
                }
                k--;
            }
            sort(ans.begin(), ans.end());
            return ans;


        }
    };

    
int main() {



    vector<int> customers = {2,4,5,8};
    Solution s;
    vector<int> ans = s.findClosestElements(customers,2,6);
    for(int a:ans ) {
        cout<<a<<" ";
    }


    return 0;
}



