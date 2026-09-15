// Greedy Scheduling - 2. Fractional Knapsack Job Sequencing

#include <bits/stdc++.h>
using namespace std;

struct Item { int val, wt; };

struct Job { char id; int deadline, profit; };

// Because items can be cut, every unit of capacity should hold the best value per weight
// available, so ratio order is optimal. 0/1 cannot cut, so it needs DP instead.
double fractionalKnapsack(vector<Item> items, int cap) {
    sort(items.begin(), items.end(), [](const Item &a, const Item &b) {
        return 1LL * a.val * b.wt > 1LL * b.val * a.wt;     // val/wt descending, no division
    });
    double total = 0;
    for (auto &it : items) {
        if (cap == 0) break;
        int take = min(cap, it.wt);
        total += it.val * (double)take / it.wt;
        cap -= take;
    }
    return total;
}

// The same ratio order applied to whole items, which is where greedy stops being correct.
int greedyKnapsack01(vector<Item> items, int cap) {
    sort(items.begin(), items.end(), [](const Item &a, const Item &b) {
        return 1LL * a.val * b.wt > 1LL * b.val * a.wt;
    });
    int total = 0;
    for (auto &it : items)
        if (it.wt <= cap) { cap -= it.wt; total += it.val; }
    return total;
}

// Exact 0/1 by trying every subset, to expose the gap.
int best01(const vector<Item> &items, int cap) {
    int n = items.size(), best = 0;
    for (int m = 0; m < (1 << n); m++) {
        int w = 0, v = 0;
        for (int i = 0; i < n; i++)
            if (m >> i & 1) { w += items[i].wt; v += items[i].val; }
        if (w <= cap) best = max(best, v);
    }
    return best;
}

// Richest job first, placed in the latest free slot before its deadline, which keeps the
// early slots free for jobs whose deadlines leave them no choice.
pair<int, string> jobSequencing(vector<Job> jobs) {
    sort(jobs.begin(), jobs.end(), [](const Job &a, const Job &b) { return a.profit > b.profit; });
    int maxD = 0;
    for (auto &j : jobs) maxD = max(maxD, j.deadline);
    vector<char> slot(maxD + 1, '-');
    int profit = 0;
    for (auto &j : jobs)
        for (int t = min(j.deadline, maxD); t >= 1; t--)
            if (slot[t] == '-') { slot[t] = j.id; profit += j.profit; break; }
    string order;
    for (int t = 1; t <= maxD; t++)
        if (slot[t] != '-') order += slot[t];
    return {profit, order};
}

int main() {
    cout << fixed << setprecision(2);
    cout << fractionalKnapsack({{60, 10}, {100, 20}, {120, 30}}, 50) << "\n";   // 240.00, 30 of the last item

    // Capacity beyond the total weight just takes everything.
    cout << fractionalKnapsack({{60, 10}, {100, 20}}, 100) << "\n";             // 160.00

    // The best ratio grabs weight 3 and strands the last unit; two whole items were better.
    {
        vector<Item> items = {{9, 3}, {5, 2}, {5, 2}};
        cout << fractionalKnapsack(items, 4) << "\n";       // 11.50
        cout << greedyKnapsack01(items, 4) << " " << best01(items, 4) << "\n";  // 9 10
    }

    {
        auto [profit, order] = jobSequencing({{'a', 2, 100}, {'b', 1, 19}, {'c', 2, 27},
                                              {'d', 1, 25}, {'e', 3, 15}});
        cout << profit << " " << order << "\n";             // 142 cae
    }

    // All deadlines 1 means only the single richest job can run.
    {
        auto [profit, order] = jobSequencing({{'a', 1, 50}, {'b', 1, 40}, {'c', 1, 30}});
        cout << profit << " " << order << "\n";             // 50 a
    }

    // Distinct deadlines never collide, so every job gets a slot.
    {
        auto [profit, order] = jobSequencing({{'a', 4, 20}, {'b', 2, 10}, {'c', 1, 40}});
        cout << profit << " " << order << "\n";             // 70 cba
    }

    return 0;
}
