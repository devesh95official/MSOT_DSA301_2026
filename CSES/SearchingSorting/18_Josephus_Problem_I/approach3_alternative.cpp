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

// Round by round: walk over the survivors and remove every second one.
// "skip" carries over between rounds so the alternation never breaks.
void solve() {
    int n; cin >> n;
    vector<int> alive(n);
    iota(alive.begin(), alive.end(), 1);

    bool removeNext = false;            // the first child (1) is skipped
    while (!alive.empty()) {
        vector<int> survivors;
        for (int c : alive) {
            if (removeNext) cout << c << ' ';
            else survivors.push_back(c);
            removeNext = !removeNext;   // strictly alternate: skip, remove, skip, ...
        }
        alive = survivors;              // each round halves the circle -> O(n) total
    }
    cout << '\n';
}

int32_t main(){
    Start();
    int t = 1;
    //cin >> t;
    while (t--) solve();
    End();
    return 0;
}
