// Core Revision - 2. Stack Dry Run

#include <bits/stdc++.h>
using namespace std;

// Take the stack by value so popping it here is only a local copy, bottom printed first.
void show(stack<int> s) {
    vector<int> v;
    while (!s.empty()) { v.push_back(s.top()); s.pop(); }
    reverse(v.begin(), v.end());
    cout << "[ ";
    for (int x : v) cout << x << " ";
    cout << "]";
}

// Push openers; every closer must match the top, and the stack must end empty.
bool balanced(const string &s) {
    stack<char> st;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') st.push(c);
        else {
            if (st.empty()) return false;
            char t = st.top();
            st.pop();
            if (c == ')' && t != '(') return false;
            if (c == ']' && t != '[') return false;
            if (c == '}' && t != '{') return false;
        }
    }
    return st.empty();
}

// Monotonic stack of indices: each index is pushed and popped once, so O(n) overall.
vector<int> nextGreater(const vector<int> &a) {
    int n = a.size();
    vector<int> res(n, -1);
    stack<int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.top()] < a[i]) {
            res[st.top()] = a[i];
            st.pop();
        }
        st.push(i);
    }
    return res;
}

int main() {
    // push, top, pop, size, empty - pop returns nothing, so read top() first.
    {
        stack<int> s;
        s.push(1); s.push(2); s.push(3);
        cout << s.top() << " " << s.size() << "\n";       // 3 3
        s.pop();
        cout << s.top() << " " << s.empty() << "\n";      // 2 0
    }

    // Dry run: print the whole stack after every single operation.
    {
        stack<int> s;
        for (int x : {4, 8, 1}) {
            s.push(x);
            cout << "push " << x << " -> "; show(s); cout << "\n";
        }
        while (!s.empty()) {
            cout << "pop  " << s.top() << " -> ";
            s.pop();
            show(s); cout << "\n";
        }
    }

    cout << balanced("{[()]}") << "\n";     // 1
    cout << balanced("([)]") << "\n";       // 0, right count but wrong nesting
    cout << balanced("((") << "\n";         // 0, stack left non-empty

    {
        vector<int> a = {4, 5, 2, 25};
        for (int x : nextGreater(a)) cout << x << " ";
        cout << "\n";                       // 5 25 25 -1
    }

    // Same idea dry-run: the stack only ever holds elements still waiting for a bigger one.
    {
        vector<int> a = {4, 5, 2, 25};
        stack<int> st;
        for (int i = 0; i < (int)a.size(); i++) {
            while (!st.empty() && st.top() < a[i]) st.pop();
            st.push(a[i]);
            cout << "i=" << i << " val=" << a[i] << " -> "; show(st); cout << "\n";
        }
    }

    return 0;
}
