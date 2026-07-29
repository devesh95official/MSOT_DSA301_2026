// C++ Lambdas - 3. STL Usage

#include <bits/stdc++.h>
using namespace std;

int main() {
    // sort: return true if a should come first.
    {
        vector<pair<int, int>> v = {{1, 30}, {2, 10}, {3, 20}};
        sort(v.begin(), v.end(), [](auto a, auto b) {
            return a.second < b.second;
        });
        for (auto p : v) cout << p.first << " " << p.second << "\n";
    }

    // priority_queue: logic is flipped, and the type needs decltype.
    {
        auto cmp = [](int a, int b) { return a > b; };
        priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
        pq.push(5); pq.push(1);
        cout << pq.top() << "\n";     // 1, min-heap
    }

    // Binary search on answer: check() with [&] reads the input directly.
    {
        long long x = 50;
        long long lo = 0, hi = x;
        auto ok = [&](long long m) { return m * m <= x; };
        while (lo < hi) {
            long long mid = (lo + hi + 1) / 2;
            if (ok(mid)) lo = mid; else hi = mid - 1;
        }
        cout << lo << "\n";           // 7
    }

    // auto params: one lambda for many types (C++14+).
    {
        auto mx = [](auto a, auto b) { return a > b ? a : b; };
        cout << mx(3, 7) << "\n";
    }

    return 0;
}
