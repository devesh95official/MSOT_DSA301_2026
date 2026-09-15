// Greedy Arrays - 1. Jump Game

#include <bits/stdc++.h>
using namespace std;

// Only the furthest index reachable so far matters, because every index below it is
// reachable too. The moment i passes that frontier you are stuck.
bool canJump(const vector<int> &a) {
    int reach = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        if (i > reach) return false;
        reach = max(reach, i + a[i]);
    }
    return true;
}

// Level BFS without a queue: end closes the current jump, far is the best the current
// level can reach, and touching end means paying for one more jump.
int minJumps(const vector<int> &a) {
    int n = a.size(), jumps = 0, end = 0, far = 0;
    for (int i = 0; i + 1 < n; i++) {   // no jump is needed from the last index
        far = max(far, i + a[i]);
        if (i == end) {
            if (far == i) return -1;    // the level cannot move at all
            jumps++;
            end = far;
        }
    }
    return jumps;
}

int main() {
    cout << canJump({2, 3, 1, 1, 4}) << "\n";       // 1
    cout << canJump({3, 2, 1, 0, 4}) << "\n";       // 0, the 0 at index 3 is a wall
    cout << canJump({0}) << "\n";                   // 1, already at the end
    cout << canJump({0, 1}) << "\n";                // 0

    cout << minJumps({2, 3, 1, 1, 4}) << "\n";      // 2, indices 0 -> 1 -> 4
    cout << minJumps({2, 3, 0, 1, 4}) << "\n";      // 2
    cout << minJumps({1, 1, 1, 1}) << "\n";         // 3, every step is forced
    cout << minJumps({5, 1, 1, 1, 1, 1}) << "\n";   // 1
    cout << minJumps({0}) << "\n";                  // 0
    cout << minJumps({3, 2, 1, 0, 4}) << "\n";      // -1

    // A big first step is not always taken: the greedy commits to a level, not to a hop.
    {
        vector<int> a = {2, 1, 1, 1, 1};
        cout << canJump(a) << " " << minJumps(a) << "\n";    // 1 3
    }

    return 0;
}
