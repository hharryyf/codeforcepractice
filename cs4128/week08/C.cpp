#include <bits/stdc++.h>
#define MAX_SIZE 8193
#define INF (1ll << 62)

typedef long long ll;

using namespace std;

int n, m;
ll pref[MAX_SIZE];
ll dp[MAX_SIZE][811];

void preprocess() {
	scanf("%d%d", &n, &m);
	scanf("%lld", &pref[1]);
	dp[1][0] = INF;
	int i;
	for (i = 2; i <= n; i++) {
		dp[i][0] = INF;
		scanf("%lld", &pref[i]);
		pref[i] = pref[i] + pref[i-1];
	}
}

/* cost(i, j) = cost from i+1 to j */
ll cost(int i, int j) {
	return (pref[j] - pref[i]) * (j - i);
}

/* 
	dp[i][j] = max(dp[k][j-1] + cost(k, i))
*/

void divc(int start, int end, int l, int r, int k) {
	if (l > r) return;
	int pos = -1;
	int mid = l + (r - l) / 2;
	int i;
	dp[mid][k] = INF;
	/* bestpos is between start and end */
	for (i = start; i <= min(mid - 1, end); i++) {
		ll ncost = dp[i][k-1] + cost(i, mid);
		if (ncost < dp[mid][k]) {
			dp[mid][k] = ncost;
			pos = i;
		}
	}
	
	divc(start, pos, l, mid - 1, k);
	divc(pos, end, mid + 1, r, k);
}

void solve() {
	int i;
	for (i = 1; i <= m; i++) {
		divc(0, n, 1, n, i);
	}
	
	cout << dp[n][m] << endl;
}

int main() {
	preprocess();
	solve();	
	return 0;
}
