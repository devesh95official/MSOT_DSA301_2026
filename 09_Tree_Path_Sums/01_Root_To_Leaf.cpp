// Tree Path Sums - 1. Root To Leaf

#include <bits/stdc++.h>
using namespace std;

// Each file defines its own node so it runs on its own.
struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

// Sample tree for every file here, as value(left, right) with . for a missing child:
//   1(2(4, 5(7, .)), 3(., 6(., 8)))
TreeNode *buildSample() {
    TreeNode *r = new TreeNode(1);
    r->left = new TreeNode(2);
    r->right = new TreeNode(3);
    r->left->left = new TreeNode(4);
    r->left->right = new TreeNode(5);
    r->left->right->left = new TreeNode(7);
    r->right->right = new TreeNode(6);
    r->right->right->right = new TreeNode(8);
    return r;
}

// Subtract as you descend and test at the leaf; a null is not a leaf, so it fails.
bool hasPathSum(TreeNode *node, int target) {
    if (!node) return false;
    if (!node->left && !node->right) return target == node->val;
    int rest = target - node->val;
    return hasPathSum(node->left, rest) || hasPathSum(node->right, rest);
}

// Push before recursing, pop after: the pop is what makes path correct for the next branch.
void allPaths(TreeNode *node, vector<int> &path, vector<vector<int>> &out) {
    if (!node) return;
    path.push_back(node->val);
    if (!node->left && !node->right) out.push_back(path);
    else {
        allPaths(node->left, path, out);
        allPaths(node->right, path, out);
    }
    path.pop_back();
}

// Passing the string by value copies it, so there is nothing to undo.
void pathStrings(TreeNode *node, string cur, vector<string> &out) {
    if (!node) return;
    cur += (cur.empty() ? "" : "->") + to_string(node->val);
    if (!node->left && !node->right) { out.push_back(cur); return; }
    pathStrings(node->left, cur, out);
    pathStrings(node->right, cur, out);
}

// Each step shifts the number one digit left, so the leaf holds the whole value.
int sumNumbers(TreeNode *node, int cur) {
    if (!node) return 0;
    cur = cur * 10 + node->val;
    if (!node->left && !node->right) return cur;
    return sumNumbers(node->left, cur) + sumNumbers(node->right, cur);
}

int main() {
    TreeNode *root = buildSample();

    // Paths here are 1-2-4 = 7, 1-2-5-7 = 15 and 1-3-6-8 = 18.
    cout << hasPathSum(root, 7) << "\n";    // 1
    cout << hasPathSum(root, 15) << "\n";   // 1
    cout << hasPathSum(root, 18) << "\n";   // 1
    cout << hasPathSum(root, 10) << "\n";   // 0

    // 1-2-5 sums to 8 but 5 is not a leaf, so a partial path must not count.
    cout << hasPathSum(root, 8) << "\n";    // 0

    {
        vector<int> path;
        vector<vector<int>> out;
        allPaths(root, path, out);
        for (auto &p : out) {
            for (int x : p) cout << x << " ";
            cout << "\n";
        }                                   // 1 2 4 / 1 2 5 7 / 1 3 6 8
        cout << path.size() << "\n";        // 0, every push was matched by a pop
    }

    {
        vector<string> out;
        pathStrings(root, "", out);
        for (auto &s : out) cout << s << "\n";   // 1->2->4 / 1->2->5->7 / 1->3->6->8
    }

    // The three leaf numbers are 124, 1257 and 1368.
    cout << sumNumbers(root, 0) << "\n";    // 2749

    // Taking path by value needs no pop, since each branch gets its own copy. Slower.
    {
        vector<vector<int>> out;
        auto walk = [&](auto &self, TreeNode *node, vector<int> path) -> void {
            if (!node) return;
            path.push_back(node->val);
            if (!node->left && !node->right) out.push_back(path);
            self(self, node->left, path);
            self(self, node->right, path);
        };
        walk(walk, root, {});
        cout << out.size() << "\n";         // 3
    }

    return 0;
}
