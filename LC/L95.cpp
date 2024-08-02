// C++ program to illustrate the
// iterators in vector
#include <bits/stdc++.h>

#define ll long long
#define all(c) c.begin(), c.end()
#define ff first
#define ss second
const int32_t M = 1e9 + 7;

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
   public:
    // vector<TreeNode*> generateTrees(int n) {

    //    return NULL;
    // }
    bool checkTree(TreeNode* root) {
        if (root->val == root->left->val + root->right->val) {
            return true;
        }
        return false;
    }
};

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
#endif

    // vector<int> inputVector;
    // int size;
    // scanf("%lld", &size);

    // printf("%lld\n", inputVector.back());

    TreeNode* treenode = new TreeNode(10);
    TreeNode* left = new TreeNode(6);
    TreeNode* right = new TreeNode(3);

    treenode->left = left;
    treenode->right = right;

    Solution sol;
    printf("%d", sol.checkTree(treenode));

    return 0;
}
