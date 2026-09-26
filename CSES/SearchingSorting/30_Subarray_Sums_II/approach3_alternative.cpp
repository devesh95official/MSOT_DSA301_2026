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

// No hashing at all: sort the prefix sums once, turn them into ranks, count with a vector.
void solve() {
    int n, x; cin >> n >> x;
    vector<int> P(n + 1, 0);
    for (int i = 1; i <= n; i++) { int v; cin >> v; P[i] = P[i - 1] + v; }

    vector<int> vals(P);
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    auto rank = [&](int v) { return lower_bound(vals.begin(), vals.end(), v) - vals.begin(); };

    vector<int> freq(vals.size(), 0);
    int cnt = 0;
    freq[rank(P[0])]++;
    for (int r = 1; r <= n; r++) {
        int want = P[r] - x;
        int k = rank(want);
        if (k < (int)vals.size() && vals[k] == want) cnt += freq[k];   // want may not exist at all
        freq[rank(P[r])]++;
    }
    cout << cnt << '\n';
}

int32_t main(){
    Start();
    int t = 1;
    //cin >> t;
    while (t--) solve();
    End();
    return 0;
}
