// Tree Traversals - 2. Iterative And BFS

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

// Push right before left so left comes off the stack first.
vector<int> preIter(TreeNode *root) {
    vector<int> out;
    if (!root) return out;
    stack<TreeNode *> st;
    st.push(root);
    while (!st.empty()) {
        TreeNode *n = st.top();
        st.pop();
        out.push_back(n->val);
        if (n->right) st.push(n->right);
        if (n->left) st.push(n->left);
    }
    return out;
}

// Run left as far as it goes, pop and visit, then turn right and repeat.
vector<int> inIter(TreeNode *root) {
    vector<int> out;
    stack<TreeNode *> st;
    TreeNode *cur = root;
    while (cur || !st.empty()) {
        while (cur) { st.push(cur); cur = cur->left; }
        cur = st.top();
        st.pop();
        out.push_back(cur->val);
        cur = cur->right;
    }
    return out;
}

// Two stacks: a preorder that goes right first, reversed, is postorder.
vector<int> postIter(TreeNode *root) {
    vector<int> out;
    if (!root) return out;
    stack<TreeNode *> st;
    st.push(root);
    while (!st.empty()) {
        TreeNode *n = st.top();
        st.pop();
        out.push_back(n->val);
        if (n->left) st.push(n->left);
        if (n->right) st.push(n->right);
    }
    reverse(out.begin(), out.end());
    return out;
}

void show(string label, vector<int> &v) {
    cout << label;
    for (int x : v) cout << x << " ";
    cout << "\n";
}

int main() {
    TreeNode *root = buildSample();

    vector<int> a = preIter(root), b = inIter(root), c = postIter(root);
    show("pre  ", a);           // 1 2 4 5 7 3 6 8
    show("in   ", b);           // 4 2 7 5 1 3 6 8
    show("post ", c);           // 4 7 5 2 8 6 3 1

    // Level order needs a queue, not a stack: push children, pop the front.
    {
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode *n = q.front();
            q.pop();
            cout << n->val << " ";
            if (n->left) q.push(n->left);
            if (n->right) q.push(n->right);
        }
        cout << "\n";           // 1 2 3 4 5 6 7 8
    }

    // For level-by-level, read q.size() first: that count is exactly this level.
    {
        vector<vector<int>> levels;
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty()) {
            int sz = q.size();
            vector<int> cur;
            while (sz--) {
                TreeNode *n = q.front();
                q.pop();
                cur.push_back(n->val);
                if (n->left) q.push(n->left);
                if (n->right) q.push(n->right);
            }
            levels.push_back(cur);
        }
        for (auto &lv : levels) {
            for (int x : lv) cout << x << " ";
            cout << "| ";
        }
        cout << "\n";           // 1 | 2 3 | 4 5 6 | 7 8 |
        cout << levels.size() << "\n";   // 4, the height in levels
    }

    return 0;
}
