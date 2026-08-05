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
    if(target < v[0]) {
       cout << "0\n";
       continue;
    }
    auto Good = [&](int m)->bool{
         if(v[m] <= target)return true;
         return false;
    };

    int l = 0, r = n;

    while(r > l + 1){
      int m = l + (r-l)/2;
      if(Good(m))l = m;
      else r = m;
    }

    cout << l + 1 << endl;
  }

  return 0;
}
