// Tree Path Sums - 2. Max Path Sum

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

// Return the best path going straight down from node; ans sees the path that bends at node.
int down(TreeNode *node, int &ans) {
    if (!node) return 0;
    int l = max(0, down(node->left, ans));    // a negative branch is worth skipping
    int r = max(0, down(node->right, ans));
    ans = max(ans, l + node->val + r);        // bend here: use both sides
    return node->val + max(l, r);             // going up: only one side can continue
}

int maxPathSum(TreeNode *root) {
    int ans = INT_MIN;
    down(root, ans);
    return ans;
}

// Root to leaf cannot bend, so there is nothing to clamp and no separate answer variable.
int maxRootToLeaf(TreeNode *node) {
    if (!node) return 0;
    if (!node->left) return node->val + maxRootToLeaf(node->right);
    if (!node->right) return node->val + maxRootToLeaf(node->left);
    return node->val + max(maxRootToLeaf(node->left), maxRootToLeaf(node->right));
}

int main() {
    TreeNode *root = buildSample();

    // Best bend is at node 1: 7-5-2 on the left, 3-6-8 on the right.
    cout << maxPathSum(root) << "\n";        // 32
    cout << maxRootToLeaf(root) << "\n";     // 18, path 1-3-6-8

    // With a negative root the answer sits below it, which is why ans is not just the root value.
    {
        TreeNode *t = new TreeNode(-10);
        t->left = new TreeNode(9);
        t->right = new TreeNode(20);
        t->right->left = new TreeNode(15);
        t->right->right = new TreeNode(7);
        cout << maxPathSum(t) << "\n";       // 42, path 15-20-7
        cout << maxRootToLeaf(t) << "\n";    // 25, path -10-20-15
    }

    // All negative: contributions clamp to 0 but ans does not, so the least bad node wins.
    {
        TreeNode *t = new TreeNode(-1);
        t->left = new TreeNode(-2);
        t->right = new TreeNode(-3);
        cout << maxPathSum(t) << "\n";       // -1
    }

    // A path of one node is legal, so a single node answers itself.
    {
        TreeNode *one = new TreeNode(-5);
        cout << maxPathSum(one) << "\n";     // -5
    }

    // The best path need not touch the root, so the bend is tested at every node.
    {
        TreeNode *t = new TreeNode(-100);
        t->left = new TreeNode(5);
        t->left->left = new TreeNode(6);
        t->left->right = new TreeNode(7);
        cout << maxPathSum(t) << "\n";       // 18, path 6-5-7 bending at node 5
        cout << maxRootToLeaf(t) << "\n";    // -88, forced through the root
    }

    return 0;
}
