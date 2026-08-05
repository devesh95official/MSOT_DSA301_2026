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
  // Good(takes time) and tells us if possible to make t papers
  auto Good = [&](int time)->bool{
    int total = 0;
    for (int i = 0; i < n; ++i){
       total += (time/v[i]);
    }
    if(total >= t)return true;
    return false;
  };

  int l = 0, r = 1;

  while(!Good(r))r *= 2;

  while(r > l+1){
    int m = l + (r-l)/2;
    if(Good(m))r = m;
    else l = m;
  }

  cout << r <<endl;
  return 0;
}
