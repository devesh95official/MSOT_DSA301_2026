// STL Containers - 2. Map Set

#include <bits/stdc++.h>
using namespace std;

int main() {
    // map stores keys in sorted order and every operation is O(log n).
    {
        map<string, int> m;
        m["b"] = 2;
        m["a"] = 1;
        m["c"] = 3;
        for (auto &[k, val] : m) cout << k << "=" << val << " ";
        cout << "\n";                   // a=1 b=2 c=3, insertion order is lost
    }

    // operator[] inserts a default-built value when the key is missing.
    {
        map<string, int> m;
        cout << m["ghost"] << "\n";     // 0
        cout << m.size() << "\n";       // 1, just reading it created the key
    }

    // count or find to test membership without inserting anything.
    {
        map<string, int> m = {{"a", 1}};
        cout << m.count("a") << " " << m.count("z") << "\n";      // 1 0
        auto it = m.find("z");
        cout << (it == m.end()) << " " << m.size() << "\n";       // 1 1
    }

    // Frequency counting is what map is used for most often.
    {
        string s = "abracadabra";
        map<char, int> freq;
        for (char c : s) freq[c]++;
        for (auto &[c, f] : freq) cout << c << f << " ";
        cout << "\n";                   // a5 b2 c1 d1 r2
    }

    // set is sorted unique keys; inserting a duplicate is silently ignored.
    {
        set<int> s = {5, 1, 5, 3};
        s.insert(1);
        for (int x : s) cout << x << " ";
        cout << "\n";                   // 1 3 5
    }

    // lower_bound: first element >= x. upper_bound: first element > x.
    // Use the member version; std::lower_bound on a set degrades to O(n).
    {
        set<int> s = {10, 20, 30, 40};
        cout << *s.lower_bound(20) << "\n";                  // 20
        cout << *s.upper_bound(20) << "\n";                  // 30
        cout << *s.lower_bound(25) << "\n";                  // 30, nearest above
        cout << (s.lower_bound(99) == s.end()) << "\n";      // 1, never dereference this
    }

    // The element just below x: step back from lower_bound, after checking begin().
    {
        set<int> s = {10, 20, 30};
        auto it = s.lower_bound(25);
        cout << (it == s.begin() ? -1 : *prev(it)) << "\n";   // 20
    }

    // erase(key) is safe when absent and returns how many it removed.
    // erase(iterator) needs a valid one, so guard it with find.
    {
        set<int> s = {1, 2, 3, 4};
        s.erase(3);
        auto it = s.find(1);
        if (it != s.end()) s.erase(it);
        cout << s.erase(99) << "\n";    // 0
        for (int x : s) cout << x << " ";
        cout << "\n";                   // 2 4
    }

    // multiset/multimap keep duplicates, and erase(key) wipes all of them at once.
    {
        multiset<int> ms = {5, 1, 5, 5};
        cout << ms.count(5) << "\n";    // 3
        ms.erase(ms.find(5));           // one copy only
        cout << ms.count(5) << "\n";    // 2
        ms.erase(5);
        cout << ms.count(5) << " " << ms.size() << "\n";      // 0 1
    }

    // unordered_map/set: O(1) average, but no ordering and no lower_bound.
    {
        unordered_map<string, int> um;
        um["x"] = 1;
        um["y"] = 2;
        cout << um.count("x") << " " << um.size() << "\n";    // 1 2
        unordered_set<int> us = {3, 1, 3};
        cout << us.size() << "\n";                            // 2
    }

    // Need sorted output or *_bound? map/set. Only membership and lookup? unordered_*.

    return 0;
}
