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
    int x, n; cin >> x >> n;
    set<int> lights = {0, x};             // borders act like lights
    multiset<int> gaps = {x};             // lengths of all current segments

    for (int i = 0; i < n; i++) {
        int p; cin >> p;
        auto right = lights.upper_bound(p);   // first light after p
        auto left = prev(right);              // last light before p
        int L = *left, R = *right;

        gaps.erase(gaps.find(R - L));         // segment [L,R] is split... (erase ONE copy)
        gaps.insert(p - L);                   // ... into [L,p]
        gaps.insert(R - p);                   // ... and  [p,R]
        lights.insert(p);

        cout << *gaps.rbegin() << " \n"[i == n - 1];   // longest segment
    }
}

int32_t main(){
    Start();
    int t = 1;
    //cin >> t;
    while (t--) solve();
    End();
    return 0;
}
