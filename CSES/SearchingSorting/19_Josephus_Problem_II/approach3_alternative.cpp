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

// Fenwick tree over positions 1..n: bit stores 1 if the child is still in the circle.
// "find the idx-th alive child" = descend the Fenwick tree by powers of two.
int n, LOG;
vector<int> bit;

void add(int i, int v) { for (; i <= n; i += i & -i) bit[i] += v; }

int kth(int k) {                          // smallest position p with prefix_sum(p) = k (1-based k)
    int pos = 0;
    for (int step = LOG; step > 0; step >>= 1)
        if (pos + step <= n && bit[pos + step] < k) {
            pos += step;
            k -= bit[pos];
        }
    return pos + 1;
}

void solve() {
    int k; cin >> n >> k;
    bit.assign(n + 1, 0);
    LOG = 1; while (LOG * 2 <= n) LOG *= 2;
    for (int i = 1; i <= n; i++) add(i, 1);

    int idx = 0, size = n;
    while (size > 0) {
        idx = (idx + k) % size;
        int child = kth(idx + 1);          // (idx+1)-th alive child
        cout << child << ' ';
        add(child, -1);
        size--;
        if (size) idx %= size;
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
