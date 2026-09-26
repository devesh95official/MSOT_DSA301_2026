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

// Same greedy, but members are "created" only when needed:
// the multiset holds only members who have watched something so far (size <= k).
void solve() {
    int n, k; cin >> n >> k;
    vector<pair<int,int>> mv(n);
    for (auto &[e, s] : mv) cin >> s >> e;
    sort(mv.begin(), mv.end());

    multiset<int> busyUntil;
    int watched = 0;
    for (auto [e, s] : mv) {
        auto it = busyUntil.upper_bound(s);
        if (it != busyUntil.begin()) {           // someone who has watched before is free
            busyUntil.erase(prev(it));
            busyUntil.insert(e);
            watched++;
        } else if ((int)busyUntil.size() < k) {  // an unused member takes it
            busyUntil.insert(e);
            watched++;
        }
    }
    cout << watched << '\n';
}

int32_t main(){
    Start();
    int t = 1;
    //cin >> t;
    while (t--) solve();
    End();
    return 0;
}
