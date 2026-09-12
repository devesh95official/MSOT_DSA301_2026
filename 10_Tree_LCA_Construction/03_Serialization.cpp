// Tree LCA And Construction - 3. Serialization

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

void inorder(TreeNode *node, vector<int> &out) {
    if (!node) return;
    inorder(node->left, out);
    out.push_back(node->val);
    inorder(node->right, out);
}

// Preorder plus a # for every null. The nulls are what make the shape recoverable.
void serialize(TreeNode *node, string &s) {
    if (!node) { s += "# "; return; }
    s += to_string(node->val) + " ";
    serialize(node->left, s);
    serialize(node->right, s);
}

// Read in the same preorder; the stream position is the whole state, so no index is needed.
TreeNode *deserialize(istringstream &in) {
    string tok;
    if (!(in >> tok) || tok == "#") return nullptr;
    TreeNode *node = new TreeNode(stoi(tok));
    node->left = deserialize(in);
    node->right = deserialize(in);
    return node;
}

TreeNode *fromString(string s) {
    istringstream in(s);
    return deserialize(in);
}

void show(string label, vector<int> &v) {
    cout << label;
    for (int x : v) cout << x << " ";
    cout << "\n";
}

int main() {
    TreeNode *root = buildSample();

    string s;
    serialize(root, s);
    cout << s << "\n";          // 1 2 4 # # 5 7 # # # 3 # 6 # 8 # #

    // A tree of n nodes has n+1 null links, so the string always carries n+1 hashes.
    cout << count(s.begin(), s.end(), '#') << "\n";   // 9

    TreeNode *back = fromString(s);
    vector<int> a, b;
    inorder(root, a);
    inorder(back, b);
    show("orig ", a);           // 4 2 7 5 1 3 6 8
    show("copy ", b);           // 4 2 7 5 1 3 6 8

    // Serializing the rebuilt tree must give the identical string, which is the real check.
    string t;
    serialize(back, t);
    cout << (s == t ? "round trip ok" : "mismatch") << "\n";

    // Whitespace separates tokens, so multi-digit and negative values need no extra work.
    {
        TreeNode *n = new TreeNode(-10);
        n->left = new TreeNode(203);
        n->right = new TreeNode(-4);
        string u;
        serialize(n, u);
        cout << u << "\n";      // -10 203 # # -4 # #
        string v;
        serialize(fromString(u), v);
        cout << (u == v) << "\n";   // 1
    }

    // The empty tree is a single #, and it comes back as nullptr.
    {
        string e;
        serialize(nullptr, e);
        cout << "[" << e << "]\n";                    // [# ]
        cout << (fromString(e) == nullptr) << "\n";   // 1
    }

    return 0;
}
