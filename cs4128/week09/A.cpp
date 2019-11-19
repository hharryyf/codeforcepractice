#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

vector<int> p;
bool visited[1000011];

void preprocess() {
	p.push_back(0);
	for (int i = 2; i <= 1000000; i++) {
		if (!visited[i]) {
			visited[i] = true;
			p.push_back(i);
			for (int j = 1; j * i <= 1000000; j++) {
				visited[j * i] = true;
			}
		}
	}
}

int getcomposite(int num) {
	int low = 0, high = (int) p.size() - 1;
	int ans = 0;
	while (low <= high) {
		int mid = low + (high - low) / 2;
		if (p[mid] <= num) {
			ans = max(ans, mid);
			low = mid + 1;
		} else {
			high = mid - 1;
		}
	}
	
	return num - ans - 1;
}

int elim(vector<int> &a, ll num) {
	int k = (int) a.size();
	ll ret = 0;
	ll curr = 1ll;
	int i, j;
	for (i = 1 ; i < (1 << k); i++) {
		int bi =  __builtin_popcount(i);
		curr = 1ll;
		for (j = 0 ; j < k; j++) {
			if (((1 << j) & i) != 0) {
				curr = curr * ((ll) a[j]);
			}
		}
		if (curr != 1) {
			if (bi % 2 == 0) {
				ret = ret - num / curr;
			} else {
				ret = ret + num / curr;
			}
		}
	}
	
	return (int) ret;
}

int main() {
	/*
		The number of composite number which is not divisable by any of the k primes
		= the number of composite number 
	*/
	
	int T;
	scanf("%d", &T);
	int i, n, k;
	preprocess();
	// cout << p.size() << endl;
	for (i = 1; i <= T; i++) {
		scanf("%d", &n);
		scanf("%d", &k);
		vector<int> pp;
		for (int j = 0; j < k; j++) {
			int v;
			scanf("%d", &v);
			if (v <= n) {
				pp.push_back(v);
			}
		}
		
		// cout << "composite " << getcomposite(n) << " eliminate " << elim(pp, (ll) n) << endl;
		if (n == 0 || n == 1) {
			printf("Case %d: 0\n", i);
		} else {
			printf("Case %d: %d\n", i, getcomposite(n) - elim(pp, (ll) n) + (int) pp.size());
		}
	}
	return 0;
}
