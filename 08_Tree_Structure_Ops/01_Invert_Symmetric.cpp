// Tree Structure Ops - 1. Invert And Symmetric

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

void preorder(TreeNode *node, vector<int> &out) {
    if (!node) return;
    out.push_back(node->val);
    preorder(node->left, out);
    preorder(node->right, out);
}

void inorder(TreeNode *node, vector<int> &out) {
    if (!node) return;
    inorder(node->left, out);
    out.push_back(node->val);
    inorder(node->right, out);
}

// Swap the two children at every node; the order of swap and recursion does not matter.
TreeNode *invert(TreeNode *node) {
    if (!node) return nullptr;
    swap(node->left, node->right);
    invert(node->left);
    invert(node->right);
    return node;
}

// Symmetry is a claim about two nodes, so recurse on a pair: outer with outer, inner with inner.
bool mirrorOf(TreeNode *a, TreeNode *b) {
    if (!a && !b) return true;
    if (!a || !b) return false;
    return a->val == b->val && mirrorOf(a->left, b->right) && mirrorOf(a->right, b->left);
}

bool isSymmetric(TreeNode *root) { return !root || mirrorOf(root->left, root->right); }

// Identical is the same recursion without the crossover.
bool isSame(TreeNode *a, TreeNode *b) {
    if (!a && !b) return true;
    if (!a || !b) return false;
    return a->val == b->val && isSame(a->left, b->left) && isSame(a->right, b->right);
}

// Try isSame at every node of a; an empty pattern matches anywhere.
bool isSubtree(TreeNode *a, TreeNode *b) {
    if (!b) return true;
    if (!a) return false;
    return isSame(a, b) || isSubtree(a->left, b) || isSubtree(a->right, b);
}

void show(string label, vector<int> &v) {
    cout << label;
    for (int x : v) cout << x << " ";
    cout << "\n";
}

int main() {
    // Inverting reverses the inorder, which is the quickest way to check the result.
    {
        TreeNode *t = buildSample();
        vector<int> before, after, pre;
        inorder(t, before);
        invert(t);
        inorder(t, after);
        preorder(t, pre);
        show("in       ", before);   // 4 2 7 5 1 3 6 8
        show("in inv   ", after);    // 8 6 3 1 5 7 2 4
        show("pre inv  ", pre);      // 1 3 6 8 2 5 7 4
        cout << isSame(invert(t), buildSample()) << "\n";  // 1, inverting twice is a no-op
    }

    // A tree is symmetric iff it is its own mirror, so compare the two halves crosswise.
    {
        TreeNode *s = new TreeNode(1);
        s->left = new TreeNode(2);
        s->right = new TreeNode(2);
        s->left->left = new TreeNode(3);
        s->left->right = new TreeNode(4);
        s->right->left = new TreeNode(4);
        s->right->right = new TreeNode(3);
        cout << isSymmetric(s) << "\n";              // 1
        cout << isSymmetric(buildSample()) << "\n";  // 0

        // Equal values are not enough: the shape must mirror too.
        TreeNode *u = new TreeNode(1);
        u->left = new TreeNode(2);
        u->right = new TreeNode(2);
        u->left->right = new TreeNode(3);
        u->right->right = new TreeNode(3);
        cout << isSymmetric(u) << "\n";              // 0
    }

    {
        cout << isSame(buildSample(), buildSample()) << "\n";  // 1
        TreeNode *t = buildSample();
        t->left->left->val = 99;
        cout << isSame(t, buildSample()) << "\n";              // 0
    }

    // Subtree means a whole node plus everything under it, not a matching fragment.
    {
        TreeNode *root = buildSample();
        TreeNode *full = new TreeNode(2);
        full->left = new TreeNode(4);
        full->right = new TreeNode(5);
        full->right->left = new TreeNode(7);
        cout << isSubtree(root, full) << "\n";       // 1, subtree at node 2

        TreeNode *partial = new TreeNode(2);
        partial->left = new TreeNode(4);
        partial->right = new TreeNode(5);
        cout << isSubtree(root, partial) << "\n";    // 0, node 5 still has child 7
    }

    return 0;
}
