#include <bits/stdc++.h>
#define MAX_SIZE 262292


typedef long long ll;

using namespace std;

int tree[MAX_SIZE];

int station[MAX_SIZE >> 1];

ll dp[MAX_SIZE >> 1];

/* return the maximum point's index within the range[start, end] */

pair<int, int> query(int start, int end, int l, int r, int index) {
	if (start > end || l > r || start > r || l > end) return make_pair(0, 0);
	int mid = l + (r - l) / 2;
	if (start <= l && r <= end) {
		if (l == r) return make_pair(tree[index], l);
		if (tree[index * 2] <= tree[index * 2 + 1]) {
			return query(start, end, mid + 1, r, index * 2 + 1);
		}
		
		return query(start, end, l, mid, index * 2);
	}
	
	return max(query(start, end, l, mid, index * 2), query(start, end, mid + 1, r, index * 2 + 1));
}

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index] = station[l];
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	tree[index] = max(tree[index * 2], tree[index * 2 + 1]);
}

int n;

int main() {
	scanf("%d", &n);
	station[n] = n;
	int i;
	for (i = 1; i < n; i++) {
		scanf("%d", &station[i]);
	}
	
	build(1, n, 1);
	
	for (i = n - 1; i >= 1; i--) {
		int index = query(i + 1, station[i], 1, n, 1).second;
		dp[i] = dp[index] +  n - (station[i] - index) - i; 
		// cout << i << ": " << index << " " << dp[i] << endl;  	
	}
	
	ll ans = 0;
	for (i = 1; i <= n; i++) {
		ans = ans + dp[i];
	}
	
	printf("%lld\n", ans);
	return 0;
}
