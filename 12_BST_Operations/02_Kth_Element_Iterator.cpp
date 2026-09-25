// BST Operations - 2. Kth Element Iterator

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

// Inorder is sorted, so the k-th node it visits is the answer. The second guard matters:
// without it the walk keeps counting ancestors on the way back up.
void kthSmallest(TreeNode *root, int k, int &cnt, int &ans) {
    if (!root || cnt >= k) return;
    kthSmallest(root->left, k, cnt, ans);
    if (cnt >= k) return;
    if (++cnt == k) ans = root->val;
    kthSmallest(root->right, k, cnt, ans);
}

// Reverse inorder (right, node, left) walks descending, so the same counter gives k-th largest.
void kthLargest(TreeNode *root, int k, int &cnt, int &ans) {
    if (!root || cnt >= k) return;
    kthLargest(root->right, k, cnt, ans);
    if (cnt >= k) return;
    if (++cnt == k) ans = root->val;
    kthLargest(root->left, k, cnt, ans);
}

// The stack holds only the left spine, so O(H) space, and next() is amortised O(1).
struct BSTIterator {
    stack<TreeNode *> st;
    BSTIterator(TreeNode *root) { pushLeft(root); }
    void pushLeft(TreeNode *n) { for (; n; n = n->left) st.push(n); }
    bool hasNext() { return !st.empty(); }
    int next() {
        TreeNode *n = st.top(); st.pop();
        pushLeft(n->right);              // the right child's spine comes next in inorder
        return n->val;
    }
};

int main() {
    TreeNode *root = build({50, 30, 70, 20, 40, 60, 80});

    for (int k = 1; k <= 7; k++) {
        int cnt = 0, ans = -1;
        kthSmallest(root, k, cnt, ans);
        cout << ans << " ";
    }
    cout << "\n";                       // 20 30 40 50 60 70 80

    {
        int cnt = 0, ans = -1;
        kthSmallest(root, 3, cnt, ans);
        cout << ans << " " << cnt << "\n";   // 40 3, only 3 nodes were counted
    }

    {
        int cnt = 0, ans = -1;
        kthLargest(root, 3, cnt, ans);
        cout << ans << "\n";            // 60
    }

    // The iterator hands out the sorted order one key at a time, without building the vector.
    {
        BSTIterator it(root);
        while (it.hasNext()) cout << it.next() << " ";
        cout << "\n";                   // 20 30 40 50 60 70 80
    }

    // k-th smallest again: call next() k times and stop.
    {
        BSTIterator it(root);
        int k = 5, ans = -1;
        while (k--) ans = it.next();
        cout << ans << "\n";            // 60
    }

    // O(H) space is a bound, not a promise: a left spine puts the whole tree on the stack.
    {
        TreeNode *deg = build({5, 4, 3, 2, 1});
        BSTIterator it(deg);
        cout << it.st.size() << " " << it.next() << "\n";   // 5 1
    }

    return 0;
}
