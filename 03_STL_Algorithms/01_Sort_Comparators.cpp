// STL Algorithms - 1. Sort Comparators

#include <bits/stdc++.h>
using namespace std;

struct Student { string name; int marks; };

int main() {
    // sort is ascending by default and is O(n log n).
    {
        vector<int> v = {5, 2, 9, 1};
        sort(v.begin(), v.end());
        for (int x : v) cout << x << " ";
        cout << "\n";                   // 1 2 5 9
    }

    // Descending: greater<int>(). reverse is separate and only flips what is there.
    {
        vector<int> v = {5, 2, 9, 1};
        sort(v.begin(), v.end(), greater<int>());
        for (int x : v) cout << x << " ";
        cout << "\n";                   // 9 5 2 1
        reverse(v.begin(), v.end());
        cout << v[0] << "\n";           // 1
    }

    // A comparator answers one question: must a come strictly before b?
    {
        vector<int> v = {-3, 1, -7, 4};
        sort(v.begin(), v.end(), [](int a, int b) { return abs(a) < abs(b); });
        for (int x : v) cout << x << " ";
        cout << "\n";                   // 1 -3 4 -7
    }

    // pair sorts by first, then second, with no comparator at all.
    {
        vector<pair<int, int>> v = {{2, 5}, {1, 9}, {2, 1}};
        sort(v.begin(), v.end());
        for (auto &p : v) cout << "(" << p.first << "," << p.second << ") ";
        cout << "\n";                   // (1,9) (2,1) (2,5)
    }

    // Structs need the rule spelled out: marks descending, then name ascending.
    {
        vector<Student> s = {{"raj", 80}, {"ann", 90}, {"bob", 80}};
        sort(s.begin(), s.end(), [](const Student &a, const Student &b) {
            if (a.marks != b.marks) return a.marks > b.marks;
            return a.name < b.name;
        });
        for (auto &x : s) cout << x.name << x.marks << " ";
        cout << "\n";                   // ann90 bob80 raj80
    }

    // stable_sort preserves the input order of equal elements; sort gives no such promise.
    {
        vector<Student> s = {{"raj", 80}, {"ann", 90}, {"bob", 80}};
        stable_sort(s.begin(), s.end(), [](const Student &a, const Student &b) {
            return a.marks > b.marks;
        });
        for (auto &x : s) cout << x.name << " ";
        cout << "\n";                   // ann raj bob, raj still before bob
    }

    // <= in a comparator is a bug: it claims a comes before a, which is not a
    // strict weak ordering, and sort then reads past the array. Use < and break ties inside.
    {
        vector<Student> s = {{"raj", 80}, {"bob", 80}};
        sort(s.begin(), s.end(), [](const Student &a, const Student &b) {
            return a.marks < b.marks;           // not <=, ties just stay unordered
        });
        cout << s.size() << "\n";       // 2
    }

    // Sort indices when you must remember where each value came from.
    {
        vector<int> a = {50, 10, 40};
        vector<int> idx = {0, 1, 2};
        sort(idx.begin(), idx.end(), [&](int i, int j) { return a[i] < a[j]; });
        for (int i : idx) cout << i << ":" << a[i] << " ";
        cout << "\n";                   // 1:10 2:40 0:50
    }

    // Sorting a sub-range: the iterators are all sort ever looks at.
    {
        vector<int> v = {9, 8, 7, 1, 2};
        sort(v.begin(), v.begin() + 3);
        for (int x : v) cout << x << " ";
        cout << "\n";                   // 7 8 9 1 2
    }

    return 0;
}
