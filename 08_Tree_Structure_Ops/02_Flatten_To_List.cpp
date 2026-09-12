// Tree Structure Ops - 2. Flatten To List

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

// Reverse postorder (right, left, node): prev is the head of the part already flattened.
void flattenRec(TreeNode *node, TreeNode *&prev) {
    if (!node) return;
    flattenRec(node->right, prev);
    flattenRec(node->left, prev);
    node->right = prev;
    node->left = nullptr;
    prev = node;
}

// O(1) space: hang cur's old right subtree off the rightmost node of its left subtree.
void flattenMorris(TreeNode *root) {
    TreeNode *cur = root;
    while (cur) {
        if (cur->left) {
            TreeNode *pred = cur->left;
            while (pred->right) pred = pred->right;
            pred->right = cur->right;
            cur->right = cur->left;
            cur->left = nullptr;
        }
        cur = cur->right;
    }
}

// Walking the chain must use right only; every left is now null.
void showChain(string label, TreeNode *head) {
    cout << label;
    for (TreeNode *n = head; n; n = n->right) cout << n->val << (n->right ? " -> " : "");
    cout << "\n";
}

void preorder(TreeNode *node, vector<int> &out) {
    if (!node) return;
    out.push_back(node->val);
    preorder(node->left, out);
    preorder(node->right, out);
}

int main() {
    // The chain must come out in preorder, so build it back to front and the root ends up first.
    {
        TreeNode *root = buildSample();
        vector<int> pre;
        preorder(root, pre);
        TreeNode *prev = nullptr;
        flattenRec(root, prev);
        showChain("rec    ", root);     // 1 -> 2 -> 4 -> 5 -> 7 -> 3 -> 6 -> 8
        for (int x : pre) cout << x << " ";
        cout << "\n";                   // 1 2 4 5 7 3 6 8, the order it had before
    }

    {
        TreeNode *root = buildSample();
        flattenMorris(root);
        showChain("morris ", root);      // 1 -> 2 -> 4 -> 5 -> 7 -> 3 -> 6 -> 8
    }

    // The result is still a tree, just right-skewed, so a preorder of it reads the chain.
    {
        TreeNode *root = buildSample();
        flattenMorris(root);
        vector<int> pre;
        preorder(root, pre);
        for (int x : pre) cout << x << " ";
        cout << "\n";                   // 1 2 4 5 7 3 6 8

        int len = 0;
        for (TreeNode *n = root; n; n = n->right) len++;
        cout << len << "\n";            // 8, the chain holds every node
    }

    // A left chain becomes a right chain in the same order.
    {
        TreeNode *c = new TreeNode(1);
        c->left = new TreeNode(2);
        c->left->left = new TreeNode(3);
        flattenMorris(c);
        showChain("chain  ", c);         // 1 -> 2 -> 3
    }

    return 0;
}
