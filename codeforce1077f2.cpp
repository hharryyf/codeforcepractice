#include <bits/stdc++.h>
#define MAX_SIZE 16387

typedef long long ll;
using namespace std;

ll dp[2][MAX_SIZE];
ll beauty[MAX_SIZE];
const ll INF = -10000000000000;

void update(int point, int l, int r, int index, ll value, ll tree[]);
ll query(int st, int ed, int l, int r, int index, ll tree[]);
int main(int argc, char *argv[]) {
	int i, j, gap, n, m;
	
	cin >> n >> gap >> m;
	if (n > m && gap == 1) {
		cout << -1 << endl;
		return 0;
	}
	/*
		dp[i][j] = max(dp[p][j-1] + value[i]) which i >= j and max(j-1, i - gap) <= p < i
	*/
	for (i = 0 ; i < n; i++) {
		cin >> beauty[i];
		update(i, 0, n - 1, 1, INF, dp[0]);
		update(i, 0, n - 1, 1, INF, dp[1]);	
	}
	
	for (i = 0 ; i < min(gap, n); i++) {
		update(i, 0, n - 1, 1, beauty[i], dp[1]);	
		// cout << "dp[" << 1 << "][" << i << "]= " << query(i, i, 0, n - 1, 1, dp[1]) << endl;
	}
	
	// cout << "hello" << endl;
	for (j = 2; j <= m; j++) {
		for (i = 0; i < n; i++) {
			if (i >= j - 1) {		
				ll res = query(max(j-2, i - gap), i - 1, 0, n - 1, 1, dp[(j - 1) % 2]);
				update(i, 0, n - 1, 1, res + beauty[i], dp[j % 2]);
			} else {
				update(i, 0, n - 1, 1, INF, dp[j % 2]);	
			}
			// cout << "dp[" << j << "][" << i << "]= " << query(i, i, 0, n - 1, 1, dp[j % 2]) << endl;
		}
		
	}
	
	ll ans = INF;
	ans = query(max(0, n - gap), n - 1, 0, n - 1, 1, dp[m % 2]);
	if (ans < 0) {
		cout << -1 << endl;
	} else {
		cout << ans << endl;
	}
	return 0;
}

void update(int point, int l, int r, int index, ll value, ll tree[]) {
	if (l > point || r < point || l > r) return;
	if (l == point && r == point) {
		tree[index] = value;
		return;
	}
	int mid = l + (r - l) / 2;
	if (point <= mid) {
		update(point, l, mid, index * 2, value, tree);
	} else {
		update(point, mid + 1, r, index * 2 + 1, value, tree);
	}
	tree[index] = max(tree[index * 2], tree[index * 2 + 1]);
}

ll query(int st, int ed, int l, int r, int index, ll tree[]) {
	if (st > r || ed < l || l > r || st > ed) return INF;
	if (l >= st && ed >= r) return tree[index];
	int mid = l + (r - l) / 2;
	return max(query(st, ed, l, mid, index * 2, tree)
			, query(st, ed, mid + 1, r, index * 2 + 1, tree));
}
