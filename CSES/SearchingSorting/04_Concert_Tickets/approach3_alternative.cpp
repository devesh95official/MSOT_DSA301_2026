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

// Sorted prices + DSU "jump left": par[i] = nearest index <= i that is still unsold
// index 0 is a sentinel meaning "no ticket available"
vector<int> par;
int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }

void solve() {
    int n, m; cin >> n >> m;
    vector<int> h(n + 1);
    for (int i = 1; i <= n; i++) cin >> h[i];
    sort(h.begin() + 1, h.end());
    par.resize(n + 1);
    iota(par.begin(), par.end(), 0);

    for (int i = 0; i < m; i++) {
        int t; cin >> t;
        // idx = number of prices <= t  -> the last such index in 1-based h
        int idx = upper_bound(h.begin() + 1, h.end(), t) - h.begin() - 1;
        int j = find(idx);                 // nearest unsold at or to the left
        if (j == 0) cout << -1 << '\n';
        else {
            cout << h[j] << '\n';
            par[j] = j - 1;                // sold: future searches jump past it
        }
    }
}

int32_t main(){
    Start();
    int t = 1;
    //cin >> t;
    while (t--) solve();
    End();
    return 0;
}
