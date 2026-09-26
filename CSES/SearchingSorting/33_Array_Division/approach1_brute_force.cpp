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

// dp[j][i] = best (smallest) max-sum splitting the first i elements into j parts
void solve() {
    int n, k; cin >> n >> k;
    vector<int> a(n), P(n + 1, 0);
    for (int i = 0; i < n; i++) { cin >> a[i]; P[i + 1] = P[i] + a[i]; }
    const int INF = LLONG_MAX;
    vector<vector<int>> dp(k + 1, vector<int>(n + 1, INF));
    dp[0][0] = 0;
    for (int j = 1; j <= k; j++)
        for (int i = 1; i <= n; i++)
            for (int p = 0; p < i; p++)
                if (dp[j - 1][p] != INF) dp[j][i] = min(dp[j][i], max(dp[j - 1][p], P[i] - P[p]));
    cout << dp[k][n] << '\n';
}

int32_t main(){
    Start();
    int t = 1;
    //cin >> t;
    while (t--) solve();
    End();
    return 0;
}
