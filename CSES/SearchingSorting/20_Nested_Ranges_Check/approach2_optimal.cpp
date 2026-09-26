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
    int n; cin >> n;
    vector<int> l(n), r(n);
    for (int i = 0; i < n; i++) cin >> l[i] >> r[i];

    // order: left end ascending; for equal left ends, the LONGER range first
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int a, int b) {
        if (l[a] != l[b]) return l[a] < l[b];
        return r[a] > r[b];
    });

    vector<int> contains(n, 0), inside(n, 0);

    // Pass 1 (left -> right): everything before me starts no later than me.
    // Someone contains me  <=>  one of them reaches at least as far right.
    int maxR = LLONG_MIN;
    for (int i : ord) {
        if (maxR >= r[i]) inside[i] = 1;
        maxR = max(maxR, r[i]);
    }
    // Pass 2 (right -> left): everything after me starts no earlier than me.
    // I contain someone  <=>  one of them ends no later than me.
    int minR = LLONG_MAX;
    for (int k = n - 1; k >= 0; k--) {
        int i = ord[k];
        if (minR <= r[i]) contains[i] = 1;
        minR = min(minR, r[i]);
    }
    // Identical ranges contain each other; the passes above see only one direction.
    map<pair<int,int>, int> cnt;
    for (int i = 0; i < n; i++) cnt[{l[i], r[i]}]++;
    for (int i = 0; i < n; i++)
        if (cnt[{l[i], r[i]}] > 1) contains[i] = inside[i] = 1;

    print(contains);
    print(inside);
}

int32_t main(){
    Start();
    int t = 1;
    //cin >> t;
    while (t--) solve();
    End();
    return 0;
}
