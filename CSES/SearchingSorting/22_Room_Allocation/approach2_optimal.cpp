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
    vector<array<int,3>> c(n);                 // (arrival, departure, original index)
    for (int i = 0; i < n; i++) { cin >> c[i][0] >> c[i][1]; c[i][2] = i; }
    sort(c.begin(), c.end());                  // handle customers in order of arrival

    // min-heap of (departure day, room) for rooms currently in use
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    vector<int> room(n);
    int rooms = 0;

    for (auto [a, b, id] : c) {
        if (!pq.empty() && pq.top().first < a) {    // earliest-freed room is free before a
            int r = pq.top().second; pq.pop();
            room[id] = r;
            pq.push({b, r});
        } else {                                    // every room is busy -> open a new one
            room[id] = ++rooms;
            pq.push({b, rooms});
        }
    }
    cout << rooms << '\n';
    print(room);
}

int32_t main(){
    Start();
    int t = 1;
    //cin >> t;
    while (t--) solve();
    End();
    return 0;
}
