// STL Containers - 3. Quick Revision

#include <bits/stdc++.h>
using namespace std;

int main() {
    // vector - the default. push_back, front/back, size, sort.
    {
        vector<int> v = {4, 1, 3};
        v.push_back(2);
        sort(v.begin(), v.end());
        cout << v.size() << " " << v.front() << " " << v.back() << "\n";    // 4 1 4
    }

    // deque - both ends matter. push_front, push_back, pop_front, front.
    {
        deque<int> d = {2};
        d.push_front(1);
        d.push_back(3);
        d.pop_front();
        cout << d.front() << " " << d.back() << "\n";        // 2 3
    }

    // list - O(1) insert/erase at a held iterator, but no [i] and cache-hostile.
    {
        list<int> l = {1, 3};
        l.insert(next(l.begin()), 2);       // before the 3
        l.push_back(4);
        cout << l.size() << " " << l.back() << "\n";         // 4 4
    }

    // map - sorted keys, O(log n). [], count, find, lower_bound.
    {
        map<int, string> m = {{2, "b"}, {1, "a"}};
        m[3] = "c";
        cout << m.count(1) << " " << m.begin()->second << " "
             << m.lower_bound(2)->first << "\n";             // 1 a 2
    }

    // set - sorted unique keys. insert, count, erase, lower_bound.
    {
        set<int> s = {30, 10, 20};
        s.insert(10);
        s.erase(30);
        cout << s.size() << " " << *s.begin() << " " << *s.lower_bound(15) << "\n";   // 2 10 20
    }

    // unordered_map - fastest lookup, zero ordering. [], count, erase.
    {
        unordered_map<string, int> um;
        um["a"]++;
        um["a"]++;
        cout << um["a"] << " " << um.count("b") << "\n";      // 2 0
    }

    // The operation you repeat most decides the container.
    {
        vector<int> a = {5, 2, 8};              // indexed scan
        deque<int> q = {1};                     // sliding window
        map<int, int> report;                   // sorted output
        unordered_map<int, int> seen;           // "have I seen x?"
        set<int> active;                        // "nearest value to x?"

        for (int x : a) { seen[x]++; active.insert(x); report[x] = x * x; }
        q.push_back(9);
        cout << seen.count(8) << " " << *active.lower_bound(4) << " "
             << report.rbegin()->second << " " << q.back() << "\n";     // 1 5 64 9
    }

    // map/set nodes never move, so a reference into them survives later inserts.
    // A vector reallocation invalidates every pointer and iterator into it.
    {
        map<int, int> m = {{1, 10}};
        int &r = m[1];
        m[2] = 20;
        cout << r << " " << m.size() << "\n";                 // 10 2
    }

    return 0;
}
