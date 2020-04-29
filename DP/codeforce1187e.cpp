#include <bits/stdc++.h>
#define MAX_SIZE 200011
typedef long long ll;
using namespace std;

vector<int> g[MAX_SIZE];
int sz[MAX_SIZE];
ll dp1[MAX_SIZE], dp2[MAX_SIZE];
int n;

void dfs(int v, int pre) {
	sz[v] = 1;
	for (auto nv : g[v]) {
		if (nv != pre) {
			dfs(nv, v);
			sz[v] += sz[nv];
		}
	}
	
	dp1[v] = sz[v];
	for (auto nv : g[v]) {
		if (nv != pre) {
			dp1[v] += dp1[nv];
		}
	}
}

void dfs2(int v, int pre) {
	for (auto nv : g[v]) {
		if (nv != pre) {
			dp2[nv] = dp2[v] + n - 2 * sz[nv];
			dfs2(nv, v);
		}
	}
}

int main() {
	int i;
	scanf("%d", &n);
	for (i = 1; i < n; ++i) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		g[v1].push_back(v2);
		g[v2].push_back(v1);
	}
	dfs(1, 0);
	dp2[1] = dp1[1];
	dfs2(1, 0);
	ll ans = 0;
	for (i = 1; i <= n; ++i) {
		ans = max(ans, max(dp1[i], dp2[i]));
	}
	printf("%I64d\n", ans);
	return 0;
}