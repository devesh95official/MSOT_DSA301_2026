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

// Offline, backwards: start with ALL lights, then remove them in reverse order.
// Removing only MERGES segments, so the answer can only grow -> a single running max.
void solve() {
    int x, n; cin >> x >> n;
    vector<int> p(n);
    for (auto &v : p) cin >> v;

    vector<int> s = p;
    s.push_back(0); s.push_back(x);
    sort(s.begin(), s.end());
    int m = s.size();
    vector<int> L(m), R(m);                  // doubly linked list over sorted positions
    int best = 0;
    for (int i = 0; i < m; i++) {
        L[i] = i - 1; R[i] = i + 1;
        if (i) best = max(best, s[i] - s[i - 1]);
    }

    vector<int> ans(n);
    for (int i = n - 1; i >= 0; i--) {
        ans[i] = best;                        // answer after lights p[0..i] are placed
        int id = lower_bound(s.begin(), s.end(), p[i]) - s.begin();
        int a = L[id], b = R[id];             // neighbours of the light we remove
        R[a] = b; L[b] = a;                   // unlink it
        best = max(best, s[b] - s[a]);        // the merged segment
    }
    for (int i = 0; i < n; i++) cout << ans[i] << " \n"[i == n - 1];
}

int32_t main(){
    Start();
    int t = 1;
    //cin >> t;
    while (t--) solve();
    End();
    return 0;
}
