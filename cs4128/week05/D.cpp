#include <bits/stdc++.h>
#define MAX_SIZE 101111
#define MOD 1000000007

typedef long long ll;

using namespace std;

ll dp[MAX_SIZE][2];

vector<int> g[MAX_SIZE];

int color[MAX_SIZE];

/* 
	https://vjudge.net/contest/336580#problem/D
	The case a black component = a white component + a black component was
	ignored.
*/

void dfs(int v, int pre) {
	dp[v][color[v]] = 1;
	for (auto nextv : g[v]) {
		if (nextv != pre) {
			dfs(nextv, v);
			// current component has one black vertices
			// could be made by combining a black and white component, disconnect a black component
			// and black component
			// combining a white and black component 
			dp[v][1] = ((dp[v][1] * (dp[nextv][1] + dp[nextv][0])) % MOD + (dp[v][0] * dp[nextv][1])) % MOD;
			// could be made by combining a white component and a white component or disconnect
			// a black component
			dp[v][0] = dp[v][0] * (dp[nextv][0] + dp[nextv][1]);
			dp[v][0] %= MOD;
		}
	}
	
	
}

int main() {
	int n, i;
	scanf("%d", &n);
	for (i = 1; i <= n - 1; i++) {
		int v;
		scanf("%d", &v);
		g[v].push_back(i);
		g[i].push_back(v);
	}
	
	for (i = 0; i < n; i++) {
		scanf("%d", &color[i]);
	}
	
	dfs(0, -1);
	
	printf("%lld\n", dp[0][1] % MOD);
	/*
	for (i = 0 ; i <= 9; i++) {
		printf("dp[%d][0] = %lld, dp[%d][1] = %lld\n", i, dp[i][0], i, dp[i][1]);
	}
	*/
	return 0;
}
