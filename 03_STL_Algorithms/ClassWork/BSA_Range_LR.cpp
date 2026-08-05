#include <bits/stdc++.h>

using namespace std;

#define int            long long int

int32_t main(){

    int n;
    cin >> n;
    vector <int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    // to apply BS sort the vector first
    sort(v.begin(), v.end());

    int tt;
    cin >> tt;
    while(tt--){
    	int l,r;
    	cin>> l >> r;
    	int l_se_chote = lower_bound(v.begin(), v.end(), l) - v.begin();
    	int r_se_bade = v.end() - upper_bound(v.begin(), v.end(), r);
    	cout << n - l_se_chote - r_se_bade << " ";
    }


	return 0;
}
