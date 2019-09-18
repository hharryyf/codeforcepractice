#include <bits/stdc++.h>
#define MAX_SIZE (200000 + 11)
typedef long long ll;

using namespace std;

int n;

vector<pair<int, int> > graph[MAX_SIZE];

typedef struct node {
	// c01 the number of pair that is rooted at the current node and
	// make pair with the nodes in the subtree with 0.......1 edge
	ll c01, c11,c00,c10;
} TreeNode;


ll ans = 0ll;
TreeNode dp[MAX_SIZE];

void dfs(int v, int prev);

int main() {
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		int v1, v2, w;
		scanf("%d%d%d", &v1, &v2, &w);
		graph[v1].push_back(make_pair(v2, w));
		graph[v2].push_back(make_pair(v1, w));
	}	
	
	dfs(1, -1);
	
	cout << ans << endl;
	return 0;
}

void dfs(int v, int prev) {
	for (auto nextp : graph[v]) {
		// connection between v and nextv.nid is nextv.wt
		if (nextp.first != prev) {
			int nextv = nextp.first, nextwt = nextp.second;
			dfs(nextv, v);
			if (nextwt == 1) {
				ans += 2 * dp[v].c11 * (dp[nextv].c11 + 1);
				ans += (dp[v].c00 + dp[v].c10) * (dp[nextv].c11 + 1);
				ans += dp[v].c11 * (dp[nextv].c10 + dp[nextv].c00);
				dp[v].c10 += dp[nextv].c00 + dp[nextv].c10;
				dp[v].c11 += dp[nextv].c11 + 1; 
			} else {
				ans += 2 * dp[v].c00 * (dp[nextv].c00 + 1);
				ans += (dp[v].c11 + dp[v].c01) * (dp[nextv].c00 + 1);
				ans += dp[v].c00 * (dp[nextv].c01 + dp[nextv].c11);
				dp[v].c00 += dp[nextv].c00 + 1;
				dp[v].c01 += dp[nextv].c01 + dp[nextv].c11;
			}
		}
	}
	
	ans += 2 * dp[v].c00;
	ans += 2 * dp[v].c11;
	ans += dp[v].c10;
	ans += dp[v].c01;
}
