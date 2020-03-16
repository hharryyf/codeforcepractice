#include <bits/stdc++.h>
#define MAX_SIZE 10011
#define INF 100000
using namespace std;

int dp[MAX_SIZE][3];
vector<int> g[MAX_SIZE];

void dfs(int v, int pre) {
	dp[v][0] = 1;
	dp[v][2] = 0;
	dp[v][1] = 0;
	bool leaf = true;
	int diff = INF;
	for (auto nv : g[v]) {
		if (nv != pre) {
			leaf = false;
			dfs(nv, v);
			dp[v][0] += min(dp[nv][0], dp[nv][2]);
			dp[v][2] += dp[nv][1];
			dp[v][1] += min(dp[nv][1], dp[nv][0]);
			diff = min(diff, max(0, dp[nv][0] - dp[nv][1]));
		}
	}
	
	if (leaf) {
		dp[v][1] = INF;
	} else {
		dp[v][1] += diff;
	}
}

int main() {
	int n, sp, i;
	while (scanf("%d", &n) != EOF) {
		for (i = 1; i <= n; ++i) g[i].clear();
		
		for (i = 1; i < n; ++i) {
			int v1, v2;
			scanf("%d%d", &v1, &v2);
			g[v1].push_back(v2);
			g[v2].push_back(v1);
		}
		
		dfs(1, 0);
		printf("%d\n", min(dp[1][0], dp[1][1]));
		scanf("%d", &sp);
		// cout << "sp= " << sp << endl;
		if (sp == -1) break;
	}
	return 0;
}