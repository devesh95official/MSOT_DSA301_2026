// Greedy Intervals - 2. Merge And Activity Selection

#include <bits/stdc++.h>
using namespace std;

// Sort by start, then a new interval either extends the last one or begins a fresh one.
vector<pair<int, int>> mergeIntervals(vector<pair<int, int>> v) {
    sort(v.begin(), v.end());
    vector<pair<int, int>> out;
    for (auto &[s, e] : v) {
        if (!out.empty() && s <= out.back().second) out.back().second = max(out.back().second, e);
        else out.push_back({s, e});
    }
    return out;
}

// Sort by end: finishing earliest leaves the largest remaining window, and it never
// costs anything, so no other first choice can do better.
int maxNonOverlap(vector<pair<int, int>> v) {
    sort(v.begin(), v.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
        return a.second < b.second;
    });
    int cnt = 0, last = INT_MIN;
    for (auto &[s, e] : v)
        if (s >= last) { cnt++; last = e; }   // touching at a point counts as free
    return cnt;
}

// Sorting by start is the classic trap: one long interval blocks everything after it.
int maxByStart(vector<pair<int, int>> v) {
    sort(v.begin(), v.end());
    int cnt = 0, last = INT_MIN;
    for (auto &[s, e] : v)
        if (s >= last) { cnt++; last = e; }
    return cnt;
}

void printIntervals(const vector<pair<int, int>> &v) {
    for (auto &[s, e] : v) cout << "[" << s << "," << e << "] ";
    cout << "\n";
}

int main() {
    printIntervals(mergeIntervals({{1, 3}, {2, 6}, {8, 10}, {15, 18}}));   // [1,6] [8,10] [15,18]

    // Touching endpoints merge here, since [1,4] and [4,5] cover 1 to 5 with no gap.
    printIntervals(mergeIntervals({{1, 4}, {4, 5}}));              // [1,5]

    // One interval can swallow a later one entirely, hence the max on the end.
    printIntervals(mergeIntervals({{1, 10}, {2, 3}, {4, 5}}));     // [1,10]

    {
        vector<pair<int, int>> acts = {{1, 2}, {3, 4}, {0, 6}, {5, 7}, {8, 9}, {5, 9}};
        cout << maxNonOverlap(acts) << "\n";                       // 4
        cout << maxByStart(acts) << "\n";                          // 2, [0,6] wasted the morning
    }

    // Smallest case that separates the two keys.
    {
        vector<pair<int, int>> acts = {{0, 10}, {1, 2}, {3, 4}};
        cout << maxNonOverlap(acts) << " " << maxByStart(acts) << "\n";   // 2 1
    }

    // Minimum removals is just everything you could not keep.
    {
        vector<pair<int, int>> v = {{1, 2}, {2, 3}, {3, 4}, {1, 3}};
        cout << (int)v.size() - maxNonOverlap(v) << "\n";           // 1
    }
    {
        vector<pair<int, int>> v = {{1, 2}, {1, 2}, {1, 2}};
        cout << (int)v.size() - maxNonOverlap(v) << "\n";           // 2
    }

    return 0;
}
