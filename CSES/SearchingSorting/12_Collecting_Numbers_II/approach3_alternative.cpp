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

// Same idea, but store the "is broken" flag of every pair explicitly.
// Recomputing a flag is idempotent, so duplicates need no special care.
void solve() {
    int n, m; cin >> n >> m;
    vector<int> a(n + 1), pos(n + 2);
    for (int i = 1; i <= n; i++) { cin >> a[i]; pos[a[i]] = i; }

    vector<int> broken(n + 1, 0);          // broken[v] = 1 if pos[v+1] < pos[v]
    int rounds = 1;
    auto refresh = [&](int v) {
        if (v < 1 || v >= n) return;
        rounds -= broken[v];
        broken[v] = pos[v + 1] < pos[v];
        rounds += broken[v];
    };
    for (int v = 1; v < n; v++) refresh(v);

    while (m--) {
        int x, y; cin >> x >> y;
        int u = a[x], w = a[y];
        swap(a[x], a[y]);
        pos[u] = y; pos[w] = x;
        refresh(u - 1); refresh(u); refresh(w - 1); refresh(w);
        cout << rounds << '\n';
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
