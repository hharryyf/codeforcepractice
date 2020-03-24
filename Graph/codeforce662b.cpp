#include <bits/stdc++.h>
#define MAX_SIZE 100111
using namespace std;

vector<pair<int, int>> g[MAX_SIZE];
int visited[MAX_SIZE];
bool valid = true;
vector<int> ans[2];
vector<int> tmp[2];
int n;

void dfs(int v, int c) {
	for (auto np : g[v]) {
		int nv = np.first, cl = np.second;
		if (visited[nv] == -1) {
			if (cl == c) {
				visited[nv] = visited[v];
				tmp[visited[nv]].push_back(nv);
			} else {
				visited[nv] = visited[v] ^ 1;
				tmp[visited[nv]].push_back(nv);
			}
			dfs(nv, c);
		} else {
			if (visited[nv] == visited[v] && cl != c) {
				valid = false;
			}
			
			if (visited[nv] != visited[v] && cl == c) {
				valid = false;
			}
		}
	}
}
// solve and make all colors to color c
bool solve(int c) {
	int i;
	for (i = 0 ; i < MAX_SIZE; ++i) visited[i] = -1;
	for (i = 1; i <= n; ++i) {
		if (visited[i] == -1) {
			valid = true;
			tmp[0].clear(), tmp[1].clear();
			tmp[0].push_back(i);
			visited[i] = 0;
			dfs(i, c);
			if (!valid) return false;
			if (tmp[0].size() < tmp[1].size()) {
				for (auto v : tmp[0]) ans[c].push_back(v);
			} else {
				for (auto v : tmp[1]) ans[c].push_back(v);
			}
		}
	}
	return true;
}

char st[4];

int main() {
	int i, m;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= m; ++i) {
		int v1, v2;
		scanf("%d%d%s", &v1, &v2, st);
		if (st[0] == 'B') {
			g[v1].emplace_back(v2, 1);
			g[v2].emplace_back(v1, 1);
		} else {
			g[v1].emplace_back(v2, 0);
			g[v2].emplace_back(v1, 0);
		}
	}

	bool ret1 = solve(0), ret2 = solve(1);
	int idx = 1;
	if (!ret1 && !ret2) {
		printf("-1\n");
		return 0;
	}
	
	if (ret1) {
		idx = 0;
	}
	
	if (ret2 && ans[0].size() > ans[1].size()) {
		idx = 1;
	}

	printf("%d\n", (int) ans[idx].size());
	for (auto v : ans[idx]) {
		printf("%d ", v);
	}
	printf("\n");
	return 0;
}