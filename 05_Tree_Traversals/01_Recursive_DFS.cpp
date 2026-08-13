// Tree Traversals - 1. Recursive DFS

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

// Visit, then left, then right.
void preorder(TreeNode *node, vector<int> &out) {
    if (!node) return;
    out.push_back(node->val);
    preorder(node->left, out);
    preorder(node->right, out);
}

// Left, visit, right.
void inorder(TreeNode *node, vector<int> &out) {
    if (!node) return;
    inorder(node->left, out);
    out.push_back(node->val);
    inorder(node->right, out);
}

// Left, right, visit.
void postorder(TreeNode *node, vector<int> &out) {
    if (!node) return;
    postorder(node->left, out);
    postorder(node->right, out);
    out.push_back(node->val);
}

void show(string label, vector<int> &v) {
    cout << label;
    for (int x : v) cout << x << " ";
    cout << "\n";
}

int main() {
    TreeNode *root = buildSample();

    // All three walk the tree in the same order; only the visit line moves.
    vector<int> pre, in, post;
    preorder(root, pre);
    inorder(root, in);
    postorder(root, post);
    show("pre  ", pre);         // 1 2 4 5 7 3 6 8
    show("in   ", in);          // 4 2 7 5 1 3 6 8
    show("post ", post);        // 4 7 5 2 8 6 3 1

    // Same walk as a lambda: pass the lambda to itself, and write -> void.
    {
        auto dfs = [&](auto &self, TreeNode *node) -> void {
            if (!node) return;
            cout << node->val << " ";
            self(self, node->left);
            self(self, node->right);
        };
        dfs(dfs, root);
        cout << "\n";           // 1 2 4 5 7 3 6 8
    }

    // A lambda keeps state in the capture instead of an extra parameter.
    {
        int sum = 0;
        auto total = [&](auto &self, TreeNode *node) -> void {
            if (!node) return;
            sum += node->val;
            self(self, node->left);
            self(self, node->right);
        };
        total(total, root);
        cout << sum << "\n";    // 36
    }

    // Inorder of a BST comes out sorted, which is why inorder is the BST order.
    {
        TreeNode *b = new TreeNode(5);
        b->left = new TreeNode(3);
        b->right = new TreeNode(8);
        b->left->left = new TreeNode(2);
        b->left->right = new TreeNode(4);
        b->right->left = new TreeNode(7);
        vector<int> v;
        inorder(b, v);
        show("bst  ", v);       // 2 3 4 5 7 8
    }

    return 0;
}
