#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#define MOD 1000000007
#define MAX_SIZE 1011

ll dp[MAX_SIZE][MAX_SIZE][2];

ll cost[MAX_SIZE];

int main() {
	int n, b, f;
	scanf("%d%d%d", &n, &b, &f);
	int i, j;
	for (i = 1; i <= n; i++) cin >> cost[i];
	for (i = 0; i <= b; i++) {
		if (i >= cost[1]) {
			dp[1][i][0] = 1;
		}
		dp[1][i][1] = 1;
		//cout << 1 << " " << i << " = " << dp[1][i][0] << ", " << dp[1][i][1] << endl;
	}
	for (i = 2; i <= n; i++) {
		for (j = 0; j <= b; j++) {
			if (j >= cost[i]) {
				dp[i][j][0] = (dp[i-1][j-cost[i]][1]) % MOD; 
			}
			
			if (j >= cost[i] + f) {
				dp[i][j][0] = (dp[i][j][0] + dp[i-1][j-cost[i]-f][0]) % MOD;
			}
			
			dp[i][j][1] = (dp[i-1][j][0] + dp[i-1][j][1]) % MOD;
			//cout << i << " " << j << " = " << dp[i][j][0] << ", " << dp[i][j][1] << endl;
		}
	}
	
	cout << (dp[n][b][0] + dp[n][b][1]) % MOD << endl;
	return 0;
}
