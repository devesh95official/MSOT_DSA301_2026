// BST Basics - 2. Validation

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

TreeNode *insert(TreeNode *root, int v) {
    if (!root) return new TreeNode(v);
    if (v < root->val) root->left = insert(root->left, v);
    else if (v > root->val) root->right = insert(root->right, v);
    return root;
}

TreeNode *build(const vector<int> &a) {
    TreeNode *root = nullptr;
    for (int x : a) root = insert(root, x);
    return root;
}

// Wrong: this only compares a node with its immediate children, never with its ancestors.
bool badValid(TreeNode *root) {
    if (!root) return true;
    if (root->left && root->left->val >= root->val) return false;
    if (root->right && root->right->val <= root->val) return false;
    return badValid(root->left) && badValid(root->right);
}

// Correct: a node must fit the open range that every ancestor above it narrowed down.
// long long bounds so a node holding INT_MIN or INT_MAX still has room to compare.
bool valid(TreeNode *root, long long lo = LLONG_MIN, long long hi = LLONG_MAX) {
    if (!root) return true;
    if (root->val <= lo || root->val >= hi) return false;
    return valid(root->left, lo, root->val) && valid(root->right, root->val, hi);
}

// The same test from the other side: the inorder sequence must be strictly increasing.
bool validInorder(TreeNode *root) {
    stack<TreeNode *> st;
    TreeNode *cur = root;
    long long prev = LLONG_MIN;
    while (cur || !st.empty()) {
        while (cur) { st.push(cur); cur = cur->left; }
        cur = st.top(); st.pop();
        if (cur->val <= prev) return false;
        prev = cur->val;
        cur = cur->right;
    }
    return true;
}

int main() {
    // 6 is a left child of 15 so the parent check passes, but 6 < 10 puts it in the wrong subtree.
    TreeNode *bad = new TreeNode(10);
    bad->left = new TreeNode(5);
    bad->right = new TreeNode(15);
    bad->right->left = new TreeNode(6);
    cout << badValid(bad) << "\n";      // 1, and it is a lie
    cout << valid(bad) << validInorder(bad) << "\n";     // 00, the range of 15's left child was (10,15)

    // A genuine BST passes all three checks.
    {
        TreeNode *ok = build({10, 5, 15, 3, 7, 12, 20});
        cout << badValid(ok) << valid(ok) << validInorder(ok) << "\n";   // 111
    }

    // Strict inequalities mean duplicates are rejected, matching the insert above.
    {
        TreeNode *dup = new TreeNode(10);
        dup->left = new TreeNode(10);
        cout << valid(dup) << validInorder(dup) << "\n";  // 00
    }

    // INT_MIN as a real key: an int sentinel would compare equal to it and fail a valid tree.
    {
        TreeNode *edge = new TreeNode(INT_MIN);
        edge->right = new TreeNode(INT_MAX);
        cout << valid(edge) << validInorder(edge) << "\n";  // 11
    }

    return 0;
}
