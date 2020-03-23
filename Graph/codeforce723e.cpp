#include <bits/stdc++.h>
#define MAX_SIZE 411
using namespace std;

unordered_set<int> g[MAX_SIZE];
int deg[MAX_SIZE];
int visited[MAX_SIZE];
int id[MAX_SIZE];
vector<pair<int, int>> ret;
const int sp = 201;
void init() {
	int i;
	for (i = 0 ; i < MAX_SIZE; ++i) {
		g[i].clear();
		deg[i] = 0;
		visited[i] = 0;
		id[i] = 0;
	}
}

void dfs(int v, int cid) {
	id[v] = cid;
	for (auto nv : g[v]) {
		if (!id[nv]) {
			dfs(nv, cid);
		}
	}
}

void euler(int v) {
	while (!g[v].empty()) {
		int nv = *g[v].begin();
		g[v].erase(nv);
		g[nv].erase(v);
		euler(nv);
		ret.push_back(make_pair(v, nv));
	}
}

int main() {
	int T, i;
	scanf("%d", &T);
	while (T > 0) {
		int n, m;
		init();
		scanf("%d%d", &n, &m);
		for (i = 1; i <= m; ++i) {
			int v1, v2;
			scanf("%d%d", &v1, &v2);
			g[v1].insert(v2);
			g[v2].insert(v1);
			++deg[v1], ++deg[v2];
		}
		
		int cnt = 1;
		int ans = 0;
		for (i = 1; i <= n; ++i) {
			if (!id[i]) {
				dfs(i, cnt++);
			}
		}
		
		for (i = 1; i <= n; ++i) {
			if (deg[i] % 2 == 1) {
				g[i].insert(id[i] + sp);
				g[sp + id[i]].insert(i);
			} else {
				++ans;
			}
		}
		
		printf("%d\n", ans);
		for (i = 1; i <= n; ++i) {
			if (!visited[id[i]]) {
				visited[id[i]] = 1;
				ret.clear();
				euler(i);
				for (auto p : ret) {
					if (p.first <= n && p.second <= n) {
						printf("%d %d\n", p.first, p.second);
					}
				}
			}
		}
		
		T--;
	}
	return 0;
}