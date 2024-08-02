// C++ program to illustrate the
// iterators in vector
#include <bits/stdc++.h>

#define ll long long
#define all(c) c.begin(),c.end()
#define ff first
#define ss second
const int32_t M = 1e9 + 7;

using namespace std;

class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int count = 0;
        for (int i = 0; i < flowerbed.size(); ++i) {
            if (flowerbed[i] == 0) {
                bool leftEmpty = (i == 0) || (flowerbed[i - 1] == 0);
                bool rightEmpty = (i == flowerbed.size() - 1) || (flowerbed[i + 1] == 0);
                if (leftEmpty && rightEmpty) {
                    flowerbed[i] = 1; // Place a flower here
                    ++count;
                    if (count >= n) return true;
                }
            }
        }
        return count >= n;
    }
};

int main() {

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#endif

    vector<int> inputVector;
    int size;
    scanf("%lld", &size);

    for (int i = 0; i < size; i++) {
        int inp;
        scanf("%d", &inp);
        inputVector.push_back(inp);
    }
    int n;

    scanf("%lld", &n);

    Solution solution;

    printf("%d", solution.canPlaceFlowers(inputVector, n));



    return 0;
}
