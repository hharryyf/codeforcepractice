#include <bits/stdc++.h>
#define MAX_LEN 524298

using namespace std;

// the segment tree
int tree[MAX_LEN];
// the lazy information
int lazy[MAX_LEN];

// dfs order[i] (start from from 0), marks the dfs order of the ith node
int dfsorder[MAX_LEN >> 1];
// subtree i means the size of the subtree of the node i
int subtree[MAX_LEN >> 1];
// tree represents as a graph in adj-list format
vector<int> graph[MAX_LEN >> 1];

// find the dfs order of all the vertices
void dfs(int vertex, int &num, int parent);
// build operation
void build(int l, int r, int index);
// operations
char oper[10];
// corresponding value
int value[MAX_LEN >> 1];
// switch start to end
void update(int start, int end, int l, int r, int index);

int query(int start, int end, int l, int r, int index);

int main(int argc, char *argv[]) {
	int i, n, m, v;
	cin >> n;
	for (i = 2 ; i <= n; i++) {
		scanf("%d", &v);
		graph[v].push_back(i);
	}
	
	v = 0;
	dfs(1, v, 0);
	
	for (i = 1 ; i <= n; i++) {
		scanf("%d", &v);
		value[dfsorder[i]] = v;
	}
	
	build(0, n - 1, 1);
	scanf("%d", &m);
	for (i = 0 ; i < m; i++) {
		scanf("%s%d", oper, &v);
		if (oper[0] == 'p') {
			update(dfsorder[v], dfsorder[v] + subtree[v] - 1, 0, n - 1, 1);
		} else if (oper[0] == 'g') {
			printf("%d\n", query(dfsorder[v], dfsorder[v] + subtree[v] - 1, 0, n - 1, 1));
		}
	}
	return 0;
}

int query(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return 0;
	if (lazy[index] != 0) {
		tree[index] = (r - l + 1) - tree[index];
		if (l != r) {
			lazy[index * 2] = 1 - lazy[2 * index];
			lazy[index * 2 + 1] = 1 - lazy[2 * index + 1];
		}
		lazy[index] = 0;
	}
	
	if (start > r || l > end) return 0;
	if (start <= l && r <= end) {
		return tree[index];
	}
	
	int mid = l + (r - l) / 2;
	return query(start, end, l, mid, index * 2) + query(start, end, mid + 1, r, index * 2 + 1);
}

void update(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return;
	if (lazy[index] != 0) {
		tree[index] = (r - l + 1) - tree[index];
		if (l != r) {
			lazy[index * 2] = 1 - lazy[2 * index];
			lazy[index * 2 + 1] = 1 - lazy[2 * index + 1];
		}
		lazy[index] = 0;
	}
	
	if (start > r || l > end) {
		return;
	}
	
	if (start <= l && r <= end) {
		tree[index] = (r - l + 1) - tree[index];
		if (l != r) {
			lazy[index * 2] = 1 - lazy[2 * index];
			lazy[index * 2 + 1] = 1 - lazy[2 * index + 1];
		}
		lazy[index] = 0;
		return;
	}
	
	int mid = l + (r - l) / 2;
	update(start, end, l, mid, index * 2);
	update(start, end, mid + 1, r, index * 2 + 1);
	tree[index] = tree[index * 2] + tree[index * 2 + 1];
}


void dfs(int vertex, int &num, int parent) {
	dfsorder[vertex] = num;
	subtree[vertex] = 1;
	num++;
	for (auto v : graph[vertex]) {
		if (v != parent) {
			dfs(v, num, vertex);
			subtree[vertex] += subtree[v];
		}
	}
}

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index] = value[l];
		return; 
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	tree[index] = tree[index * 2] + tree[index * 2 + 1];
}
