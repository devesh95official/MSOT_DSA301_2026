// Tree Views - 1. Top And Bottom View

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

// Horizontal distance: root is 0, left child hd-1, right child hd+1. Same hd means same column.
// BFS visits shallower nodes first, so the first arrival at an hd is the one you can see.
map<int, int> topView(TreeNode *root) {
    map<int, int> col;
    queue<pair<TreeNode *, int>> q;
    q.push({root, 0});
    while (!q.empty()) {
        auto [n, hd] = q.front();
        q.pop();
        if (!col.count(hd)) col[hd] = n->val;
        if (n->left) q.push({n->left, hd - 1});
        if (n->right) q.push({n->right, hd + 1});
    }
    return col;
}

// Same walk, but overwrite so the deepest node in each column wins.
map<int, int> bottomView(TreeNode *root) {
    map<int, int> col;
    queue<pair<TreeNode *, int>> q;
    q.push({root, 0});
    while (!q.empty()) {
        auto [n, hd] = q.front();
        q.pop();
        col[hd] = n->val;
        if (n->left) q.push({n->left, hd - 1});
        if (n->right) q.push({n->right, hd + 1});
    }
    return col;
}

// DFS finishes the whole left subtree first, so it can claim an hd with a deeper node.
void topViewDfsBroken(TreeNode *node, int hd, map<int, int> &col) {
    if (!node) return;
    if (!col.count(hd)) col[hd] = node->val;
    topViewDfsBroken(node->left, hd - 1, col);
    topViewDfsBroken(node->right, hd + 1, col);
}

void show(string label, map<int, int> &col) {
    cout << label;
    for (auto [hd, v] : col) cout << v << " ";
    cout << "\n";
}

int main() {
    TreeNode *root = buildSample();

    // map keeps the columns in hd order, so printing left to right is free.
    map<int, int> t = topView(root), b = bottomView(root);
    show("top    ", t);          // 4 2 1 3 6 8
    show("bottom ", b);          // 4 7 5 3 6 8

    // Columns of this tree run from hd -2 (node 4) to hd 3 (node 8).
    for (auto [hd, v] : t) cout << hd << ":" << v << " ";
    cout << "\n";                // -2:4 -1:2 0:1 1:3 2:6 3:8

    // Nodes 5 and 7 share a column with 1 and 2, which is what the two views disagree on.
    cout << t[0] << " " << b[0] << "\n";    // 1 5
    cout << t[-1] << " " << b[-1] << "\n";  // 2 7

    // Here node 5 sits at hd 1 but four levels down, while node 3 is at hd 1 two levels down.
    {
        TreeNode *r = new TreeNode(1);
        r->left = new TreeNode(2);
        r->right = new TreeNode(3);
        r->left->right = new TreeNode(4);
        r->left->right->right = new TreeNode(5);
        map<int, int> good = topView(r), bad;
        topViewDfsBroken(r, 0, bad);
        show("bfs    ", good);   // 2 1 3
        show("dfs    ", bad);    // 2 1 5, DFS reached 5 before 3
    }

    return 0;
}
