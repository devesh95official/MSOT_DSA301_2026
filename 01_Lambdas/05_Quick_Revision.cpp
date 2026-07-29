// C++ Lambdas - 5. Quick Revision

#include <bits/stdc++.h>
using namespace std;

struct Node { int w; };

// Long or reused logic belongs in a normal function, not a lambda.
bool cmp(Node a, Node b) { return a.w < b.w; }

int main() {
    // Use a lambda for short logic needed in one place.
    {
        vector<int> v = {3, 1, 4, 1, 5};
        sort(v.begin(), v.end(), [](auto a, auto b) { return a > b; });
        for (int x : v) cout << x << " ";
        cout << "\n";
    }

    {
        vector<Node> e = {{5}, {2}, {9}};
        sort(e.begin(), e.end(), cmp);
        for (auto n : e) cout << n.w << " ";
        cout << "\n";
    }

    // Captures:  [] nothing   [=] copy all   [&] reference all
    //            [x] copy of x   [&x] reference to x
    // Start with [&], narrow it only if needed.

    // The three patterns that cover almost every contest use.
    {
        vector<int> a = {2, 7, 4};

        sort(a.begin(), a.end(), [](int x, int y) { return x > y; });

        auto ok = [&](long long m) { return m <= a[0]; };

        auto dfs = [&](auto &self, int u) -> void {
            if (u == 0) return;
            self(self, u - 1);
        };

        for (int x : a) cout << x << " ";
        cout << "\n";
        cout << ok(5) << "\n";
        dfs(dfs, 3);
    }

    return 0;
}
