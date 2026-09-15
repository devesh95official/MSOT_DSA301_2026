// Greedy Scheduling - 1. Min Platforms Sweep

#include <bits/stdc++.h>
using namespace std;

// Trains have no identity here: only how many are present at once matters, so sort the
// arrivals and departures separately and walk both lists.
int minPlatforms(vector<int> arr, vector<int> dep) {
    sort(arr.begin(), arr.end());
    sort(dep.begin(), dep.end());
    int n = arr.size(), i = 0, j = 0, cur = 0, best = 0;
    while (i < n) {
        if (arr[i] <= dep[j]) { cur++; i++; best = max(best, cur); }   // <= so a train arriving
        else { cur--; j++; }                                           // at another's departure waits
    }
    return best;
}

// Identical answer as events: +1 per arrival, -1 per departure, arrivals first on a tie.
int minPlatformsSweep(const vector<int> &arr, const vector<int> &dep) {
    vector<pair<int, int>> ev;
    for (int t : arr) ev.push_back({t, +1});
    for (int t : dep) ev.push_back({t, -1});
    sort(ev.begin(), ev.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
        return a.first != b.first ? a.first < b.first : a.second > b.second;
    });
    int cur = 0, best = 0;
    for (auto &[t, delta] : ev) { cur += delta; best = max(best, cur); }
    return best;
}

// Meeting rooms II: the heap top is the room that frees up first, so reuse it if it is free.
// Here a room is reusable at the exact end time, hence <= instead of <.
int minRooms(vector<pair<int, int>> mt) {
    sort(mt.begin(), mt.end());
    priority_queue<int, vector<int>, greater<int>> pq;
    for (auto &[s, e] : mt) {
        if (!pq.empty() && pq.top() <= s) pq.pop();
        pq.push(e);
    }
    return pq.size();
}

int main() {
    vector<int> arr = {900, 940, 950, 1100, 1500, 1800};
    vector<int> dep = {910, 1200, 1120, 1130, 1900, 2000};
    cout << minPlatforms(arr, dep) << " " << minPlatformsSweep(arr, dep) << "\n";   // 3 3

    // Nothing overlaps, so one platform is enough however many trains there are.
    {
        vector<int> a = {900, 1100, 1300}, d = {1000, 1200, 1400};
        cout << minPlatforms(a, d) << " " << minPlatformsSweep(a, d) << "\n";       // 1 1
    }

    // Everything overlaps, so every train needs its own platform.
    {
        vector<int> a = {900, 901, 902}, d = {1000, 1001, 1002};
        cout << minPlatforms(a, d) << " " << minPlatformsSweep(a, d) << "\n";       // 3 3
    }

    // The tie rule matters: one train leaves at 1000 and the next arrives at 1000.
    {
        vector<int> a = {900, 1000}, d = {1000, 1100};
        cout << minPlatforms(a, d) << " " << minPlatformsSweep(a, d) << "\n";       // 2 2
    }

    cout << minRooms({{0, 30}, {5, 10}, {15, 20}}) << "\n";     // 2
    cout << minRooms({{7, 10}, {2, 4}}) << "\n";                // 1
    cout << minRooms({{1, 5}, {5, 9}, {9, 12}}) << "\n";        // 1, a room frees at its end time

    return 0;
}
