#include <bits/stdc++.h>
 
using namespace std;
 
#define int long long int
 
int32_t main() {
  int w, h, n;
  cin >> w >> h >> n;
 
  auto Good = [&](int side)->bool{
    int total = (side / w) * (side / h);
    if(total >= n)return true;
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
