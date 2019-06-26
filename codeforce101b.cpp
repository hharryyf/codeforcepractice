#include <bits/stdc++.h>
#define MAX_LEN 131073
#define MOD 1000000007
typedef long long Long;
using namespace std;

/*
	we have dp[i] = number of ways to reach the ith stop, which i is 
	a terminal stop
	sort the bus according to the terminal stop
	dp[t[i]] = dp[t[i] - 1] + dp[t[i] - 2] + ... + dp[s[i]]
*/

Long tree[MAX_LEN << 1];
int n;
int m;
typedef struct bus {
	Long l, r;
} Bus;

Bus stops[MAX_LEN];

map<int, int> stoporder;

static bool cmp(Bus &b1, Bus &b2) {
	if (b1.r != b2.r) return b1.r < b2.r;
	return b1.l < b2.l;
}

void update(int index, Long delta);
Long query(int index);

int main(int argc, char *argv[]) {
	scanf("%d%d", &n, &m);
	stoporder = map<int, int>();
	int i;
	for (i = 0 ; i < m; i++) {
		cin >>  stops[i].l >> stops[i].r;
		stoporder[stops[i].l] = 0;
		stoporder[stops[i].r] = 0;
	}
	
	map<int, int> :: iterator iter = stoporder.begin();
	int k = 1;
	while (iter != stoporder.end()) {
		iter->second = k;
		k++;
		iter++;
	}
	
	sort(stops, stops + m, cmp);
	Long ans = 0;
	for (i = 0 ; i < m; i++) {
		iter = stoporder.lower_bound(stops[i].r);
		int right = iter->second;
		iter = stoporder.lower_bound(stops[i].l);
		int left = iter->second;
		Long q = query(right - 1) - query(left - 1);
		if (stops[i].l == 0) {
			q++;
		}
		
		update(stoporder[stops[i].r], q);
		if (stops[i].r == n) {
			int k = stoporder[stops[i].r];
			ans = query(k) - query(k - 1);
			ans += MOD;
			ans %= MOD;
		}
	}
	
	cout << ans << endl;
	return 0;
}

int shift(int index) {
	return index & (-index);
}

void update(int index, Long delta) {
	int maxsize = 1 + stoporder.size();
	
	while (index <= maxsize) {
		tree[index] = (tree[index] + delta) % MOD;
		index += shift(index);
	}
}

Long query(int index) {
	Long ans = 0;
	while (index > 0) {
		ans = ans + tree[index];
		ans %= MOD;
		index = index - shift(index);
	}
	return ans;
}
