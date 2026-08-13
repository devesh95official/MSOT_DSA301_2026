// Core Revision - 1. Recursion

#include <bits/stdc++.h>
using namespace std;

// Base case first, then one step towards it - a missing base case blows the stack.
long long fact(int n) {
    if (n <= 1) return 1;
    return n * fact(n - 1);
}

// Two calls per level, so this is O(2^n) and recomputes the same subproblems.
int fib(int n) {
    if (n < 2) return n;
    return fib(n - 1) + fib(n - 2);
}

// Same recursion, memoised: the shape is unchanged, only the repeats are gone.
long long fibMemo(int n, vector<long long> &memo) {
    if (n < 2) return n;
    if (memo[n] != -1) return memo[n];
    return memo[n] = fibMemo(n - 1, memo) + fibMemo(n - 2, memo);
}

// Shrink the problem by one element and trust the smaller call.
int arrSum(const vector<int> &a, int i) {
    if (i == (int)a.size()) return 0;
    return a[i] + arrSum(a, i + 1);
}

// Swap the two ends, then recurse inwards.
void revString(string &s, int l, int r) {
    if (l >= r) return;
    swap(s[l], s[r]);
    revString(s, l + 1, r - 1);
}

// Counting calls is how you see the branching factor instead of guessing it.
int calls = 0;
int fibCount(int n) {
    calls++;
    if (n < 2) return n;
    return fibCount(n - 1) + fibCount(n - 2);
}

// Indent by depth and the recursion tree prints itself.
void tree(int n, int depth) {
    cout << string(depth * 2, ' ') << "f(" << n << ")\n";
    if (n < 2) return;
    tree(n - 1, depth + 1);
    tree(n - 2, depth + 1);
}

int main() {
    cout << fact(10) << "\n";           // 3628800

    cout << fib(10) << "\n";            // 55, but fib(50) here would never finish

    {
        vector<long long> memo(51, -1);
        cout << fibMemo(50, memo) << "\n";        // 12586269025, instant
    }

    {
        vector<int> a = {1, 2, 3, 4, 5};
        cout << arrSum(a, 0) << "\n";             // 15
    }

    {
        string s = "recursion";
        revString(s, 0, (int)s.size() - 1);
        cout << s << "\n";                        // noisrucer
    }

    // Naive fib(n) makes 2*fib(n+1)-1 calls, so each +10 on n costs about 100x.
    {
        calls = 0; fibCount(10); cout << calls << "\n";       // 177
        calls = 0; fibCount(20); cout << calls << "\n";       // 21891
    }

    // Branching recursion: every node spawns f(n-1) and f(n-2).
    tree(4, 0);

    // Tail-ish recursion: one call per level, depth n, no repeated work.
    {
        function<int(int, int)> sumTo = [&](int n, int acc) {
            if (n == 0) return acc;
            return sumTo(n - 1, acc + n);
        };
        cout << sumTo(100, 0) << "\n";            // 5050
    }

    // Depth is bounded by the call stack - a few times 10^5 frames is the practical cap,
    // so deep linear recursion is safer rewritten as a loop.
    {
        int depth = 0;
        function<void(int)> down = [&](int n) {
            if (n == 0) return;
            depth++;
            down(n - 1);
        };
        down(1000);
        cout << depth << "\n";                    // 1000
    }

    return 0;
}
