#include <bits/stdc++.h>
#define MAX_SIZE 524312
#define BLACK 1
#define WHITE 2
using namespace std;

const int INF = -400000000;

// the segment tree
int tree[MAX_SIZE];
// the lazy tree
int lazy[MAX_SIZE];
// the number of black nodes below the tree node
int black[MAX_SIZE >> 1];
// the number of white notes below the tree node
int white[MAX_SIZE >> 1];
// the dfs order of the node
int dfsorder[MAX_SIZE >> 1];
// the leftmost child node number of the current node if it exists
int leftmost[MAX_SIZE >> 1];

int color[MAX_SIZE >> 1];

int order = 0;

vector<int> graph[MAX_SIZE >> 1];

// dfs on vertex 
void dfs(int vertex, int arr[], int left[], int depth, int mod, int parent);

// increment start to end by delta
void update(int start, int end, int l, int r, int index, int delta);

// query on start, end maximum value on the segment tree
int query(int start, int end, int l, int r, int index);

int value[MAX_SIZE];

int main(int argc, char *argv[]) {
	int n, q, i, v, u, x;
	cin >> n >> q;
	
	for (i = 1 ; i <= n; i++) {
		cin >> value[i];
	}
	
	for (i = 1 ; i < n; i++) {
		cin >> v >> u;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}	
	
	dfs(1, black, leftmost, 0, 0, -1);
	dfs(1, white, leftmost, 0, 1, -1);
	/*
	for (i = 1; i <= n; i++) {
		cout << query(dfsorder[i], dfsorder[i], 0, n - 1, 1) << " " << endl;
	}*/
	
	for (i = 0 ; i < q; i++) {
		cin >> u;
		// cout << i << endl;
		if (u == 1) {
			cin >> x >> v;
			if (color[x] == BLACK) {
				//cout << "increment " << dfsorder[x] << " " << dfsorder[x] + black[x] - 1 << " by " << v << endl;
				update(dfsorder[x], dfsorder[x] + black[x] - 1, 0, n - 1, 1, v);
				if (leftmost[x] != 0) {
					//cout << "increment " << dfsorder[leftmost[x]] << " " << dfsorder[leftmost[x]] + white[x] - 1 << " by " << -v << endl;
					update(dfsorder[leftmost[x]], dfsorder[leftmost[x]] + white[x] - 1, 0, n - 1, 1, -v);
				}
			} else if (color[x] == WHITE) {
				//cout << "increment " << dfsorder[x] << " " << dfsorder[x] + white[x] - 1 << " by " << v << endl;
				update(dfsorder[x], dfsorder[x] + white[x] - 1, 0, n - 1, 1, v);
				if (leftmost[x] != 0) {
					//cout << "increment " << dfsorder[leftmost[x]] << " " << dfsorder[leftmost[x]] + black[x] - 1 << " by " << -v << endl;
					update(dfsorder[leftmost[x]], dfsorder[leftmost[x]] + black[x] - 1, 0, n - 1, 1, -v);
				}
			}
		} else {
			cin >> x;
			cout << query(dfsorder[x], dfsorder[x], 0, n - 1, 1) + value[x] << endl;
		}
	}
	
	return 0;
}

// dfs on vertex 
void dfs(int vertex, int arr[], int left[], int depth, int mod, int parent) {
	if (depth % 2 == mod) {
		dfsorder[vertex] = order++;
	} 
	
	if (depth % 2 == 0) {
		color[vertex] = BLACK;
	} else {
		color[vertex] = WHITE;
	}
	
	for (auto p : graph[vertex]) {
		if (p != parent) {
			if (left[vertex] == 0) {
				left[vertex] = p;
			}
			dfs(p, arr, left, depth + 1, mod , vertex);
			arr[vertex] += arr[p]; 
		}
	}
	
	if (depth % 2 == mod) {
		arr[vertex] += 1;
	}
}

// increment start to end by delta
void update(int start, int end, int l, int r, int index, int delta) {
	if (start > end || l > r) return;
	if (lazy[index] != 0) {
		tree[index] += lazy[index];
		if (l != r) {
			lazy[index * 2] += lazy[index];
			lazy[index * 2 + 1] += lazy[index];
		}
		lazy[index] = 0;
	}
	
	if (start > r || end < l) return;
	
	if (start <= l && r <= end) {
		tree[index] += delta;
		if (l != r) {
			lazy[index * 2] += delta;
			lazy[index * 2 + 1] += delta;
		}
		return;
	}
	
	int mid = l + (r - l) / 2;
	update(start, end, l, mid, index * 2, delta);
	update(start, end, mid + 1, r, index * 2 + 1, delta);
	tree[index] = max(tree[index * 2], tree[index * 2 + 1]);
}

int query(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return INF;
	if (lazy[index] != 0) {
		tree[index] += lazy[index];
		if (l != r) {
			lazy[index * 2] += lazy[index];
			lazy[index * 2 + 1] += lazy[index];
		}
		lazy[index] = 0;
	}
	
	if (start > r || end < l) return INF;
	
	if (start <= l && r <= end) {
		return tree[index];
	}
	
	int mid = l + (r - l) / 2;
	return max(query(start, end, l, mid, index * 2), query(start, end, mid + 1, r, index * 2 + 1));
}
