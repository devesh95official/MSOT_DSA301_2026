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

int n, m;
vector<int> a, pos;

// pair (v, v+1) costs an extra round if v+1 sits before v
int bad(int v) {
    if (v < 1 || v >= n) return 0;        // pair doesn't exist
    return pos[v + 1] < pos[v];
}

void solve() {
    cin >> n >> m;
    a.assign(n + 1, 0); pos.assign(n + 2, 0);
    for (int i = 1; i <= n; i++) { cin >> a[i]; pos[a[i]] = i; }

    int rounds = 1;
    for (int v = 1; v < n; v++) rounds += bad(v);

    while (m--) {
        int x, y; cin >> x >> y;
        int u = a[x], w = a[y];                        // the two VALUES being moved
        // only pairs that contain u or w can change
        set<int> pairs = {u - 1, u, w - 1, w};          // pair v means (v, v+1); set removes duplicates

        for (int v : pairs) rounds -= bad(v);          // 1) remove old contribution
        swap(a[x], a[y]);                               // 2) do the swap
        pos[a[x]] = x; pos[a[y]] = y;
        for (int v : pairs) rounds += bad(v);          // 3) add new contribution

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
