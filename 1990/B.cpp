#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t-- > 0) {
        int n, x, y;

        cin >> n >> x >> y;

        // cout << n<<x<<y;

        vector<int> ans;
        for (int i = 0; i < n; i++) {
            ans.push_back(1);
        }
        bool check = false;
	
        for (int i = x; i < n; i++) {
            if (!check) {
                ans[i] = -1;
                check = true;
            } else {
                check = false;
            }
        }
        check = false;
        for (int i = y - 2; i >= 0; i--) {
            if (!check) {
                ans[i] = -1;
                check = true;
            } else {
                check = false;
            }
        }

        for (int i = 0; i < n; i++) {
            cout << ans[i] << +" ";
        }

        cout << "\n";
    }

    return 0;
}
