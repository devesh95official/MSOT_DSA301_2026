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
    int n, m, k; cin >> n >> m >> k;
    vector<int> a(n);
    multiset<int> free_apts;
    for (auto &x : a) cin >> x;
    for (int j = 0; j < m; j++) { int x; cin >> x; free_apts.insert(x); }
    sort(a.begin(), a.end());

    int matched = 0;
    for (int want : a) {
        // smallest free apartment that is >= want - k
        auto it = free_apts.lower_bound(want - k);
        if (it != free_apts.end() && *it <= want + k) {
            matched++;
            free_apts.erase(it);        // erase ONE copy (by iterator), not all equal values
        }
    }
    cout << matched << '\n';
}

int32_t main(){
    Start();
    int t = 1;
    //cin >> t;
    while (t--) solve();
    End();
    return 0;
}
