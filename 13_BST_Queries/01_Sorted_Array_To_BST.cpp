// BST Queries - 1. Sorted Array To BST

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

// The middle element becomes the root, so both halves are equal in size and the tree is balanced.
TreeNode *toBST(const vector<int> &a, int lo, int hi) {
    if (lo > hi) return nullptr;
    int mid = lo + (hi - lo) / 2;
    TreeNode *root = new TreeNode(a[mid]);
    root->left = toBST(a, lo, mid - 1);
    root->right = toBST(a, mid + 1, hi);
    return root;
}

// Inorder of any BST is the sorted array back, so the two directions are inverses.
void toArray(TreeNode *root, vector<int> &out) {
    if (!root) return;
    toArray(root->left, out);
    out.push_back(root->val);
    toArray(root->right, out);
}

void preorder(TreeNode *root, vector<int> &out) {
    if (!root) return;
    out.push_back(root->val);
    preorder(root->left, out);
    preorder(root->right, out);
}

int height(TreeNode *root) {
    if (!root) return 0;
    return 1 + max(height(root->left), height(root->right));
}

// Inserting keys one by one in the given order, for contrast with the divide-and-conquer build.
TreeNode *insertAll(const vector<int> &a) {
    TreeNode *root = nullptr;
    for (int x : a) {
        TreeNode **cur = &root;
        while (*cur) cur = x < (*cur)->val ? &(*cur)->left : &(*cur)->right;
        *cur = new TreeNode(x);
    }
    return root;
}

void printVec(const vector<int> &v) {
    for (int x : v) cout << x << " ";
    cout << "\n";
}

int main() {
    vector<int> a = {1, 2, 3, 4, 5, 6, 7};
    TreeNode *root = toBST(a, 0, a.size() - 1);

    vector<int> pre;
    preorder(root, pre);
    printVec(pre);                      // 4 2 1 3 6 5 7

    vector<int> back;
    toArray(root, back);
    printVec(back);                     // 1 2 3 4 5 6 7
    cout << (back == a) << "\n";        // 1

    // Same keys, same BST rules, wildly different shape: height is what search actually pays.
    cout << height(root) << " " << height(insertAll(a)) << "\n";   // 3 7

    // Height stays ceil(log2(n+1)) because each level halves the remaining range.
    {
        vector<int> big(1000);
        iota(big.begin(), big.end(), 1);
        cout << height(toBST(big, 0, big.size() - 1)) << "\n";     // 10
    }

    // Even sizes are fine; the lower middle is picked, so the left half can be one shorter.
    {
        vector<int> e = {10, 20, 30, 40};
        vector<int> p;
        preorder(toBST(e, 0, e.size() - 1), p);
        printVec(p);                    // 20 10 30 40
    }

    return 0;
}
