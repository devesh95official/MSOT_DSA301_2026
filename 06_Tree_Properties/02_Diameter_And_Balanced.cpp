// Tree Properties - 2. Diameter And Balanced

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

// A perfect tree of 7 nodes, for the balanced case.
TreeNode *buildPerfect() {
    TreeNode *r = new TreeNode(1);
    r->left = new TreeNode(2);
    r->right = new TreeNode(3);
    r->left->left = new TreeNode(4);
    r->left->right = new TreeNode(5);
    r->right->left = new TreeNode(6);
    r->right->right = new TreeNode(7);
    return r;
}

int height(TreeNode *node) {
    if (!node) return 0;
    return 1 + max(height(node->left), height(node->right));
}

// O(N^2): height is recomputed from scratch at every node.
bool balancedNaive(TreeNode *node) {
    if (!node) return true;
    if (abs(height(node->left) - height(node->right)) > 1) return false;
    return balancedNaive(node->left) && balancedNaive(node->right);
}

// O(N): return the height, or -1 to mean "already unbalanced below here".
int heightOrFail(TreeNode *node) {
    if (!node) return 0;
    int l = heightOrFail(node->left);
    if (l == -1) return -1;
    int r = heightOrFail(node->right);
    if (r == -1) return -1;
    if (abs(l - r) > 1) return -1;
    return 1 + max(l, r);
}

bool balanced(TreeNode *node) { return heightOrFail(node) != -1; }

// Diameter in edges. Return the height, and on the way up test the path bending here.
int heightTrackingDiameter(TreeNode *node, int &best) {
    if (!node) return 0;
    int l = heightTrackingDiameter(node->left, best);
    int r = heightTrackingDiameter(node->right, best);
    best = max(best, l + r);
    return 1 + max(l, r);
}

int main() {
    TreeNode *root = buildSample();
    TreeNode *perfect = buildPerfect();

    // Node 3 has an empty left side and a height-2 right side, so the gap is 2.
    cout << balancedNaive(root) << " " << balanced(root) << "\n";        // 0 0
    cout << balancedNaive(perfect) << " " << balanced(perfect) << "\n";  // 1 1

    // The sentinel version stops climbing as soon as one node fails, so each node is visited once.
    {
        int best = 0;
        heightTrackingDiameter(root, best);
        cout << best << "\n";              // 6 edges, path 7-5-2-1-3-6-8
        cout << best + 1 << "\n";          // 7 nodes on that path
    }

    // The longest path need not pass through the root, so a per-node maximum is required.
    {
        int best = 0;
        heightTrackingDiameter(root->left, best);
        cout << best << "\n";              // 3, the best inside subtree 2 alone
    }

    {
        int best = 0;
        heightTrackingDiameter(perfect, best);
        cout << best << "\n";              // 4, e.g. 4-2-1-3-6
    }

    // A single node has height 1 and diameter 0.
    {
        TreeNode *one = new TreeNode(9);
        int best = 0;
        cout << height(one) << " " << heightTrackingDiameter(one, best) << " " << best << "\n";  // 1 1 0
    }

    return 0;
}
