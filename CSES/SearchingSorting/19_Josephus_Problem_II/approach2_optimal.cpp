#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
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

// ordered_set: a set that also answers "give me the i-th element" in O(log n)
typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update> ordered_set;

void solve() {
    int n, k; cin >> n >> k;
    ordered_set circle;
    for (int i = 1; i <= n; i++) circle.insert(i);

    int idx = 0;                                  // index (0-based) where counting starts
    while (!circle.empty()) {
        idx = (idx + k) % circle.size();          // skip k children, wrapping around
        auto it = circle.find_by_order(idx);      // the idx-th smallest = the child at idx
        cout << *it << ' ';
        circle.erase(it);
        // the child after the removed one now sits at the SAME index idx
        if (!circle.empty()) idx %= circle.size();
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
