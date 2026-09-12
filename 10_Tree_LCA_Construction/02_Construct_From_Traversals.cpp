// Tree LCA And Construction - 2. Construct From Traversals

#include <bits/stdc++.h>
using namespace std;

// Each file defines its own node so it runs on its own.
struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

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

void postorder(TreeNode *node, vector<int> &out) {
    if (!node) return;
    postorder(node->left, out);
    postorder(node->right, out);
    out.push_back(node->val);
}

// Preorder gives the root; its inorder index splits the range into left and right parts.
// pi moves forward once per node, so left must be built before right.
TreeNode *fromPreIn(vector<int> &pre, int &pi, int lo, int hi, map<int, int> &idx) {
    if (lo > hi) return nullptr;
    TreeNode *node = new TreeNode(pre[pi++]);
    int m = idx[node->val];
    node->left = fromPreIn(pre, pi, lo, m - 1, idx);
    node->right = fromPreIn(pre, pi, m + 1, hi, idx);
    return node;
}

// Postorder read backwards also gives roots first, but right must now be built before left.
TreeNode *fromInPost(vector<int> &post, int &pi, int lo, int hi, map<int, int> &idx) {
    if (lo > hi) return nullptr;
    TreeNode *node = new TreeNode(post[pi--]);
    int m = idx[node->val];
    node->right = fromInPost(post, pi, m + 1, hi, idx);
    node->left = fromInPost(post, pi, lo, m - 1, idx);
    return node;
}

// Value to inorder index once, instead of scanning inorder inside every call.
map<int, int> indexOf(vector<int> &in) {
    map<int, int> idx;
    for (int i = 0; i < (int)in.size(); i++) idx[in[i]] = i;
    return idx;
}

void show(string label, vector<int> &v) {
    cout << label;
    for (int x : v) cout << x << " ";
    cout << "\n";
}

int main() {
    // Traversals of the sample tree 1(2(4, 5(7, .)), 3(., 6(., 8))).
    vector<int> pre = {1, 2, 4, 5, 7, 3, 6, 8};
    vector<int> in = {4, 2, 7, 5, 1, 3, 6, 8};
    vector<int> post = {4, 7, 5, 2, 8, 6, 3, 1};
    map<int, int> idx = indexOf(in);

    // Inorder is what tells left from right, so it must be one of the two given.
    {
        int pi = 0;
        TreeNode *root = fromPreIn(pre, pi, 0, in.size() - 1, idx);
        vector<int> a, b, c;
        preorder(root, a);
        inorder(root, b);
        postorder(root, c);
        show("pre  ", a);        // 1 2 4 5 7 3 6 8
        show("in   ", b);        // 4 2 7 5 1 3 6 8
        show("post ", c);        // 4 7 5 2 8 6 3 1
    }

    {
        int pi = post.size() - 1;
        TreeNode *root = fromInPost(post, pi, 0, in.size() - 1, idx);
        vector<int> a, b;
        preorder(root, a);
        postorder(root, b);
        show("pre  ", a);        // 1 2 4 5 7 3 6 8
        show("post ", b);        // 4 7 5 2 8 6 3 1
    }

    // The index map turns each lookup into O(log N), so building is O(N log N) not O(N^2).
    cout << idx[1] << " " << idx[4] << " " << idx[8] << "\n";   // 4 0 7

    // preorder + postorder alone is ambiguous: these two trees share both.
    {
        TreeNode *a = new TreeNode(1);
        a->left = new TreeNode(2);
        TreeNode *b = new TreeNode(1);
        b->right = new TreeNode(2);
        vector<int> pa, pb, qa, qb;
        preorder(a, pa);
        preorder(b, pb);
        postorder(a, qa);
        postorder(b, qb);
        cout << (pa == pb && qa == qb) << "\n";   // 1, same pre and post, different trees
    }

    return 0;
}
