#include <bits/stdc++.h>

using namespace std;

// upper bound
int main() {

  int n, target;
  cin >> n >> target;
  vector <int> v(n);
  for (int i = 0; i < n; ++i){
    cin >> v[i];
  }

  // upper bound just > target
  int l = -1, r = n - 1; // l = bad, r = good
  while(r > l+1){
    int m = (l+r)/2;
    if(v[m] > target)r = m;
    else l = m;
  }

  if(target >= v[n-1])cout << "-1\n";
  else cout<<v[r] <<endl;
  return 0;
}
