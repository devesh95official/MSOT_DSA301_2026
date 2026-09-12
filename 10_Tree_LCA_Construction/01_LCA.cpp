// Tree LCA And Construction - 1. LCA

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

// Both sides answering means the two targets split here, so this node is the LCA.
// If only one side answers, pass it up; a target found first is also its own ancestor.
TreeNode *lca(TreeNode *node, int p, int q) {
    if (!node) return nullptr;
    if (node->val == p || node->val == q) return node;
    TreeNode *l = lca(node->left, p, q);
    TreeNode *r = lca(node->right, p, q);
    if (l && r) return node;
    return l ? l : r;
}

// Records the route to a target; the pop_back is the undo when a branch fails.
bool pathTo(TreeNode *node, int target, vector<TreeNode *> &path) {
    if (!node) return false;
    path.push_back(node);
    if (node->val == target) return true;
    if (pathTo(node->left, target, path) || pathTo(node->right, target, path)) return true;
    path.pop_back();
    return false;
}

// Walk both routes together; the last shared node is the LCA. O(N) time but O(N) space.
TreeNode *lcaByPath(TreeNode *root, int p, int q) {
    vector<TreeNode *> a, b;
    if (!pathTo(root, p, a) || !pathTo(root, q, b)) return nullptr;
    TreeNode *ans = nullptr;
    for (size_t i = 0; i < a.size() && i < b.size() && a[i] == b[i]; i++) ans = a[i];
    return ans;
}

// Edges from node down to a value, or -1 if it is not in this subtree.
int distFrom(TreeNode *node, int target) {
    if (!node) return -1;
    if (node->val == target) return 0;
    int d = distFrom(node->left, target);
    if (d == -1) d = distFrom(node->right, target);
    return d == -1 ? -1 : d + 1;
}

// Both routes share the stretch above the LCA, so subtract it twice.
int distBetween(TreeNode *root, int p, int q) {
    TreeNode *m = lca(root, p, q);
    if (!m) return -1;
    return distFrom(m, p) + distFrom(m, q);
}

int main() {
    TreeNode *root = buildSample();

    cout << lca(root, 4, 7)->val << "\n";    // 2
    cout << lca(root, 4, 8)->val << "\n";    // 1
    cout << lca(root, 7, 5)->val << "\n";    // 5, an ancestor counts as its own ancestor
    cout << lca(root, 6, 8)->val << "\n";    // 6

    cout << lcaByPath(root, 4, 7)->val << "\n";   // 2
    cout << lcaByPath(root, 4, 8)->val << "\n";   // 1
    cout << lcaByPath(root, 6, 8)->val << "\n";   // 6

    // The recursive version assumes both values exist; here it wrongly returns the one it found.
    cout << lca(root, 4, 99)->val << "\n";        // 4
    cout << (lcaByPath(root, 4, 99) == nullptr) << "\n";   // 1, the path version can tell

    cout << distBetween(root, 4, 7) << "\n";    // 3, path 4-2-5-7
    cout << distBetween(root, 4, 8) << "\n";    // 5, path 4-2-1-3-6-8
    cout << distBetween(root, 6, 8) << "\n";    // 1
    cout << distBetween(root, 4, 4) << "\n";    // 0

    // Same answer measured from the root instead: d(p) + d(q) - 2 * d(lca).
    {
        int a = distFrom(root, 4), b = distFrom(root, 8);
        int m = distFrom(root, lca(root, 4, 8)->val);
        cout << a + b - 2 * m << "\n";       // 5
    }

    return 0;
}
