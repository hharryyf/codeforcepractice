#include <bits/stdc++.h>
#define MOD 1000000007

typedef long long ll;

using namespace std;

/* this problem is really hard*/
/* i people, j imbalance, k incomplete group */
/* we add the imbalance cost as we iterate */
int dp[211][211][1011];

int a[201];

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	int i, j, k;
	for (i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	
	sort(a + 1, a + n + 1);
	
	dp[0][0][0] = 1;
	
	for (i = 1; i <= n; i++) {
		for (j = 0; j <= i; j++) {
			for (k = 0; k <= m; k++) {
				/*
					k -> j * (a[i] - a[i-1])
				*/
				int diff = j * (a[i] - a[i-1]);
				if (k + diff <= m) {
					/* the ith person is not in one of the group and another imbalance is formed*/
					dp[i][j+1][diff + k] = (dp[i-1][j][k] + dp[i][j+1][diff + k]) % MOD;
					/* the ith person is a group */
					dp[i][j][diff + k] = (dp[i-1][j][k] + dp[i][j][diff + k]) % MOD;
					/* the ith person is put in one of the groups and act as the maxmimum */
					/* the ith person is put in one of the previous imbalance group */
					if (j > 0) {
						dp[i][j][k + diff] = ((1ll *  dp[i-1][j][k] * j) % MOD + dp[i][j][k + diff]) % MOD; 
						dp[i][j-1][k + diff] = (dp[i][j-1][k + diff] + (1ll * dp[i-1][j][k] *  j) % MOD) % MOD;
					}
				}
			}
		}
	}
	
	int ans = 0;
	for (i = 0 ; i <= m; i++) {
		ans = (ans + dp[n][0][i]) % MOD;
	}
	
	printf("%d\n", ans);
	return 0;
}
