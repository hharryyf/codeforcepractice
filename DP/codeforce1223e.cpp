#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 500011
using namespace std;

vector<pair<int, ll>> g[MAX_SIZE];
int n, k;
ll dp[MAX_SIZE][2];

// dp[v][0] = maximum score of subtree v when select no more than k (v,u) edges
// dp[v][1] = maximum score of subtree v when none of the (v, u) edge is selected

void dfs(int v, int pre) {
	int sz = g[v].size(), i;
	vector<ll> disc;
	for (i = 0 ; i < sz; ++i) {
		if (g[v][i].first != pre) {
			dfs(g[v][i].first, v);
			dp[v][0] += dp[g[v][i].first][0];
			dp[v][1] += dp[g[v][i].first][0];
			disc.push_back(dp[g[v][i].first][1] - dp[g[v][i].first][0] + g[v][i].second);
		}
	}
	
	sort(disc.begin(), disc.end(), greater<ll>());
	sz = (int) disc.size();
	for (i = 0 ; i < k && i < sz; ++i) {
		if (disc[i] <= 0) break;
		dp[v][0] += disc[i];
		if (i < k - 1) {
			dp[v][1] += disc[i];
		}
	}
}

int main() {
	int T, i;
	scanf("%d", &T);
	while (T > 0) {
		scanf("%d%d", &n, &k);
		for (i = 1; i <= n; ++i) {
			g[i].clear();
			dp[i][0] = dp[i][1] = 0;
		}
		for (i = 1; i < n; ++i) {
			int v1, v2;
			ll w;
			scanf("%d%d%I64d", &v1, &v2, &w);
			g[v1].emplace_back(v2, w);
			g[v2].emplace_back(v1, w);
		}
		
		dfs(1, 0);
		
		printf("%I64d\n", max(dp[1][0], dp[1][1]));
		--T;
	}
	return 0;
}