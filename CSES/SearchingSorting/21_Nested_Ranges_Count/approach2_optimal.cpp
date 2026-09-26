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

struct Fenwick {                       // prefix sums with point updates, both O(log n)
    int n; vector<int> t;
    Fenwick(int n) : n(n), t(n + 1, 0) {}
    void add(int i, int v) { for (; i <= n; i += i & -i) t[i] += v; }
    int sum(int i) { int s = 0; for (; i > 0; i -= i & -i) s += t[i]; return s; }
};

void solve() {
    int n; cin >> n;
    vector<int> l(n), r(n);
    for (int i = 0; i < n; i++) cin >> l[i] >> r[i];

    // compress right ends to 1..m so they can index the Fenwick tree
    vector<int> vals(r);
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    int m = vals.size();
    vector<int> rc(n);
    for (int i = 0; i < n; i++) rc[i] = lower_bound(vals.begin(), vals.end(), r[i]) - vals.begin() + 1;

    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int a, int b) {
        if (l[a] != l[b]) return l[a] < l[b];
        return r[a] > r[b];
    });

    vector<int> contains(n), inside(n);

    // ---- inside[i]: ranges j with l_j <= l_i and r_j >= r_i. Sweep forward.
    Fenwick f1(m);
    for (int s = 0; s < n; ) {
        int e = s;                                     // [s, e) = block of identical ranges
        while (e < n && l[ord[e]] == l[ord[s]] && r[ord[e]] == r[ord[s]]) e++;
        for (int k = s; k < e; k++) f1.add(rc[ord[k]], 1);
        for (int k = s; k < e; k++) {
            int i = ord[k];
            inside[i] = e - f1.sum(rc[i] - 1) - 1;   // e ranges inserted; those with r >= r_i, minus me
        }
        s = e;
    }
    // ---- contains[i]: ranges j with l_j >= l_i and r_j <= r_i. Sweep backward.
    Fenwick f2(m);
    for (int e = n; e > 0; ) {
        int s = e;
        while (s > 0 && l[ord[s - 1]] == l[ord[e - 1]] && r[ord[s - 1]] == r[ord[e - 1]]) s--;
        for (int k = s; k < e; k++) f2.add(rc[ord[k]], 1);
        for (int k = s; k < e; k++) {
            int i = ord[k];
            contains[i] = f2.sum(rc[i]) - 1;          // inserted with r <= r_i, minus me
        }
        e = s;
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
