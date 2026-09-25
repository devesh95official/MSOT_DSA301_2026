// BST Basics - 1. Search Insert

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

// The invariant: every key in the left subtree is smaller, every key on the right is larger.
TreeNode *insert(TreeNode *root, int v) {
    if (!root) return new TreeNode(v);
    if (v < root->val) root->left = insert(root->left, v);
    else if (v > root->val) root->right = insert(root->right, v);
    return root;                        // equal key, ignored
}

TreeNode *build(const vector<int> &a) {
    TreeNode *root = nullptr;
    for (int x : a) root = insert(root, x);
    return root;
}

// One comparison discards an entire subtree, so the cost is the height, not N.
TreeNode *searchRec(TreeNode *root, int key) {
    if (!root || root->val == key) return root;
    return key < root->val ? searchRec(root->left, key) : searchRec(root->right, key);
}

// Same walk without the call stack: O(H) time, O(1) space.
TreeNode *searchIter(TreeNode *root, int key) {
    while (root && root->val != key) root = key < root->val ? root->left : root->right;
    return root;
}

// The smallest key is the leftmost node, the largest is the rightmost.
TreeNode *findMin(TreeNode *root) {
    while (root && root->left) root = root->left;
    return root;
}

TreeNode *findMax(TreeNode *root) {
    while (root && root->right) root = root->right;
    return root;
}

// Inorder visits left, node, right, which in a BST is exactly ascending order.
void inorder(TreeNode *root, vector<int> &out) {
    if (!root) return;
    inorder(root->left, out);
    out.push_back(root->val);
    inorder(root->right, out);
}

// Nodes on the longest root-to-leaf path; an empty tree has height 0.
int height(TreeNode *root) {
    if (!root) return 0;
    return 1 + max(height(root->left), height(root->right));
}

void printAll(TreeNode *root) {
    vector<int> v;
    inorder(root, v);
    for (int x : v) cout << x << " ";
    cout << "\n";
}

int main() {
    TreeNode *root = build({50, 30, 70, 20, 40, 60, 80});
    printAll(root);                     // 20 30 40 50 60 70 80

    // A hit returns the node, a miss returns nullptr; both searches must agree.
    cout << (searchRec(root, 40) != nullptr) << (searchIter(root, 40) != nullptr) << "\n";  // 11
    cout << (searchRec(root, 45) != nullptr) << (searchIter(root, 45) != nullptr) << "\n";  // 00

    cout << findMin(root)->val << " " << findMax(root)->val << "\n";    // 20 80

    // Insert never rearranges anything: the search falls off the tree and the key lands as a leaf.
    root = insert(root, 35);
    printAll(root);                     // 20 30 35 40 50 60 70 80
    cout << searchIter(root, 35)->val << " " << height(root) << "\n";   // 35 4

    // Sorted insertion order gives every node one child, so the BST degenerates into a list.
    {
        TreeNode *bal = build({4, 2, 6, 1, 3, 5, 7});
        TreeNode *deg = build({1, 2, 3, 4, 5, 6, 7});
        cout << height(bal) << " " << height(deg) << "\n";   // 3 7, O(H) is now O(N)
        printAll(deg);                  // 1 2 3 4 5 6 7, same keys, same order
    }

    return 0;
}
