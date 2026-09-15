// Greedy Arrays - 2. Gas Station

#include <bits/stdc++.h>
using namespace std;

// Invariant: if the tank goes negative at i then no station in [start..i] can be the
// answer either, since each of them starts with even less fuel, so jump start to i+1.
int startStation(const vector<int> &gas, const vector<int> &cost) {
    int total = 0, tank = 0, start = 0;
    for (int i = 0; i < (int)gas.size(); i++) {
        int d = gas[i] - cost[i];
        total += d;
        tank += d;
        if (tank < 0) { start = i + 1; tank = 0; }
    }
    return total < 0 ? -1 : start;      // total >= 0 means the surviving start does complete the loop
}

// Simulate the full circle from every station, to check the greedy answer.
int bruteStart(const vector<int> &gas, const vector<int> &cost) {
    int n = gas.size();
    for (int s = 0; s < n; s++) {
        int tank = 0;
        bool ok = true;
        for (int k = 0; k < n && ok; k++) {
            int i = (s + k) % n;
            tank += gas[i] - cost[i];
            if (tank < 0) ok = false;
        }
        if (ok) return s;
    }
    return -1;
}

int main() {
    {
        vector<int> gas = {1, 2, 3, 4, 5}, cost = {3, 4, 5, 1, 2};
        cout << startStation(gas, cost) << " " << bruteStart(gas, cost) << "\n";   // 3 3
    }

    // Total fuel is less than total cost, so no start works at all.
    {
        vector<int> gas = {2, 3, 4}, cost = {3, 4, 3};
        cout << startStation(gas, cost) << " " << bruteStart(gas, cost) << "\n";   // -1 -1
    }

    // Total exactly zero: the loop is still possible, but only from one station.
    {
        vector<int> gas = {3, 1, 1}, cost = {1, 2, 2};
        cout << startStation(gas, cost) << " " << bruteStart(gas, cost) << "\n";   // 0 0
    }

    // Surplus everywhere, so station 0 already works.
    {
        vector<int> gas = {5, 5, 5}, cost = {1, 1, 1};
        cout << startStation(gas, cost) << " " << bruteStart(gas, cost) << "\n";   // 0 0
    }

    // The answer can be the last station, found only after resetting every step before it.
    {
        vector<int> gas = {1, 1, 5}, cost = {2, 2, 1};
        cout << startStation(gas, cost) << " " << bruteStart(gas, cost) << "\n";   // 2 2
    }

    return 0;
}
