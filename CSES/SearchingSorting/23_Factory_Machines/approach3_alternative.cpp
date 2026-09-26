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

// Same monotonic predicate, but "binary search by bits":
// build the LARGEST time that is NOT enough, one bit at a time; answer = that + 1.
void solve() {
    int n, t; cin >> n >> t;
    vector<int> k(n);
    for (auto &v : k) cin >> v;
    auto enough = [&](int time) {
        int made = 0;
        for (int v : k) { made += time / v; if (made >= t) return true; }
        return false;
    };
    int bad = 0;                                   // 0 seconds is never enough
    for (int bitv = 1LL << 60; bitv > 0; bitv >>= 1)
        if (!enough(bad + bitv)) bad += bitv;      // still not enough -> keep this bit
    cout << bad + 1 << '\n';
}

int32_t main(){
    Start();
    int t = 1;
    //cin >> t;
    while (t--) solve();
    End();
    return 0;
}
