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

// BFS over time units. State = remaining reading time of each book for each person.
// Each second: Kotivalo reads some book (or idles), Justiina reads a DIFFERENT book (or idles).
void solve() {
    int n; cin >> n;
    vector<int> t(n);
    for (auto &v : t) cin >> v;
    vector<int> start;
    for (int i = 0; i < n; i++) start.push_back(t[i]);
    for (int i = 0; i < n; i++) start.push_back(t[i]);
    map<vector<int>, int> dist; dist[start] = 0;
    queue<vector<int>> q; q.push(start);
    while (!q.empty()) {
        auto s = q.front(); q.pop();
        if (*max_element(s.begin(), s.end()) == 0) { cout << dist[s] << '\n'; return; }
        for (int i = -1; i < n; i++) for (int j = -1; j < n; j++) {
            if (i != -1 && (s[i] == 0)) continue;
            if (j != -1 && (s[n + j] == 0 || j == i)) continue;
            auto ns = s;
            if (i != -1) ns[i]--;
            if (j != -1) ns[n + j]--;
            if (!dist.count(ns)) { dist[ns] = dist[s] + 1; q.push(ns); }
        }
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
