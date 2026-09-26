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

// Sort, fix the two smallest, and finish with two pointers: O(n^3) but a tiny constant.
void solve() {
    int n, x; cin >> n >> x;
    vector<pair<int,int>> a(n);
    for (int i = 0; i < n; i++) { cin >> a[i].first; a[i].second = i + 1; }
    sort(a.begin(), a.end());

    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            int need = x - a[i].first - a[j].first;
            int l = j + 1, r = n - 1;
            while (l < r) {
                int s = a[l].first + a[r].first;
                if (s == need) {
                    cout << a[i].second << " " << a[j].second << " "
                         << a[l].second << " " << a[r].second << '\n';
                    return;
                }
                if (s < need) l++; else r--;
            }
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
