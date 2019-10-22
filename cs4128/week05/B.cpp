#include <bits/stdc++.h>
#define MAX_SIZE 111
#define INF 1000000000000ll

typedef long long ll;

/*
	https://codeforces.com/contest/711/problem/C
*/

using namespace std;

ll dp[MAX_SIZE][MAX_SIZE][MAX_SIZE];
ll dp2[MAX_SIZE][MAX_SIZE][MAX_SIZE];
ll cost[MAX_SIZE][MAX_SIZE];
int c[MAX_SIZE];
ll backward[MAX_SIZE];

int main() {
	int i, j, n, m, k, p;
	scanf("%d%d%d", &n, &m, &k);
	for (i = 0 ; i <= n; i++) {
		for (j = 0; j <= k; j++) {
			for (p = 0; p <= m; p++) {
				dp[i][j][p] = INF;
				dp2[i][j][p] = INF;
			}
		}
	}
	
	for (i = 1; i <= n; i++) {
		scanf("%d", &c[i]);
	}
	
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) {
			scanf("%lld", &cost[i][j]);
		}
	}
	
	dp[0][0][0] = 0;
	for (i = 1; i <= m; i++) {
		dp2[0][0][i] = 0;
	}
	
	ll ans = INF;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= k; j++) {
			for (p = 1; p <= m; p++) {
				if (c[i] == 0) {
					dp[i][j][p] = cost[i][p] + min(dp2[i-1][j-1][p], dp[i-1][j][p]); 
				} else if (c[i] == p) {
					dp[i][j][p] = min(dp2[i-1][j-1][p], dp[i-1][j][p]); 
				}
				
			    // cout << i << " " << j << " " << p << " " << dp[i][j][p] << endl;
				
				if (i == n && j == k) {
					ans = min(ans, dp[i][j][p]);
				}
			}
			
			for (p = 1; p <= m; p++) {
				dp2[i][j][p] = min(dp2[i][j][p-1], dp[i][j][p-1]);
				backward[i] = INF;
			}
			
			backward[0] = backward[m+1] = INF;
			
			for (p = m; p >= 1; p--) {
				dp2[i][j][p] = min(dp2[i][j][p], backward[p+1]);
				backward[p] = min(backward[p+1], dp[i][j][p]);
			}
		}
	}
	
	if (ans == INF) {
		printf("-1\n");
	} else {
		printf("%lld\n", ans);
	}
	return 0;
}
