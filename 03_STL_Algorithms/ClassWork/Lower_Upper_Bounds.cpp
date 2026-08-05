#include <bits/stdc++.h>

using namespace std;

int main() {

    int n,target;
    cin >> n >> target;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    // lower_bound
    cout << *lower_bound(v.begin(),v.end(),target) << endl;
    // upper bound
    cout << *upper_bound(v.begin(),v.end(),target) << endl;
    // indexes
    // lower_bound
    cout << lower_bound(v.begin(),v.end(),target) - v.begin() << endl;
    // upper bound
    cout << upper_bound(v.begin(),v.end(),target) - v.begin() << endl;

  return 0;
}
