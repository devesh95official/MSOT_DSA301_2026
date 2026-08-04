// STL Algorithms - 2. Binary Search

#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> v = {10, 20, 20, 20, 30, 40};       // must already be sorted

    // binary_search answers yes/no only - it never tells you where.
    cout << binary_search(v.begin(), v.end(), 20) << "\n";      // 1
    cout << binary_search(v.begin(), v.end(), 25) << "\n";      // 0

    // lower_bound: first element >= x. upper_bound: first element > x.
    cout << *lower_bound(v.begin(), v.end(), 20) << "\n";       // 20
    cout << *upper_bound(v.begin(), v.end(), 20) << "\n";       // 30

    // Subtract begin() to turn an iterator into an index.
    cout << lower_bound(v.begin(), v.end(), 20) - v.begin() << "\n";     // 1
    cout << upper_bound(v.begin(), v.end(), 20) - v.begin() << "\n";     // 4

    // The gap between the two bounds is the count of that value.
    cout << upper_bound(v.begin(), v.end(), 20) -
            lower_bound(v.begin(), v.end(), 20) << "\n";                 // 3

    // equal_range returns both bounds together.
    {
        auto [lo, hi] = equal_range(v.begin(), v.end(), 20);
        cout << hi - lo << " " << lo - v.begin() << "\n";       // 3 1
    }

    // For a missing value both bounds coincide - the slot it would be inserted at.
    {
        auto it = lower_bound(v.begin(), v.end(), 25);
        cout << it - v.begin() << " " << *it << "\n";           // 4 30
    }

    // Above the last element you get end(), which must never be dereferenced.
    cout << (lower_bound(v.begin(), v.end(), 99) == v.end()) << "\n";     // 1

    // On pairs the whole pair is compared, so pad with INT_MIN to find a key's start.
    {
        vector<pair<int, int>> a = {{1, 5}, {2, 3}, {2, 9}, {4, 1}};
        cout << lower_bound(a.begin(), a.end(), make_pair(2, INT_MIN)) - a.begin() << "\n";   // 1
    }

    // Binary search on the answer: check() must be false..false,true..true.
    // Smallest eating speed that finishes the piles within h hours.
    {
        vector<int> piles = {3, 6, 7, 11};
        int h = 8;
        auto ok = [&](int speed) {
            long long hours = 0;
            for (int p : piles) hours += (p + speed - 1) / speed;
            return hours <= h;
        };
        int lo = 1, hi = 11;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (ok(mid)) hi = mid; else lo = mid + 1;
        }
        cout << lo << "\n";             // 4
    }

    // Mirror form for the largest true value: bias mid upward or the loop never ends.
    {
        long long x = 50;
        long long lo = 0, hi = x;
        auto ok = [&](long long m) { return m * m <= x; };
        while (lo < hi) {
            long long mid = (lo + hi + 1) / 2;
            if (ok(mid)) lo = mid; else hi = mid - 1;
        }
        cout << lo << "\n";             // 7, floor of sqrt(50)
    }

    return 0;
}
