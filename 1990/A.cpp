#include <bits/stdc++.h>

using namespace std;

bool check(vector<int> v) {
    int ans = 0;
    int max = v.back();
    for (int i = 0; i < v.size(); i++) {
        int a = v[v.size() - i - 1];
        if (a == max) {
            ans++;
        } else {
            if (ans % 2 == 1) {
                return true;
            }
			max = a;
            ans = 1;
        }
    }

    if (ans % 2 == 1) {
        return true;
    }

    return false;
}

int main() {
    int t;
    cin >> t;

    while (t-- > 0) {
        int size;
        cin >> size;
        vector<int> n;
        while (size-- > 0) {
            int a;
            cin >> a;
            n.push_back(a);
        }

        sort(n.begin(), n.end());

        bool ans = check(n);

        if (ans) {
            cout << "YES";
            cout << "\n";
        } else {
            cout << "NO";
            cout << "\n";
        }
    }

    return 0;
}