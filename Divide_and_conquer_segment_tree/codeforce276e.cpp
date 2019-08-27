#include <bits/stdc++.h>
#define MAX_LEN 131075

using namespace std;

// the bfsorder of all of the points, 0 indexed
int bfsorder[MAX_LEN];

// the dfs order of all of the points, 0 indexed
int dfsorder[MAX_LEN];

// the depth of all of the points 
int depth[MAX_LEN];

// the segment tree for the sum gained by the level-order
int bfstree[2 * MAX_LEN];

// the segment tree for the sum gained by the dfs-order
int dfstree[2 * MAX_LEN];

// the lazy tree of the bfstree
int lazybfs[2 * MAX_LEN];

// the lazy tree of the dfstree
int lazydfs[2 * MAX_LEN];

// the tree represents as a graph
vector<int> graph[MAX_LEN];

// visited array for the bfs
int visited[MAX_LEN];

// visited array for the dfs
int visited2[MAX_LEN];

// the rightmost vertex for each depth
int Right[MAX_LEN];

// the inverteddepth for each node
int invertdepth[MAX_LEN];

// the depth first search that determines the depth first order of all points
void dfs(int vertex, int d);

// breath first search that start from src
void bfs(int src);

// a global variable that records the order of the nodes expanded
int order;

// segment tree update
void update(int st, int ed, int l, int r, int tree[], int lazy[], int index, int delta);

// query in a segment tree
int query(int st, int ed, int l, int r, int tree[], int lazy[], int index);

int main(int argc, char *argv[]) {
	int n, q, i;
	cin >> n >> q;
	for (i = 0 ; i < n-1; i++) {
		int v1, v2;
		cin >> v1 >> v2;
		graph[v1].push_back(v2);
		graph[v2].push_back(v1);
	}
	
	order = 0;
	dfs(1, 0);
	bfs(1);

	for (i = 0 ; i < q; i++) {
		int r, v, x, d;
		cin >> r;
		if (r == 0) {
			cin >> v >> x >> d;
			if (d > depth[v]) {
				update(0, bfsorder[Right[min(d - depth[v], invertdepth[1])]], 0, n - 1, bfstree, lazybfs, 1, x);
				update(dfsorder[v] - (2 * depth[v] - d) + 1, dfsorder[v], 0, n - 1, dfstree, lazydfs, 1, x);
				update(dfsorder[v] + max(1, d - 2 * depth[v] + 1), dfsorder[v] + min(d, invertdepth[v]), 
								0, n - 1, dfstree, lazydfs, 1, x);
			} else if (d == depth[v]) {
				update(dfsorder[v] - d + 1, dfsorder[v] + min(d, invertdepth[v]), 0, n - 1, dfstree, lazydfs, 1, x);
				update(0, 0, 0, n - 1, dfstree, lazydfs, 1, x);
			} else {
				update(dfsorder[v] - d, dfsorder[v] + min(d, invertdepth[v]), 0, n - 1, dfstree, lazydfs, 1, x);
			}
		} else if (r == 1) {
			cin >> v;
			int dv = query(dfsorder[v], dfsorder[v], 0, n - 1, dfstree, lazydfs, 1);
			int bv = query(bfsorder[v], bfsorder[v], 0, n - 1, bfstree, lazybfs, 1);
			cout << dv + bv << endl;
		}
	}	
	return 0;
}

// depth first search
void dfs(int vertex, int d) {
	visited2[vertex] = 1;
	depth[vertex] = d;
	dfsorder[vertex] = order;
	order++;
	for (auto v : graph[vertex]) {
		if (visited2[v] == 0) {
			dfs(v, d + 1);
			invertdepth[vertex] = max(invertdepth[vertex], 1 + invertdepth[v]);
		}
	}
}

// breath first search that start from src
void bfs(int src) {
	int prev = -1;
	queue<int> q = queue<int>();
	q.push(src);
	order = 0;
	while (!q.empty()) {
		int nextv = q.front();
		q.pop();	
		if (visited[nextv]) continue;
		visited[nextv] = 1;
		bfsorder[nextv] = order++;
		if (prev != -1 && depth[prev] != depth[nextv]) {
			Right[depth[prev]] = prev;
		}
		
		prev = nextv;
		for (auto v : graph[nextv]) {
			if (!visited[v]) {
				q.push(v);
			}
		}
	}
	
	if (prev != -1) {
		Right[depth[prev]] = prev; 
	}
}

// segment tree update
void update(int st, int ed, int l, int r, int tree[], int lazy[], int index, int delta) {
	if (st > ed || l > r) return;
	if (lazy[index] != 0) {
		tree[index] += lazy[index];
		if (l != r) {
			lazy[index * 2] += lazy[index];
			lazy[index * 2 + 1] += lazy[index];
		}
		lazy[index] = 0;
	}
	
	if (l > ed || r < st) return;
	if (l >= st && r <= ed) {
		tree[index] += delta;
		if (l != r) {
			lazy[index * 2] += delta;
			lazy[index * 2 + 1] += delta;
		}
		return;
	}
	
	int mid = l + (r - l) / 2;
	update(st, ed, l, mid, tree, lazy, index * 2, delta);
	update(st, ed, mid + 1, r, tree, lazy, index * 2 + 1, delta);
	tree[index] = max(tree[index * 2], tree[2 * index + 1]);
}

// query in a segment tree
int query(int st, int ed, int l, int r, int tree[], int lazy[], int index) {
	if (lazy[index] != 0) {
		tree[index] += lazy[index];
		if (l != r) {
			lazy[index * 2] += lazy[index];
			lazy[index * 2 + 1] += lazy[index];
		}
		lazy[index] = 0;
	}
	
	if (l > ed || r < st) return 0;
	if (l >= st && r <= ed) return tree[index];
	
	int mid = l + (r - l) / 2;
	return max(query(st, ed, l, mid, tree, lazy, index * 2), query(st, ed, mid + 1, r, tree, lazy, index * 2 + 1));
}
