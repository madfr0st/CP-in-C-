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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<TreeNode*> nodes;
        nodes.push_back(root);


        vector<vector<int>>* ans = new vector<vector<int>>();;


        ans->push_back(vector<int>{root->val});



        levelOrderTraverse(nodes,ans);


        // for (vector<int> a: *ans) {
        //     for (int b:a) {
        //         cout<< b << " ";
        //     }
        //     cout << endl;
        // }


        return *ans;


    }

    void levelOrderTraverse(vector<TreeNode*> nodes, vector<vector<int>>* ans) {
        vector<TreeNode*> delta = {};
        vector<int> temp;
        bool check = false;

            for (int i = 0; i < nodes.size(); i++) {
                if (nodes[i] != nullptr) {
                    if (nodes[i]->left != nullptr) {
                        temp.push_back(nodes[i]->left->val);
                        delta.push_back(nodes[i]->left);
                        check = true;
                    }
                    if (nodes[i]->right != nullptr) {
                        temp.push_back(nodes[i]->right->val);
                        delta.push_back(nodes[i]->right);
                        check = true;
                    }
                }
            }

        ans->push_back(temp);
        if (check == true) {
            levelOrderTraverse(delta,ans);
        }
    }


    vector<int> rightSideView(TreeNode* root) {
        vector<int> ans = {};
        if (root == nullptr) {
            return ans;
        }

        ans.push_back(root->val);
        // for (int a:ans) {
        //     cout << a << endl;
        // }

        rightUtil(vector<TreeNode*> {root},ans);

        // for (int a:ans) {
        //     cout << a << endl;
        // }

        return ans;


    }

    void rightUtil(vector<TreeNode*> levelNodes, vector<int> &ans) {
        vector<TreeNode*> temp = {};
        TreeNode* last;
        for (TreeNode* node: levelNodes) {
            if (node!= nullptr) {
                last = node;
                temp.push_back(node->left);
                temp.push_back(node->right);
            }

        }

        ans.push_back(last->val);
        if (temp.size()>0) {
            rightUtil(temp,ans);
        }
    }


};

    
int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);

    // root->left->left = new TreeNode(1);
    // root->left->right = new TreeNode(4);

    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(4);

    // root->left->left->left = new TreeNode(3);

    Solution().rightSideView(root);

    // cout << p->val << endl;




    return 0;
}
