// C++ Lambdas - 4. Recursive Lambdas

#include <bits/stdc++.h>
using namespace std;

vector<int> g[5];
int vis[5];

int main() {
    // A lambda has no name, so it cannot call itself:
    //   auto f = [](int n) { return n * f(n - 1); };   // error

    // Fix 1: take the lambda itself as the first param, call self(self, ...).
    {
        auto fact = [](auto &self, int n) -> long long {
            if (n <= 1) return 1;
            return n * self(self, n - 1);
        };
        cout << fact(fact, 5) << "\n";    // 120
    }

    // Fix 2: name it with std::function first. Readable but slower.
    {
        function<long long(int)> fact = [&](int n) {
            if (n <= 1) return 1LL;
            return n * fact(n - 1);
        };
        cout << fact(5) << "\n";          // 120
    }

    // DFS: capture graph and vis with [&], and write -> void.
    {
        g[0] = {1, 2};
        g[1] = {0, 3};
        g[2] = {0};
        g[3] = {1};

        auto dfs = [&](auto &self, int u) -> void {
            vis[u] = 1;
            cout << u << " ";
            for (int v : g[u]) if (!vis[v]) self(self, v);
        };
        dfs(dfs, 0);
        cout << "\n";
    }

    return 0;
}
