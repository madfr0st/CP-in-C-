#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    int dp[n + 1];
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 1;
    int parent = 2;
    for (int i = 3; i <= n; ++i) {
        if (i - parent == parent) {
            dp[i] = 1;
            parent = i;
        } else {
            dp[i] = dp[parent] + dp[i - parent];
        }
    }

    cout << "[";

    for (int i = 0; i < n; ++i) {
        cout << dp[i] << ",";
    }

    cout << dp[n] << "]";
}