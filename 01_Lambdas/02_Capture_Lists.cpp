// C++ Lambdas - 2. Capture Lists

#include <bits/stdc++.h>
using namespace std;

int main() {
    // [] sees nothing from outside. Not capturing is the usual compile error.
    {
        int n = 5;
        // auto f = [](int x) { return x + n; };   // error: n not captured
        auto g = [n](int x) { return x + n; };
        cout << g(1) << "\n";      // 6
    }

    // [=] copies everything, frozen at that moment.
    {
        int n = 3;
        auto f = [=](int x) { return x * n; };
        n = 100;
        cout << f(2) << "\n";      // 6, not 200
    }

    // [&] uses the real variables, so changes are seen outside.
    {
        int cnt = 0;
        auto hit = [&]() { cnt++; };
        hit(); hit();
        cout << cnt << "\n";       // 2
    }

    // [x] copy of x, [&x] the real x. Mixing is allowed.
    {
        int a = 1, b = 1;
        auto f = [a, &b]() { b += a; };
        f();
        cout << b << "\n";         // 2
    }

    return 0;
}
