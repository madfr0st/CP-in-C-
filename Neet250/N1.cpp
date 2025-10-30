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
#include <climits>


#define ll long long
#define all(c) c.begin(), c.end()
#define ff first
#define ss second
const int32_t M = 1e9 + 7;

using namespace std;

class Solution {
    public:
        string maxWindow(string s, string t) {

            vector<int> comp(100,0);
            for (int i = 0; i < t.length(); ++i) {
                comp[t[i]-'A']++;
            }

            // for (int a:comp) {
            //     cout << a << endl;
            // }

            vector<int> count(100, 0);
            int l=0, r=0;

            struct trip {
                int l=0, r=0, size = INT_MAX;
            };

            trip ans;

            while (l<=r && r<s.size()) {
                if (!check(count,comp)) {
                    count[s[r]-'A']++;
                    r++;
                }
                else {
                    // printf("left: %d, right: %d\n",l,r);
                    if (ans.size > (r-l)) {
                        ans.l = l;
                        ans.r = r;
                        ans.size = r-l;
                        // cout << ans.size << endl;
                    }
                    count[s[l]-'A']--;
                    l++;

                }
            }

            if (!check(count,comp)) {
                count[s[r]-'A']++;
                r++;
            }
            else {
                printf("left: %d, right: %d\n",l,r);
                if (ans.size > (r-l)) {
                    ans.l = l;
                    ans.r = r;
                    ans.size = r-l;
                    cout << ans.size << endl;
                }
                count[s[l]-'A']--;
                l++;
            }

            while (l<=r) {
                if (check(count,comp)) {
                    // printf("left: %d, right: %d\n",l,r);
                    if (ans.size > (r-l)) {
                        ans.l = l;
                        ans.r = r;
                        ans.size = r-l;
                        // cout << ans.size << endl;
                    }
                }
                count[s[l]-'A']--;
                l++;
            }

            if (ans.size==0) {
                return "";
            }

            return s.substr(ans.l, ans.r-ans.l);
        }

        bool check(vector<int> count, vector<int> comp) {
            for (int i = 0; i < count.size(); i++) {
                if (count[i] < comp[i]) {
                    return false;
                }
            }
            return true;
        }

    };

    
int main() {

    string s = "ab", t = "b";
    string ans = Solution().maxWindow(s, t);
    cout << ans << endl;


    return 0;
}
