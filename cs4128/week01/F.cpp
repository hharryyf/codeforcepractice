#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#define MAX_VAL 100000000000000ll
typedef long long ll;
using namespace std;
ll coins[1011];

int main() {
	int T;
	scanf("%d", &T);
	while (T > 0) {
		int n, i, j;
		scanf("%d", &n);
		// dp[i][j] = minimum total number of coins that up to the first
		// i coins with j coins selected
		vector<vector<ll> > dp = vector<vector<ll> >(n + 1, vector<ll>(n+1,MAX_VAL));
		for (i = 1 ; i <= n; i++) {
			cin >> coins[i];
		}
		
		dp[0][0] = 0;
		coins[n+1] = MAX_VAL;
		int ans = 1;
		for (i = 1; i <= n; i++) {
			for (j = 1; j <= i; j++) {
				if (coins[i] > dp[i-1][j-1]) {
					dp[i][j] = min(dp[i-1][j-1] + coins[i], dp[i-1][j]);
				} else {
					
					dp[i][j] = dp[i-1][j];
				}
				
				if (dp[i][j] < coins[i+1]) {
					ans = max(ans, j);
				} else {
					dp[i][j] = MAX_VAL;
				}
				
				// cout << i << ", " << j << "   " << dp[i][j] << endl;
			}
		}
		
		cout << ans << endl;
		T--;
	}
	return 0;
}
