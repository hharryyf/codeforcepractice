#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll dp[32][2];

int main() {
	dp[0][0] = 1;
	dp[0][1] = 0;
	dp[1][0] = 0;
	dp[1][1] = 1;
	int i;
	for (i = 2; i <= 30; i++) {
		dp[i][0] = 2 * dp[i-1][1] + dp[i-2][0];
		dp[i][1] = dp[i-1][0] + dp[i-2][1];
	}
	
	int n;
	while (scanf("%d", &n) != EOF) {
		if (n == -1) break;
		printf("%lld\n", dp[n][0]);
	}
	return 0;
}
