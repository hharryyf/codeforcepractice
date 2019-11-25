#include <bits/stdc++.h>
#define MAX_SIZE 131092

using namespace std;

int n;

vector<int> g[MAX_SIZE];
int parent[MAX_SIZE][19];
int height[MAX_SIZE];
int subsz[MAX_SIZE];

void dfs(int v, int pre, int dpt) {
	parent[v][0] = pre;
	height[v] = dpt;
	subsz[v] = 1;
	int i;
	for (i = 1; i < 19; i++) {
		parent[v][i] = parent[parent[v][i-1]][i-1];
	}
	
	for (auto nv : g[v]) {
		if (nv != pre) {
			dfs(nv, v, dpt + 1);
			subsz[v] += subsz[nv];
		}
	}
}

int LCA(int a, int b) {
	int i;
	if (height[a] < height[b]) {
		swap(a, b);
	}
	
	for (i = 18; i >= 0; i--) {
		if (height[a] >= (1 << i) + height[b]) {
			a = parent[a][i];
		}
	}
	
	if (a == b) return a;
	
	for (i = 18; i >= 0; i--) {
		if (parent[a][i] != parent[b][i]) {
			a = parent[a][i];
			b = parent[b][i];
		}
	}
	
	return parent[a][0];
}

int kparent(int v, int k) {
	if (k < 0) return 0;
	int i;
	for (i = 18; i >= 0; i--) {
		if (k >= (1 << i)) {
			v = parent[v][i];
			k = k - (1 << i);
		}
	}
	return v;
}

void solve(int v1, int v2) {
	int v = LCA(v1, v2);
	int dist = height[v1] + height[v2] - 2 * height[v];
	if (v1 == v2) {
		printf("%d\n", n);
		return;
	}
	
	if (dist % 2 == 1) {
		printf("0\n");
		return;
	}
	
	if (height[v1] != height[v2]) {
		if (height[v1] < height[v2]) {
			swap(v1, v2);
		}	
		
		int p1 = kparent(v1, dist / 2);
		int p2 = kparent(v1, dist / 2 - 1);
		printf("%d\n", subsz[p1] - subsz[p2]);
	} else {
		int p1 = kparent(v1, height[v1] - height[v] - 1);
		int p2 = kparent(v2, height[v2] - height[v] - 1);
		printf("%d\n", n - subsz[p1] - subsz[p2]);
	}
}

int main() {
	scanf("%d", &n);
	int i;
	for (i = 1; i < n; i++) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		g[v1].push_back(v2);
		g[v2].push_back(v1);
	}
	
	dfs(1, 0, 1);
	int q;
	scanf("%d", &q);
	while (q > 0) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		solve(v1, v2);
		q--;
	}
	return 0;
}
