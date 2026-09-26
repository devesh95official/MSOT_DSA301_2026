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

// Same window, but compress values first so counts live in a plain vector (faster than map)
void solve() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto &v : a) cin >> v;
    vector<int> vals(a);
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    for (auto &v : a) v = lower_bound(vals.begin(), vals.end(), v) - vals.begin();

    vector<int> freq(vals.size(), 0);
    int distinct = 0, l = 0, total = 0;
    for (int r = 0; r < n; r++) {
        if (freq[a[r]]++ == 0) distinct++;
        while (distinct > k)
            if (--freq[a[l++]] == 0) distinct--;
        total += r - l + 1;
    }
    cout << total << '\n';
}

int32_t main(){
    Start();
    int t = 1;
    //cin >> t;
    while (t--) solve();
    End();
    return 0;
}
