// BST Operations - 1. Deletion Successor

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

void inorder(TreeNode *root, vector<int> &out) {
    if (!root) return;
    inorder(root->left, out);
    out.push_back(root->val);
    inorder(root->right, out);
}

void printAll(TreeNode *root) {
    vector<int> v;
    inorder(root, v);
    for (int x : v) cout << x << " ";
    cout << "\n";
}

// Successor: each time you step left the node you left behind is a tighter upper bound.
TreeNode *successor(TreeNode *root, int key) {
    TreeNode *res = nullptr;
    while (root) {
        if (root->val > key) { res = root; root = root->left; }
        else root = root->right;
    }
    return res;
}

// Predecessor mirrors it: record the node whenever you step right. Neither needs key present.
TreeNode *predecessor(TreeNode *root, int key) {
    TreeNode *res = nullptr;
    while (root) {
        if (root->val < key) { res = root; root = root->right; }
        else root = root->left;
    }
    return res;
}

// Three cases: no child and one child both collapse to "return the other side",
// two children copies the inorder successor's key up and deletes it from the right subtree.
TreeNode *deleteNode(TreeNode *root, int key) {
    if (!root) return nullptr;
    if (key < root->val) root->left = deleteNode(root->left, key);
    else if (key > root->val) root->right = deleteNode(root->right, key);
    else {
        if (!root->left) { TreeNode *r = root->right; delete root; return r; }
        if (!root->right) { TreeNode *l = root->left; delete root; return l; }
        TreeNode *s = root->right;
        while (s->left) s = s->left;    // smallest key greater than root, so order is preserved
        root->val = s->val;
        root->right = deleteNode(root->right, s->val);  // that node has no left child, so case 1 or 2
    }
    return root;
}

int main() {
    TreeNode *root = build({50, 30, 70, 20, 40, 60, 80});
    printAll(root);                     // 20 30 40 50 60 70 80

    cout << successor(root, 30)->val << " " << predecessor(root, 30)->val << "\n";   // 40 20
    cout << successor(root, 50)->val << " " << predecessor(root, 50)->val << "\n";   // 60 40
    cout << successor(root, 35)->val << " " << predecessor(root, 35)->val << "\n";   // 40 30, key absent

    // The extremes have no neighbour on one side, so the walk returns nullptr.
    cout << (successor(root, 80) == nullptr) << (predecessor(root, 20) == nullptr) << "\n";   // 11

    // Leaf: it just disappears.
    root = deleteNode(root, 20);
    printAll(root);                     // 30 40 50 60 70 80

    // One child: 30 now has only 40, which is spliced into 30's place.
    root = deleteNode(root, 30);
    printAll(root);                     // 40 50 60 70 80

    // Two children: 50 takes its successor 60, and the old 60 is deleted as a leaf.
    root = deleteNode(root, 50);
    printAll(root);                     // 40 60 70 80
    cout << root->val << "\n";          // 60

    // Deleting an absent key changes nothing.
    root = deleteNode(root, 99);
    printAll(root);                     // 40 60 70 80

    return 0;
}
