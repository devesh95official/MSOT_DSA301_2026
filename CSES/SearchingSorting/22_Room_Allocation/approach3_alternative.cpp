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

// Event sweep: a customer leaving on day b frees the room from day b+1.
// Keep a stack of free room numbers; reuse one on arrival, return it on leave.
void solve() {
    int n; cin >> n;
    vector<int> a(n), b(n);
    vector<array<int,3>> ev;                    // (day, type, id); type 0 = leave, 1 = arrive
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        ev.push_back({a[i], 1, i});
        ev.push_back({b[i] + 1, 0, i});         // leave BEFORE arrivals of the same day
    }
    sort(ev.begin(), ev.end());

    vector<int> room(n), freeRooms;
    int rooms = 0;
    for (auto [day, type, id] : ev) {
        if (type == 0) freeRooms.push_back(room[id]);      // room becomes free
        else if (!freeRooms.empty()) { room[id] = freeRooms.back(); freeRooms.pop_back(); }
        else room[id] = ++rooms;
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
