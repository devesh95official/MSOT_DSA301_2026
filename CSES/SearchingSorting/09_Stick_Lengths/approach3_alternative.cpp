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

// Evaluate the cost of EVERY candidate target p[i] in O(1) using prefix sums
void solve() {
    int n; cin >> n;
    vector<int> p(n);
    for (auto &v : p) cin >> v;
    sort(p.begin(), p.end());
    vector<int> pre(n + 1, 0);
    for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + p[i];

    int best = LLONG_MAX;
    for (int i = 0; i < n; i++) {
        int t = p[i];
        int left  = t * i - pre[i];                         // raise p[0..i-1] up to t
        int right = (pre[n] - pre[i + 1]) - t * (n - 1 - i); // cut p[i+1..n-1] down to t
        best = min(best, left + right);
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
