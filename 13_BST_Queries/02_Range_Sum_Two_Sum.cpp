// BST Queries - 2. Range Sum Two Sum

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

// Prune: below lo the whole left subtree is too small, above hi the right subtree is too big.
long long rangeSum(TreeNode *root, int lo, int hi) {
    if (!root) return 0;
    if (root->val < lo) return rangeSum(root->right, lo, hi);
    if (root->val > hi) return rangeSum(root->left, lo, hi);
    return root->val + rangeSum(root->left, lo, hi) + rangeSum(root->right, lo, hi);
}

// Same pruning, counting instead of adding.
int countInRange(TreeNode *root, int lo, int hi) {
    if (!root) return 0;
    if (root->val < lo) return countInRange(root->right, lo, hi);
    if (root->val > hi) return countInRange(root->left, lo, hi);
    return 1 + countInRange(root->left, lo, hi) + countInRange(root->right, lo, hi);
}

void inorder(TreeNode *root, vector<int> &out) {
    if (!root) return;
    inorder(root->left, out);
    out.push_back(root->val);
    inorder(root->right, out);
}

// Flatten to the sorted array, then it is the ordinary two-pointer two-sum. O(N) memory.
bool twoSumFlat(TreeNode *root, int target) {
    vector<int> a;
    inorder(root, a);
    int i = 0, j = (int)a.size() - 1;
    while (i < j) {
        int s = a[i] + a[j];
        if (s == target) return true;
        if (s < target) i++;
        else j--;
    }
    return false;
}

// One iterator, walked forward or in reverse depending on the flag.
struct Iter {
    stack<TreeNode *> st;
    bool fwd;
    Iter(TreeNode *root, bool f) : fwd(f) { push(root); }
    void push(TreeNode *n) { for (; n; n = fwd ? n->left : n->right) st.push(n); }
    int next() {
        TreeNode *n = st.top(); st.pop();
        push(fwd ? n->right : n->left);
        return n->val;
    }
};

// The same two pointers without materialising the array: O(H) memory instead of O(N).
bool twoSumIter(TreeNode *root, int target) {
    if (!root) return false;
    Iter lo(root, true), hi(root, false);
    int a = lo.next(), b = hi.next();
    while (a < b) {                     // a < b also guarantees both iterators still have keys
        if (a + b == target) return true;
        if (a + b < target) a = lo.next();
        else b = hi.next();
    }
    return false;
}

int main() {
    TreeNode *root = build({10, 5, 15, 3, 7, 13, 18, 1, 6});   // sorted: 1 3 5 6 7 10 13 15 18

    cout << rangeSum(root, 7, 15) << "\n";      // 45, that is 7+10+13+15
    cout << countInRange(root, 7, 15) << "\n";  // 4
    cout << rangeSum(root, 6, 6) << "\n";       // 6
    cout << rangeSum(root, 20, 30) << "\n";     // 0, nothing in range
    cout << rangeSum(root, 0, 100) << "\n";     // 78, the whole tree

    cout << twoSumFlat(root, 9) << twoSumIter(root, 9) << "\n";     // 11, 3+6
    cout << twoSumFlat(root, 33) << twoSumIter(root, 33) << "\n";   // 11, 15+18
    cout << twoSumFlat(root, 4) << twoSumIter(root, 4) << "\n";     // 11, 1+3

    // 2 would need 1+1, and i < j forbids reusing one node.
    cout << twoSumFlat(root, 2) << twoSumIter(root, 2) << "\n";     // 00

    // A single node can never make a pair.
    {
        TreeNode *one = build({5});
        cout << twoSumFlat(one, 10) << twoSumIter(one, 10) << "\n"; // 00
    }

    return 0;
}
