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
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto &v : a) cin >> v;

    // can we cut the array into at most k pieces, each with sum <= limit?
    auto possible = [&](int limit) {
        int pieces = 1, cur = 0;
        for (int v : a) {
            if (v > limit) return false;           // a single element is already too big
            if (cur + v > limit) { pieces++; cur = 0; }   // close this piece, start a new one
            cur += v;
        }
        return pieces <= k;                        // fewer pieces can always be split more
    };

    int lo = *max_element(a.begin(), a.end());     // answer is at least the biggest element
    int hi = accumulate(a.begin(), a.end(), 0LL);  // ... and at most the whole sum
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (possible(mid)) hi = mid;
        else lo = mid + 1;
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
