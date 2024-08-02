#include <bits/stdc++.h>

#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> trees;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        trees.push_back(a);
    }

    int paint[n][m];

    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        paint[i][0] = a;
        paint[i][1] = b;
    }

    int minPaintTop[n + 2][m + 2];
    int minPaintBottom[n + 2][m + 2];

    for (int i = 0; i <= n + 1; i++) {
        for (int j = 0; j <= m + 1; j++) {
            minPaintTop[i][j] = 214748364;
            minPaintBottom[i][j] = 214748364;
        }
    }
    for (int i = 0; i <= n + 1; ++i) {
        for (int j = 0; j <= m + 1; ++j) {
            cout << minPaintTop[i][j] << " ";
        }
        cout << endl
             << "---";  // Move to the next line after printing each row
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            minPaintTop[i][j] = min(minPaintTop[i - 1][j], paint[i - 1][j - 1]);
            minPaintBottom[n + 1 - i][j] = min(minPaintBottom[n + 2 - i][j], paint[n - i][j - 1]);
        }
    }

    for (int i = 0; i <= n + 1; ++i) {
        for (int j = 0; j <= m + 1; ++j) {
            cout << minPaintTop[i][j] << " ";
        }
        cout << endl
             << "---";  // Move to the next line after printing each row
    }

    for (int i = 0; i <= n + 1; ++i) {
        for (int j = 0; j <= m + 1; ++j) {
            cout << minPaintBottom[i][j] << " ";
        }
        cout << endl
             << "|||";  // Move to the next line after printing each row
    }

    int dp[n + 2][m + 2][k + 2];

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            for (int h = 0; h <= k; ++h) {
                dp[i][j][h] = 214748364;
                dp[0][j][h] = 0;
            }
        }
    }

    // 2 3 45 2 3 41 5 4 3 2 1 3 5 6 66

    for (int j = 0; j <= m + 1; j++) {
        // minLeft[j] = 214748364;
        // minRight[j] = 214748364;
    }

    for (int i = 1; i <= n; i++) {
        for (int h = 1; h <= k; h++) {
            if (trees[i - 1] != 0) {
                for (int j = 0; j <= m; j++) {
                    if (trees[i - 1] == j) {
                        dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j][k]);
                    } else {
                        dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j][k-1]);
                    }
                    dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j][k - 1] + min(minPaintTop[i][j - 1], minPaintBottom[i][j + 1]));
                    dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j][k] + min(minPaintTop[i][j], minPaintBottom[i][j]));
                    //    dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j][k - 1] + min(paint[j][i], min(minLeft[j], minRight[j])));
                }
            } else {
                for (int j = 0; j <= m; j++) {
                    dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j][k - 1] + min(minPaintTop[i][j - 1], minPaintBottom[i][j + 1]));
                    dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j][k] + min(minPaintTop[i][j], minPaintBottom[i][j]));
                    //    dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j][k - 1] + min(paint[j][i], min(minLeft[j], minRight[j])));
                }
            }
        }
    }

    for (int p = 0; p < m; ++p) {
        //   cout << minLeft[p] << " ";

        cout << endl;  // Move to the next line after printing each row
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int h = 0; h < k; ++h) {
                cout << "array[" << i << "][" << j << "][" << k << "] = " << dp[i][j][h] << endl;
            }
        }
    }

    return 0;
}