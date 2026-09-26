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

// Fix the MIDDLE index j. Keep a hash map of every value to the LEFT of j,
// then for each k > j ask: "is x - a[j] - a[k] somewhere on the left?"
// The map only grows (one insert per j), so there is no clearing cost: O(n^2) lookups.
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t SEED = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + SEED);
    }
};

void solve() {
    int n, x; cin >> n >> x;
    vector<int> a(n);
    for (auto &v : a) cin >> v;

    unordered_map<int, int, custom_hash> left;   // value -> a position i < j
    left.reserve(2 * n);
    for (int j = 0; j < n; j++) {
        for (int k = j + 1; k < n; k++) {
            auto it = left.find(x - a[j] - a[k]);
            if (it != left.end()) {
                cout << it->second << " " << j + 1 << " " << k + 1 << '\n';
                return;
            }
        }
        left[a[j]] = j + 1;                       // a[j] can now be the first element
    }
    cout << "IMPOSSIBLE\n";
}

int32_t main(){
    Start();
    int t = 1;
    //cin >> t;
    while (t--) solve();
    End();
    return 0;
}
