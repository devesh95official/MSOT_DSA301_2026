#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
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

// ordered set of (right end, id): order_of_key counts how many are strictly smaller
typedef tree<pair<int,int>, null_type, less<pair<int,int>>, rb_tree_tag,
             tree_order_statistics_node_update> ordered_set;

void solve() {
    int n; cin >> n;
    vector<int> l(n), r(n);
    for (int i = 0; i < n; i++) cin >> l[i] >> r[i];
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int a, int b) {
        if (l[a] != l[b]) return l[a] < l[b];
        return r[a] > r[b];
    });
    auto same = [&](int a, int b) { return l[a] == l[b] && r[a] == r[b]; };
    vector<int> contains(n), inside(n);

    ordered_set os;                                  // forward sweep -> inside[]
    for (int s = 0, e; s < n; s = e) {
        for (e = s; e < n && same(ord[e], ord[s]); e++) os.insert({r[ord[e]], ord[e]});
        for (int k = s; k < e; k++) {
            int i = ord[k];
            int smaller = os.order_of_key({r[i], -1});     // right end < r_i
            inside[i] = (int)os.size() - smaller - 1;
        }
    }
    os.clear();                                      // backward sweep -> contains[]
    for (int e = n, s; e > 0; e = s) {
        for (s = e; s > 0 && same(ord[s - 1], ord[e - 1]); s--) os.insert({r[ord[s - 1]], ord[s - 1]});
        for (int k = s; k < e; k++) {
            int i = ord[k];
            contains[i] = os.order_of_key({r[i], LLONG_MAX}) - 1;   // right end <= r_i, minus me
        }
    }
    print(contains);
    print(inside);
}

int32_t main(){
    Start();
    int t = 1;
    //cin >> t;
    while (t--) solve();
    End();
    return 0;
}
