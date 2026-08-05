#include <bits/stdc++.h>

using namespace std;

#define int long long int

int32_t main() {

  int n, t;
  cin >> n >> t;
  vector <int> v(n);
  for (int i = 0; i < n; i++) {
      cin >> v[i];
  }

  while(t--){
    int target;
    cin >> target;

    // exception
    if(target > v[n-1]) {
       cout << n + 1 << "\n";
       continue;
    }
    // function to check v[m] >= target
    auto Good = [&](int m)->bool{
         if(v[m] >= target)return true;
         return false;
    };

    int l = -1, r = n - 1;

    while(r > l + 1){
      int m = l + (r-l)/2;
      if(Good(m))r = m;
      else l = m;
    }

    cout << r + 1 << endl;
  }

  return 0;
}
