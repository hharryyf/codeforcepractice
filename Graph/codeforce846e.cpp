#include <bits/stdc++.h>
#define INF (1ll << 61)
#define MAX_SIZE 100111
typedef long long ll;
using namespace std;

vector<int> g[MAX_SIZE];
ll a[MAX_SIZE], b[MAX_SIZE];
ll dp[MAX_SIZE];
ll wt[MAX_SIZE];
int n;

void dfs(int v) {
	for (auto nv : g[v]) {
		dfs(nv);
		if (dp[nv] < 0) {
			// we should do something like 
			// dp[v] += dp[nv] * wt[nv]
			// dp[nv] = 0
			// but this might overflow :(, hence we 
			// need some more observation, note that if dp[v] is smaller
			// than -1e12 * 1e5, it can never be made positive
			if (INF / wt[nv] <= -dp[nv]) {
				dp[nv] = 0;
				dp[v] = -INF;
			} else {
				dp[v] += dp[nv] * wt[nv];
				dp[nv] = 0;
				if (dp[v] < -INF) dp[v] = -INF;
			}
		} else {
			dp[v] += dp[nv];
			dp[nv] = 0;
		}
	}
}

int main() {
	int i;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) {
		scanf("%I64d", &b[i]);
	}
	
	for (i = 1; i <= n; ++i) {
		scanf("%I64d", &a[i]);
	}
	
	for (i = 1; i <= n; ++i) {
		dp[i] = b[i] - a[i];
	}
	
	for (i = 2; i <= n; ++i) {
		int v;
		ll k;
		scanf("%d%I64d", &v, &k);
		g[v].push_back(i);
		wt[i] = k;
	}
	
	dfs(1);
	
	printf("%s\n", dp[1] >= 0 ? "YES" : "NO");
	
	return 0;
}