// Greedy Intervals - 1. Exchange Argument

#include <bits/stdc++.h>
using namespace std;

// Total waiting time is the sum of start times, so a job delays everyone behind it.
long long totalWait(const vector<int> &d) {
    long long t = 0, wait = 0;
    for (int x : d) { wait += t; t += x; }
    return wait;
}

// Weighted objective: each job costs weight * its completion time.
long long weightedCost(const vector<pair<int, int>> &jobs) {
    long long t = 0, cost = 0;
    for (auto &[dur, w] : jobs) { t += dur; cost += 1LL * w * t; }
    return cost;
}

// Brute force over every order, so the greedy claim is checked and not just asserted.
long long bestWait(vector<int> d) {
    sort(d.begin(), d.end());
    long long best = LLONG_MAX;
    do { best = min(best, totalWait(d)); } while (next_permutation(d.begin(), d.end()));
    return best;
}

long long bestWeighted(vector<pair<int, int>> jobs) {
    sort(jobs.begin(), jobs.end());
    long long best = LLONG_MAX;
    do { best = min(best, weightedCost(jobs)); } while (next_permutation(jobs.begin(), jobs.end()));
    return best;
}

int main() {
    vector<int> d = {4, 1, 3, 2};

    // Swap any adjacent pair with the longer job first: the shorter one loses more than the
    // longer one gains, so the total drops. Repeating that swap sorts by duration ascending.
    cout << totalWait(d) << "\n";       // 17, waits 0+4+5+8
    {
        vector<int> s = d;
        sort(s.begin(), s.end());
        cout << totalWait(s) << "\n";   // 10, waits 0+1+3+6
        cout << bestWait(d) << "\n";    // 10, no order beats shortest-job-first
    }

    // Plausible but wrong on a different objective: shortest-first ignores the weights.
    {
        vector<pair<int, int>> jobs = {{1, 1}, {2, 10}};   // (duration, weight)
        sort(jobs.begin(), jobs.end());                    // duration ascending
        cout << weightedCost(jobs) << "\n";                // 31, that is 1*1 + 10*3
    }

    // The exchange argument on the weighted cost gives duration/weight ascending instead.
    {
        vector<pair<int, int>> jobs = {{1, 1}, {2, 10}};
        sort(jobs.begin(), jobs.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
            return 1LL * a.first * b.second < 1LL * b.first * a.second;   // a.d/a.w < b.d/b.w
        });
        cout << weightedCost(jobs) << "\n";                // 23, the heavy job goes first
        cout << bestWeighted(jobs) << "\n";                // 23
    }

    // Same rule on a bigger instance, still optimal, and duration order is still worse.
    {
        vector<pair<int, int>> jobs = {{3, 1}, {1, 2}, {4, 6}, {2, 5}};
        sort(jobs.begin(), jobs.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
            return 1LL * a.first * b.second < 1LL * b.first * a.second;
        });
        cout << weightedCost(jobs) << " " << bestWeighted(jobs) << "\n";  // 68 68
        sort(jobs.begin(), jobs.end());
        cout << weightedCost(jobs) << "\n";                               // 83
    }

    return 0;
}
