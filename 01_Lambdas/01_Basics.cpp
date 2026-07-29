// C++ Lambdas - 1. Basics

#include <bits/stdc++.h>
using namespace std;

int main() {
    // A lambda is a nameless function written inline. Keep it in auto.
    auto add = [](int a, int b) {
        return a + b;
    };
    cout << add(2, 3) << "\n";      // 5

    // [capture] (params) -> ret { body }   only [] and {} are compulsory
    auto square = [](int x) { return x * x; };
    auto hi     = [] { cout << "hi\n"; };        // () dropped
    cout << square(4) << "\n";
    hi();

    // Params work like normal functions. Use & for big containers.
    auto sum = [](vector<int> &v) {
        long long s = 0;
        for (int x : v) s += x;
        return s;
    };
    vector<int> v = {1, 2, 3, 4, 5};
    cout << sum(v) << "\n";         // 15

    // Return type is deduced. Write -> T to force it.
    auto half = [](int x) { return x / 2; };
    auto sq   = [](int n) -> long long { return 1LL * n * n; };
    cout << half(9) << "\n";        // 4
    cout << sq(100000) << "\n";     // 10000000000, would overflow int

    return 0;
}

