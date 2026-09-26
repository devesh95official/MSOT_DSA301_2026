#include <bits/stdc++.h>
using namespace std;

#define int            long long int
#define Start()        ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); clock_t z = clock();
#define bug(...)       __f (#__VA_ARGS__, __VA_ARGS__)
#define print(a)       for(auto x : a) cout << x << " "; cout << '\n'
#define print1(a)      for(auto x : a) cout << x.first << " " << x.second << '\n'
#define print2(a)      for (int i = 0; i < (int)a.size(); i++){print(a[i]);}
#define End()          cerr << fixed << "Run Time : " << ((double)(clock() - z) / CLOCKS_PER_SEC);

template <typename Arg1>
void __f (const char* name, Arg1&& arg1) { cout << name << " : " << arg1 << endl; }
template <typename Arg1, typename... Args>
void __f (const char* names, Arg1&& arg1, Args&&... args){
    const char* comma = strchr (names + 1, ',');
    cout.write (names, comma - names) << " : " << arg1 << " | "; __f (comma + 1, args...);
}

const int mod = 1e9+7;
const int N = 100005;

// Sliding-window minimum with a monotonic deque: O(n) total.
void solve() {
    int n, A, B; cin >> n >> A >> B;
    vector<int> P(n + 1, 0);
    for (int i = 1; i <= n; i++) { int v; cin >> v; P[i] = P[i - 1] + v; }

    deque<int> dq;                          // indices l, with P[l] increasing front -> back
    int best = LLONG_MIN;
    for (int r = A; r <= n; r++) {
        int add = r - A;                    // new allowed l
        while (!dq.empty() && P[dq.back()] >= P[add]) dq.pop_back();   // useless from now on
        dq.push_back(add);
        if (dq.front() < r - B) dq.pop_front();   // too far left: window too long
        best = max(best, P[r] - P[dq.front()]);
    }
    cout << best << '\n';
}

int32_t main(){
    Start();
    int t = 1;
    //cin >> t;
    while (t--) solve();
    End();
    return 0;
}
