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

// try every assignment order with bitmask DP over apartments (tiny n,m only)
void solve() {
    int n, m, k; cin >> n >> m >> k;
    vector<int> a(n), b(m);
    for (auto &x : a) cin >> x;
    for (auto &x : b) cin >> x;
    // dp[i][mask] = best matches using applicants >= i, apartments in mask used
    vector<vector<int>> dp(n + 1, vector<int>(1 << m, 0));
    for (int i = n - 1; i >= 0; i--)
        for (int mask = 0; mask < (1 << m); mask++) {
            int best = dp[i + 1][mask];                 // applicant i gets nothing
            for (int j = 0; j < m; j++)
                if (!(mask >> j & 1) && abs(a[i] - b[j]) <= k)
                    best = max(best, 1 + dp[i + 1][mask | (1 << j)]);
            dp[i][mask] = best;
        }
    cout << dp[0][0] << '\n';
}

int32_t main(){
    Start();
    int t = 1;
    //cin >> t;
    while (t--) solve();
    End();
    return 0;
}
