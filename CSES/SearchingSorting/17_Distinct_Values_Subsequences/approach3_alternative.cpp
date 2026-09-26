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

// Online version: add elements one by one.
// ways(value v) goes from f to f+1 when a new copy arrives, so
// total = total / (f+1) * (f+2)  -> needs a modular inverse, which is fine since mod is prime.
int power(int b, int e) {
    int r = 1; b %= mod;
    while (e) { if (e & 1) r = r * b % mod; b = b * b % mod; e >>= 1; }
    return r;
}

void solve() {
    int n; cin >> n;
    map<int,int> f;
    int ways = 1;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        int c = f[x]++;                                   // copies before this one
        ways = ways * power(c + 1, mod - 2) % mod;        // remove old factor (c+1)
        ways = ways * (c + 2) % mod;                      // multiply new factor (c+2)
    }
    cout << (ways - 1 + mod) % mod << '\n';
}

int32_t main(){
    Start();
    int t = 1;
    //cin >> t;
    while (t--) solve();
    End();
    return 0;
}
