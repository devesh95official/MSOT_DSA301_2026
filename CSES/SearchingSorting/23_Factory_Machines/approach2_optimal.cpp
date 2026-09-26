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
    int n, t; cin >> n >> t;
    vector<int> k(n);
    for (auto &v : k) cin >> v;

    // how many products can all machines make together in `time` seconds? (capped at t)
    auto enough = [&](int time) {
        int made = 0;
        for (int v : k) {
            made += time / v;
            if (made >= t) return true;   // stop early -> no overflow
        }
        return false;
    };

    int lo = 1, hi = *min_element(k.begin(), k.end()) * t;   // fastest machine alone is enough
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (enough(mid)) hi = mid;        // mid works -> answer is mid or smaller
        else lo = mid + 1;                // mid fails -> answer is bigger
    }
    cout << lo << '\n';
}

int32_t main(){
    Start();
    int t = 1;
    //cin >> t;
    while (t--) solve();
    End();
    return 0;
}
