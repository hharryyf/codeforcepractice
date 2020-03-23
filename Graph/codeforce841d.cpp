#include <bits/stdc++.h>
#define MAX_SIZE 300111
using namespace std;

struct edge {
	int to;
	int id;
};

vector<edge> g[MAX_SIZE];
int visited[MAX_SIZE];
int deg[MAX_SIZE];
vector<int> ans;
int cnt;
int cnt1;

void dfs(int v) {
	visited[v] = 1;
	for (auto e : g[v]) {
		int nv = e.to;
		int id = e.id;
		if (!visited[nv]) {
			dfs(nv);
			if (deg[nv]) {
				ans.push_back(id);
				deg[nv] = 0;
				deg[v] ^= 1;
			}
		}
	}
}

int main() {
	int i, n, m;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n; ++i) {
		scanf("%d", &deg[i]);
		if (deg[i] < 0) ++cnt1;
		else {
			cnt += deg[i];
		}
	}
	
	for (i = 1; i <= m; ++i) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		g[v1].push_back(edge{v2, i});
		g[v2].push_back(edge{v1, i});
	}
	
	if (cnt % 2 == 1 && cnt1 == 0) {
		printf("-1\n");
		return 0;
	}
	
	for (i = 1; i <= n; ++i) {
		if (deg[i] == -1) {
			deg[i] = cnt % 2;
			cnt = 0;
		}
	}
	
	dfs(1);
	
	printf("%d\n", (int) ans.size());
	
	sort(ans.begin(), ans.end());
	
	for (auto v : ans) {
		printf("%d\n", v);
	}
	return 0;
}