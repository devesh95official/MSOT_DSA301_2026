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

// bitmask DP: dp[mask] = min gondolas for the children in mask
void solve() {
    int n, x; cin >> n >> x;
    vector<int> p(n);
    for (auto &v : p) cin >> v;
    vector<int> dp(1 << n, 1e18);
    dp[0] = 0;
    for (int mask = 1; mask < (1 << n); mask++) {
        int i = __builtin_ctzll(mask);                    // lowest child must go somewhere
        int rest = mask ^ (1LL << i);
        dp[mask] = dp[rest] + 1;                          // alone
        for (int j = 0; j < n; j++)
            if ((rest >> j & 1) && p[i] + p[j] <= x)
                dp[mask] = min(dp[mask], dp[rest ^ (1LL << j)] + 1);
    }
    cout << dp[(1 << n) - 1] << '\n';
}

int32_t main(){
    Start();
    int t = 1;
    //cin >> t;
    while (t--) solve();
    End();
    return 0;
}
