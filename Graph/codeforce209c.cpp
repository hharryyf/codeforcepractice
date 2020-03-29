#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 1000011
using namespace std;
typedef long long ll;
// we can proof that the order of joining the connected
// components would not affect the final answer
vector<int> g[MAX_SIZE];
int deg[MAX_SIZE];
int visited[MAX_SIZE];
int n, m;
ll tol = 0;
void dfs(int v) {
	visited[v] = 1;
	tol += (deg[v] & 1);
	for (auto nv : g[v]) {
		if (!visited[nv]) dfs(nv);
	}
}

int cost(int a, int b) {
	if (a == 0 && b == 0) return 2;
	if (a == 0 || b == 0) return a + b;
	return a + b - 2;
}

int main() {
	int i;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= m; ++i) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		g[v1].push_back(v2);
		g[v2].push_back(v1);
		++deg[v1], ++deg[v2];
	}
	
	vector<pair<ll, int>> ret;
	for (i = 1; i <= n; ++i) {
		if (!visited[i]) {
			tol = 0;
			dfs(i);
			ret.emplace_back(tol, deg[i] > 0);
		}
	}
	
	ll cnt = 0;
	ll ans = ret[0].first;
	for (i = 1; i < (int) ret.size(); ++i) {
		if (ret[i].second) {
			cnt++;
			ans = cost(ans, ret[i].first);
		}
	}
	
	printf("%I64d\n", cnt + ans / 2);
	return 0;
}