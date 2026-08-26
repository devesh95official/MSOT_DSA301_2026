// Tree Properties - 1. Height And Depth

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

// Counted in nodes: null is 0, a leaf is 1. Same recursion as max depth.
int height(TreeNode *node) {
    if (!node) return 0;
    return 1 + max(height(node->left), height(node->right));
}

// Wrong: a null child returns 0, so a node with one child looks like a leaf.
int minDepthWrong(TreeNode *node) {
    if (!node) return 0;
    return 1 + min(minDepthWrong(node->left), minDepthWrong(node->right));
}

// Right: only descend into a side that exists, so the path always ends at a real leaf.
int minDepth(TreeNode *node) {
    if (!node) return 0;
    if (!node->left) return 1 + minDepth(node->right);
    if (!node->right) return 1 + minDepth(node->left);
    return 1 + min(minDepth(node->left), minDepth(node->right));
}

int countNodes(TreeNode *node) {
    if (!node) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

// A leaf is a node with neither child; internal nodes contribute nothing.
int countLeaves(TreeNode *node) {
    if (!node) return 0;
    if (!node->left && !node->right) return 1;
    return countLeaves(node->left) + countLeaves(node->right);
}

// Depth of a value with root at 1, or -1 if it is not in the tree.
int depthOf(TreeNode *node, int target) {
    if (!node) return -1;
    if (node->val == target) return 1;
    int d = depthOf(node->left, target);
    if (d == -1) d = depthOf(node->right, target);
    return d == -1 ? -1 : d + 1;
}

int main() {
    TreeNode *root = buildSample();

    cout << height(root) << "\n";           // 4, path 1-2-5-7
    cout << countNodes(root) << "\n";       // 8
    cout << countLeaves(root) << "\n";      // 3, nodes 4, 7 and 8

    // Node 3 has only a right child, so the broken version stops there and reports 2.
    cout << minDepthWrong(root) << "\n";    // 2, wrong
    cout << minDepth(root) << "\n";         // 3, path 1-2-4

    cout << depthOf(root, 7) << "\n";       // 4
    cout << depthOf(root, 4) << "\n";       // 3
    cout << depthOf(root, 99) << "\n";      // -1

    // Height is a bottom-up value, depth a top-down one, so depth is usually passed in.
    {
        auto walk = [&](auto &self, TreeNode *node, int d) -> void {
            if (!node) return;
            cout << node->val << ":" << d << " ";
            self(self, node->left, d + 1);
            self(self, node->right, d + 1);
        };
        walk(walk, root, 1);
        cout << "\n";                       // 1:1 2:2 4:3 5:3 7:4 3:2 6:3 8:4
    }

    // Every leaf at the same depth means a perfect tree, so height == log2(n+1).
    {
        TreeNode *p = new TreeNode(1);
        p->left = new TreeNode(2);
        p->right = new TreeNode(3);
        p->left->left = new TreeNode(4);
        p->left->right = new TreeNode(5);
        p->right->left = new TreeNode(6);
        p->right->right = new TreeNode(7);
        cout << height(p) << " " << minDepth(p) << " " << countNodes(p) << "\n";  // 3 3 7
    }

    return 0;
}
