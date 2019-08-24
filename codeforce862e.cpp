#include <bits/stdc++.h>

using namespace std;

typedef long long Long;

vector<Long> b;
vector<Long> prefix;
int n, m, q;
Long query(Long target, vector<Long> &arr);

int main(int argc, char *argv[]) {
	scanf("%d%d%d", &n, &m, &q);
	int i;
	Long v, asum = 0ll;
	for (i = 0 ; i < n; i++) {
		cin >> v;
		if (i % 2 == 0) {
			asum += v;
		} else {
			asum -= v;
		}
	}
	
	for (i = 0 ; i < m; i++) {
		cin >> v;
		b.push_back(v);
	}
	
	v = 0ll;
	for (i = 0 ; i < m; i++) {
		if (i < n) {
			if (i % 2 == 0) {
				v += b[i];
			} else {
				v -= b[i];
			}
			
			if (i == n - 1) {
				prefix.push_back(v);
			}
		} else {
			if (n % 2 == 0) {
				v -= b[i - n];
				v *= -1;
				v -= b[i];
			} else {
				v -= b[i - n];
				v *= -1;
				v += b[i];
			}
			prefix.push_back(v);
		}
	}
	
	sort(prefix.begin(), prefix.end());
	
	cout << query(asum, prefix) << endl;
	while (q > 0) {
		Long l, r, v;
		cin >> l >> r >> v;
		if ((r - l + 1) % 2 != 0) {
			if (l % 2 == 1) {
				asum += v;
			} else {
				asum -= v;
			}
		}
		
		cout << query(asum, prefix) << endl;
		q--;
	}
	return 0;	
}

Long query(Long target, vector<Long> &arr) {
	if (target <= arr[0]) {
		// cout << "target is " << target << " get index 0" << endl;
		return arr[0] - target;
	} 
	
	if (target >= arr[(int) arr.size() - 1]) {
		// cout << "target is " << target << " get index last " << endl;
		return target - arr[(int) arr.size() - 1];
	}
	
	int index = lower_bound(arr.begin(), arr.end(), target) - arr.begin();
	// cout << "target is " << target << " index is " << index - 1 << " and " << index << endl;
	return min(arr[index] - target, target - arr[index - 1]); 
}
