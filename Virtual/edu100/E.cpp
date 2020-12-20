#include <bits/stdc++.h>
#define MAX_SIZE 300011
typedef long long ll;
using namespace std;
int up[MAX_SIZE], down[MAX_SIZE];
int f[MAX_SIZE], p[MAX_SIZE];
vector<int> g[MAX_SIZE];
vector<int> h[MAX_SIZE];
int visited[MAX_SIZE];
vector<int> ret;
vector<int> ans;
int pos[MAX_SIZE];
int cycle = 0;
int N, K;

int find(int x) {
	if (f[x] == x) return x;
	return f[x] = find(f[x]);
}

void dfs(int v) {
	visited[v] = 1;
	for (auto nv : g[v]) {
		if (visited[nv] == 1) {
			cycle = 1;
		}

		if (visited[nv] == 0) {
			dfs(nv);
		}
	}

	visited[v] = 2;
	ret.push_back(v);
}

void dfs2(int v) {
	visited[v] = 1;
	ans.push_back(v);
	for (auto nv : h[v]) {
		dfs2(nv);
	}
}

int main() {
	int i;
	scanf("%d%d", &N, &K);
	for (i = 0 ; i < MAX_SIZE; ++i) {
		f[i] = up[i] = down[i] = i;
	}
	
	for (i = 1; i <= N; ++i) {
		scanf("%d", &p[i]);
	}

	for (i = 1; i <= K; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		h[u].push_back(v);
		if (find(u) == find(v)) {
			printf("0\n");
			return 0;
		}

		int x = find(u), y = find(v);
		if (down[x] != u || up[y] != v) {
			printf("0\n");
			return 0;
		}

		int v1 = up[x], v2 = down[y];
		f[x] = y;
		up[find(x)] = v1, down[find(y)] = v2;
	}

	for (i = 1; i <= N; ++i) {
		if (p[i] != 0 && find(i) != find(p[i])) {
			g[find(p[i])].push_back(find(i));
		}
	}

	for (i = 1; i <= N; ++i) {
		if (!visited[i]) {
			dfs(i);
		}
	}

	if (cycle) {
		printf("0\n");
		return 0;
	}

	reverse(ret.begin(), ret.end());
	memset(visited, 0, sizeof(visited));
	for (auto v : ret) {
		if (find(v) == v) {
			dfs2(up[find(v)]);
		}
	}

	for (i = 0; i < (int) ans.size(); ++i) {
		pos[ans[i]] = i;
	}

	for (i = 1; i <= N; ++i) {
		if (pos[p[i]] > pos[i]) {
			printf("0\n");
			return 0;
		}
	}

	for (auto v : ans) {
		printf("%d ", v);
	}
	printf("\n");
	return 0;
}