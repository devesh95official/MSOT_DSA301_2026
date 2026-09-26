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

// Same binary search, but the check JUMPS with prefix sums:
// from position p, the farthest end of a piece is the last q with P[q] - P[p] <= limit.
// Each check costs O(k log n) instead of O(n) -> great when k is small.
void solve() {
    int n, k; cin >> n >> k;
    vector<int> P(n + 1, 0);
    int mx = 0;
    for (int i = 1; i <= n; i++) { int v; cin >> v; P[i] = P[i - 1] + v; mx = max(mx, v); }

    auto possible = [&](int limit) {
        int p = 0;
        for (int piece = 0; piece < k && p < n; piece++)
            p = upper_bound(P.begin(), P.end(), P[p] + limit) - P.begin() - 1;
        return p == n;
    };
    int lo = mx, hi = P[n];
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (possible(mid)) hi = mid; else lo = mid + 1;
    }
    cout << lo << '\n';
}

int32_t main(){
    Start();
    int t = 1;
    //cin >> t;
    while (t--) solve();
    End();
    return 0;
}
