#include <bits/stdc++.h>
#define MAX_SIZE 261
#define MOD 1000000007
typedef long long ll;
using namespace std;


ll dp[MAX_SIZE][MAX_SIZE];

/*
	dp[i][j] refers to how many ways of forming i valid rows with j valid colunms
	if we know dp[i][j],
	we would know dp[i+1][k] += dp[i][j] * c(m-j, k-j) * k^j * (k-1)^(n-k)   ......(k > j)
				  dp[i+1][j] += dp[i][j] * (k^j - (k-1)^j)
*/

ll c[MAX_SIZE][MAX_SIZE];
ll p1[MAX_SIZE], p2[MAX_SIZE];

int n;
ll k;

void precompute() {
	int i, j;
	for (i = 0; i <= n; i++) {
		c[i][0] = 1;
	}
	
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= i; j++) {
			c[i][j] = c[i-1][j] + c[i-1][j-1];
			c[i][j] %= MOD;
		}
	}
	
	p1[0] = p2[0] = 1;
	for (i = 1; i <= n; i++) {
		p1[i] = p1[i-1] * k;
		p1[i] %= MOD;
		p2[i] = p2[i-1] * (k-1);
		p2[i] %= MOD; 
	}
}

int main() {
	scanf("%d%lld", &n, &k);
	if (k == 1) {
		cout << 1 << endl;
		return 0;
	}
	
	precompute();
	
	int i, j, l;
	
	for (i = 1; i <= n; i++) {
		dp[1][i] = c[n][i] * p2[n-i];
		dp[1][i] %= MOD;
	}
	
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			for (l = j; l <= n; l++) {
				if (l == j) {
					dp[i+1][l] = dp[i+1][l] + (((dp[i][j] * (p1[l] - p2[l])) % MOD) * p2[n-l]) % MOD;
				} else  {
					dp[i+1][l] = dp[i+1][l] + (((dp[i][j] * c[n-j][l-j]) % MOD * p1[j]) % MOD) * p2[n-l] % MOD;
				}
				dp[i+1][j] = (dp[i+1][j] % MOD + MOD) % MOD;
			}
		}
	}
	
	cout << dp[n][n] << endl;
	return 0;
}
