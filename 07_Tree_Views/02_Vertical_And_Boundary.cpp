// Tree Views - 2. Vertical And Boundary

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

// Bucket by hd, then by depth, so both maps sort themselves and only ties need a vector.
void collect(TreeNode *node, int hd, int depth, map<int, map<int, vector<int>>> &g) {
    if (!node) return;
    g[hd][depth].push_back(node->val);
    collect(node->left, hd - 1, depth + 1, g);
    collect(node->right, hd + 1, depth + 1, g);
}

// One column per hd, top to bottom inside it.
vector<vector<int>> verticalOrder(TreeNode *root) {
    map<int, map<int, vector<int>>> g;
    collect(root, 0, 0, g);
    vector<vector<int>> cols;
    for (auto &[hd, byDepth] : g) {
        vector<int> col;
        for (auto &[d, vals] : byDepth)
            for (int v : vals) col.push_back(v);
        cols.push_back(col);
    }
    return cols;
}

bool isLeaf(TreeNode *n) { return n && !n->left && !n->right; }

// Hug the left edge, falling to the right only when there is no left child.
void leftBoundary(TreeNode *root, vector<int> &out) {
    for (TreeNode *n = root->left; n; n = n->left ? n->left : n->right)
        if (!isLeaf(n)) out.push_back(n->val);   // leaves belong to the leaf pass
}

// Leaves left to right; this is just a DFS that stops at leaves.
void leaves(TreeNode *node, vector<int> &out) {
    if (!node) return;
    if (isLeaf(node)) { out.push_back(node->val); return; }
    leaves(node->left, out);
    leaves(node->right, out);
}

// Right edge is collected top-down then reversed, since the boundary runs anticlockwise.
void rightBoundary(TreeNode *root, vector<int> &out) {
    vector<int> tmp;
    for (TreeNode *n = root->right; n; n = n->right ? n->right : n->left)
        if (!isLeaf(n)) tmp.push_back(n->val);
    out.insert(out.end(), tmp.rbegin(), tmp.rend());
}

vector<int> boundary(TreeNode *root) {
    vector<int> out;
    if (!root) return out;
    out.push_back(root->val);
    if (isLeaf(root)) return out;   // a lone root is its own boundary, counted once
    leftBoundary(root, out);
    leaves(root, out);
    rightBoundary(root, out);
    return out;
}

void show(string label, vector<int> &v) {
    cout << label;
    for (int x : v) cout << x << " ";
    cout << "\n";
}

int main() {
    TreeNode *root = buildSample();

    // Column -2 holds only 4; column -1 holds 2 above 7; column 0 holds 1 above 5.
    for (auto &col : verticalOrder(root)) {
        for (int v : col) cout << v << " ";
        cout << "| ";
    }
    cout << "\n";               // 4 | 2 7 | 1 5 | 3 | 6 | 8 |

    // The inner depth map is what makes two nodes in one column come out top first.
    {
        map<int, map<int, vector<int>>> g;
        collect(root, 0, 0, g);
        for (auto &[d, vals] : g[-1])
            for (int v : vals) cout << d << ":" << v << " ";
        cout << "\n";           // 1:2 3:7
    }

    // Root, then left edge, then all leaves, then the right edge upwards.
    vector<int> b = boundary(root);
    show("boundary ", b);       // 1 2 4 7 8 6 3

    // Leaves on the left and right edges must not be printed twice, hence the isLeaf skips.
    {
        TreeNode *one = new TreeNode(9);
        vector<int> s = boundary(one);
        show("single   ", s);   // 9
    }

    // A left-skewed tree has no right boundary and exactly one leaf.
    {
        TreeNode *c = new TreeNode(1);
        c->left = new TreeNode(2);
        c->left->left = new TreeNode(3);
        vector<int> s = boundary(c);
        show("chain    ", s);   // 1 2 3
    }

    return 0;
}
