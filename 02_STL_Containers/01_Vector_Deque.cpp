// STL Containers - 1. Vector Deque

#include <bits/stdc++.h>
using namespace std;

int main() {
    // vector is a growable array. push_back copies a value, emplace_back builds it in place.
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.emplace_back(30);
    cout << v.size() << " " << v.back() << "\n";        // 3 30

    // Range-for to read, index to write. v[i] is unchecked, v.at(i) throws.
    for (int x : v) cout << x << " ";
    cout << "\n";

    // resize changes the size, reserve only books memory for later push_backs.
    {
        vector<int> a;
        a.reserve(100);
        cout << a.size() << " " << a.capacity() << "\n";     // 0 100, still empty
        a.resize(3);
        cout << a.size() << " " << a[0] << "\n";             // 3 0, new slots are zeroed
    }

    // insert and erase in the middle are O(n) - every later element shifts.
    {
        vector<int> a = {1, 2, 3, 4, 5};
        a.insert(a.begin() + 1, 99);
        a.erase(a.begin() + 3);
        for (int x : a) cout << x << " ";
        cout << "\n";                   // 1 99 2 4 5
    }

    // Deleting every copy of a value: remove shifts them back, erase drops the tail.
    {
        vector<int> a = {1, 2, 2, 3, 2};
        a.erase(remove(a.begin(), a.end(), 2), a.end());
        for (int x : a) cout << x << " ";
        cout << "\n";                   // 1 3
    }

    // sort 
    {
        vector<int> a = {5, 1, 4, 2};
        sort(a.begin(), a.end());
        cout << a.front() << " " << a.back() << "\n";        // 1 5
    }

    // 2D vector: rows count first, then the row template.
    {
        int n = 3, m = 4;
        vector<vector<int>> g(n, vector<int>(m, 0));
        g[1][2] = 7;
        cout << g.size() << " " << g[0].size() << " " << g[1][2] << "\n";   // 3 4 7
    }

    // Growing a vector may reallocate, which invalidates old pointers and iterators.
    {
        vector<int> a = {1, 2, 3};
        cout << a.capacity() << " ";
        a.push_back(4);
        cout << a.capacity() << "\n";   // 3 6, the buffer moved
    }

    // deque: O(1) push and pop at both ends, and still indexable.
    {
        deque<int> d = {2, 3};
        d.push_front(1);
        d.push_back(4);
        d.pop_front();
        cout << d[0] << " " << d.back() << " " << d.size() << "\n";    // 2 4 3
    }

    // Prefer deque when you need the front; vector's front ops are O(n).
    // Its storage is chunked, not one block, so &d[0] is not a usable array.
    {
        deque<int> window;
        for (int x : {5, 1, 9, 3}) {
            window.push_back(x);
            if (window.size() > 2) window.pop_front();      // keep the last 2
        }
        for (int x : window) cout << x << " ";
        cout << "\n";                   // 9 3
    }

    return 0;
}
