#include <bits/stdc++.h>
using namespace std;

const int shift = 10001;
int dp[1011][21111];
int a[1011];
int ans;

const int mod = 1e9 + 7;

int main() {
	int i, n, j;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) scanf("%d", &a[i]);
	dp[1][-a[1] + shift] = 1;
	dp[1][a[1] + shift] = 1;
	
	for (i = 2; i <= n; ++i) {
		dp[i][a[i] + shift] = 1;
		dp[i][-a[i] + shift] = 1;
		for (j = -10000; j <= 10000; ++j) {
			dp[i][j + shift] = (dp[i][j + shift] + dp[i-1][a[i] + j + shift]) % mod;
			dp[i][j + shift] = (dp[i][j + shift] + dp[i-1][-a[i] + j + shift]) % mod;
		}
		// cout << dp[i][shift] << endl;
		ans = (ans + dp[i][shift]) % mod;
	}
	
	cout << ans << endl;
	return 0;
}