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

            int x = matrix.size();
            int y = matrix[0].size();
            
            int ans = 0;

            vector<vector<vector<vector<int>>>> dp(x, vector<vector<vector<int>>>(
                    y, vector<vector<int>>(
                        x, vector<int>(y, 0))));

            dp[0][0][0][0] = matrix[0][0];
            if (dp[0][0][0][0]==target) {
                ans = 1;
            }

            for (int i = 1; i < x; i++) {
                for (int k = 0; k <= i; k++) {
                    dp[i][0][k][0] = matrix[i][0] + dp[i - 1][0][k][0];
                    if (dp[i][0][k][0] == target) {
                        ans++;
                    }
                    cout <<   "val (" << i << ", " << 0 <<  ", " << k << ", " << 0 <<  "): " <<dp[i][0][k][0] << "\n";

                }

            }

            // cout << ans << endl;
            //
            // for (int i = 0; i < x; i++) {
            //     for (int j = 0; j < y; j++) {
            //         for (int k = 0; k < i; k++) {
            //             for (int l = 0; l < j; l++) {
            //                 cout <<   "val (" << i << ", " << j <<  ", " << k << ", " << l <<  "): " <<dp[i][j][k][l] << "\n";
            //             }
            //         }
            //     }
            // }


            for (int i = 1; i < y; i++) {
                for (int k = 0; k <= i; k++) {
                    dp[0][i][0][k] = matrix[0][i] + dp[0][i - 1][0][k];
                    if (dp[0][i][0][k] == target) {
                        ans++;
                    }
                    cout <<   "val (" << 0 << ", " << i <<  ", " << 0 << ", " << k <<  "): " <<dp[0][i][0][k] << "\n";

                }

            }

            // cout << ans << endl;

            for (int i = 1; i < x; i++) {
                for (int j = 1; j < y; j++) {
                    for (int k = 0; k <=i; k++) {
                        for (int n = 0; n <= j; n++) {
                            dp[i][j][k][n] = dp[i][j-1][k][n]
                            + dp[i-1][j][k][n]
                            - dp[i - 1][j-1][k][n]
                            + matrix[i][j];
                            cout <<   "val (" << i << ", " << j <<  ", " << k << ", " << n <<  "): " <<dp[i][j][k][n] << "\n";

                            if (dp[i][j][k][n] == target) {
                                ans++;
                            }
                        }
                    }
                }
            }

            // for (int i = 0; i < x; i++) {
            //     for (int j = 0; j < y; j++) {
            //         for (int k = 0; k < i; k++) {
            //             for (int l = 0; l < j; l++) {
            //                 cout <<   "val (" << i << ", " << j <<  ", " << k << ", " << l <<  "): " <<dp[i][j][k][l] << "\n";
            //             }
            //
            //         }
            //
            //     }
            // }




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
