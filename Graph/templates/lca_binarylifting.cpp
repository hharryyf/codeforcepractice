#include <bits/stdc++.h>
#define MAX_SIZE 201111

using namespace std;

int height[MAX_SIZE];
// the graph must be a tree!!
vector<int> g[MAX_SIZE];
int parent[MAX_SIZE][19];
int n;
int logs[MAX_SIZE];
void precompute() {
	int i;
	logs[0] = 0, logs[1] = 0;
	for (i = 2; i <= n; i++) {
		logs[i] = logs[i / 2] + 1;
	}
}

void dfs(int v, int pre, int d) {
	height[v] = d;
	int i;
	parent[v][0] = pre;
	for (i = 1; i <= logs[n]; i++) {
		parent[v][i] = parent[parent[v][i-1]][i-1];
	}
	
	for (auto nextv : g[v]) {
		if (nextv != pre) {
			dfs(nextv, v, d + 1);
		}
	}
}

int LCA(int u, int v) {
	if (height[u] < height[v]) {
		swap(u, v);
	}
	
	int i;
	for (i = logs[n]; i >= 0; i--) {
		if (height[u] >= (1 << i) + height[v]) {
			u = parent[u][i];
		} 
	}
	
	if (u == v) return u;
	
	for (i = logs[n]; i >= 0; i--) {
		if (parent[u][i] != parent[v][i]) {
			u = parent[u][i];
			v = parent[v][i];
		}
	}
	
	return parent[u][0];
}

void testing();

void connect(int v1, int v2) {
	g[v1].push_back(v2);
	g[v2].push_back(v1);
}

int main() {
	testing();
	return 0;
}

void testing() {
	n = 13;
	connect(1, 13);
	connect(1, 2);
	connect(1, 4);
	connect(3, 2);
	connect(5, 3);
	connect(5, 12);
	connect(6, 4);
	connect(8, 6);
	connect(11, 6);
	connect(4, 7);
	connect(7, 9);
	connect(10, 9);
	precompute();
	dfs(1, 0, 0);
	assert(LCA(1, 2) == 1);
	assert(LCA(2, 1) == 1);
	assert(LCA(1, 3) == 1);
	assert(LCA(3, 1) == 1);
	assert(LCA(2, 12) == 2);
	assert(LCA(13, 12) == 1);
	assert(LCA(12, 13) == 1);
	assert(LCA(8, 11) == 6);
	assert(LCA(11, 4) == 4);
	assert(LCA(10, 7) == 7);
	assert(LCA(8, 9) == 4);
	assert(LCA(5, 10) == 1);
	assert(LCA(3, 10) == 1);
	cout << "pass all tests" << endl;
}
