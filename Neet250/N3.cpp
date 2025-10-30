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


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
 

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {

        TreeNode* parent;
        parent = root;

        vector<TreeNode*> nodes_p;
        vector<TreeNode*> nodes_q;

        nodes_p.push_back(root);
        nodes_q.push_back(root);

        while (true) {
            if (parent->val == p->val) {
                break;
            }
            else if (parent->val > p->val) {
                parent = parent->left;
                nodes_p.push_back(parent);
            }
            else {
                parent = parent->right;
                nodes_p.push_back(parent);
            }

        }
        for (auto node : nodes_p) {
            cout << node->val << " ";
        }
        cout << endl;

        parent = root;

        while (true) {
            if (parent->val == q->val) {
                break;
            }
            else if (parent->val > q->val) {
                parent = parent->left;
                nodes_q.push_back(parent);
            }
            else {
                parent = parent->right;
                nodes_q.push_back(parent);
            }
        }
        for (auto node : nodes_q) {
            cout << node->val << " ";
        }
        cout << endl;

        int a = min(nodes_q.size(), nodes_p.size());

        for ( int i = 0; i < a; i++) {
            if (nodes_q[i] != nodes_p[i]) {
                return nodes_q[i-1];
            }
        }

        return nodes_q[a-1];
    }



};

    
int main() {
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(3);
    root->right = new TreeNode(8);

    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(4);

    root->right->left = new TreeNode(7);
    root->right->right = new TreeNode(9);

    root->left->left->left = new TreeNode(3);

    TreeNode* p = Solution().lowestCommonAncestor(root,root->left,root->left->right);

    cout << p->val << endl;




    return 0;
}
