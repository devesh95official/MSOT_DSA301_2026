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

void solve() {
    int n; cin >> n;
    vector<pair<int,int>> mv(n);
    for (auto &[a, b] : mv) cin >> a >> b;
    int best = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<pair<int,int>> s;
        for (int i = 0; i < n; i++) if (mask >> i & 1) s.push_back(mv[i]);
        sort(s.begin(), s.end());
        bool ok = true;
        for (int i = 1; i < (int)s.size(); i++) if (s[i].first < s[i - 1].second) ok = false;
        if (ok) best = max(best, (int)s.size());
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
