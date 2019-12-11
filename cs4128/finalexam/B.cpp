#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 50011
using namespace std;

int dp[MAX_SIZE][3];

int prefix[MAX_SIZE];

int main() {
	int n, w, k, i;
	scanf("%d%d%d", &n, &w, &k);
	for (i = 1; i <= n; i++) {
		scanf("%d", &prefix[i]);
		prefix[i] += prefix[i-1];
	}
	
	for (i = 1; i <= n; i++) {
		int mns = i >= w ? prefix[i-w] : 0;
		dp[i][0] = max(dp[i-1][0], prefix[i] - mns);
		dp[i][1] = max(dp[i-1][1], prefix[i] - mns + (i >= w ? dp[i-w][0] : 0));
		dp[i][2] = max(dp[i-1][2], prefix[i] - mns + (i >= w ? dp[i-w][1] : 0));
	}	
	
	cout << dp[n][k-1] << endl;
	return 0;
}
