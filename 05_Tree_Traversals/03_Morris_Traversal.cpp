// Tree Traversals - 3. Morris Traversal

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

void inorder(TreeNode *node, vector<int> &out) {
    if (!node) return;
    inorder(node->left, out);
    out.push_back(node->val);
    inorder(node->right, out);
}

// Inorder in O(1) space: borrow the null right pointer of the predecessor as a way back up.
vector<int> morrisInorder(TreeNode *root) {
    vector<int> out;
    TreeNode *cur = root;
    while (cur) {
        if (!cur->left) {
            out.push_back(cur->val);
            cur = cur->right;
        } else {
            // Rightmost node of the left subtree is cur's inorder predecessor.
            TreeNode *pred = cur->left;
            while (pred->right && pred->right != cur) pred = pred->right;
            if (!pred->right) {
                pred->right = cur;        // first visit: thread, then dive left
                cur = cur->left;
            } else {
                pred->right = nullptr;    // second visit: unthread, left is done
                out.push_back(cur->val);
                cur = cur->right;
            }
        }
    }
    return out;
}

// Same threading, but visit on the way down instead of on the way back.
vector<int> morrisPreorder(TreeNode *root) {
    vector<int> out;
    TreeNode *cur = root;
    while (cur) {
        if (!cur->left) {
            out.push_back(cur->val);
            cur = cur->right;
        } else {
            TreeNode *pred = cur->left;
            while (pred->right && pred->right != cur) pred = pred->right;
            if (!pred->right) {
                out.push_back(cur->val);
                pred->right = cur;
                cur = cur->left;
            } else {
                pred->right = nullptr;
                cur = cur->right;
            }
        }
    }
    return out;
}

void show(string label, vector<int> &v) {
    cout << label;
    for (int x : v) cout << x << " ";
    cout << "\n";
}

int main() {
    TreeNode *root = buildSample();

    // pred->right != cur is the test that tells a real edge from a thread we added.
    vector<int> m = morrisInorder(root);
    show("morris in  ", m);      // 4 2 7 5 1 3 6 8

    // Every thread is removed on the second visit, so the tree ends up as it started.
    vector<int> again;
    inorder(root, again);
    show("plain in   ", again);  // 4 2 7 5 1 3 6 8
    cout << (m == again ? "tree unchanged" : "tree damaged") << "\n";

    vector<int> p = morrisPreorder(root);
    show("morris pre ", p);      // 1 2 4 5 7 3 6 8

    return 0;
}
