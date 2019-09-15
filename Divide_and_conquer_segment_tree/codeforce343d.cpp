#include <bits/stdc++.h>
#define MAX_SIZE (1048576 + 11)
using namespace std;

typedef struct segt {
	int lazy, value;
} segmenttree;

segmenttree tree[MAX_SIZE];

vector<int> graph[MAX_SIZE >> 1];
int dfsord[MAX_SIZE >> 1];
int subsize[MAX_SIZE >> 1];
int pred[MAX_SIZE];
int k = 1;

void dfs(int v, int prev);
void update(int start, int end, int l, int r, int index, int val);
int query(int start, int end, int l, int r, int index);
void build(int l, int r, int index);

int main(int argc, char *argv[]) {
	int n;
	scanf("%d", &n);
	for (int i = 0 ; i < n - 1; i++) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		graph[v1].push_back(v2);
		graph[v2].push_back(v1);
	}
	
	dfs(1, 0);
	build(1, n, 1);
	
	int m;
	scanf("%d", &m);
	for (int i = 0 ; i < m; i++) {
		int op, v;
		scanf("%d%d", &op, &v);
		if (op == 1) {
			if (query(dfsord[v], dfsord[v] + subsize[v] - 1, 1, n, 1) !=  subsize[v] && pred[v] != 0) {
				update(dfsord[pred[v]], dfsord[pred[v]], 1, n, 1, 0);
			}
			update(dfsord[v], dfsord[v] + subsize[v] - 1, 1, n, 1, 1);
		} else if (op == 2) {
			update(dfsord[v], dfsord[v], 1, n, 1, 0);
		} else {
			printf("%d\n", query(dfsord[v], dfsord[v] + subsize[v] - 1, 1, n, 1) == subsize[v]);
		}
	}
	return 0;
}

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index].lazy = -1;
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	tree[index].lazy = -1;
}

void update(int start, int end, int l, int r, int index, int val) {
	if (start > end || l > r) return;
	if (tree[index].lazy != -1) {
		tree[index].value = (r - l + 1) * tree[index].lazy;
		if (l != r) {
			tree[index * 2].lazy = tree[index * 2 + 1].lazy = tree[index].lazy;
		}
		tree[index].lazy = -1;
	}
	
	if (start > r || l > end) return;
	if (start <= l && r <= end) {
		tree[index].value = val * (r - l + 1);
		if (l != r) {
			tree[index * 2].lazy = tree[index * 2 + 1].lazy = val;
		}
		return;
	}
	
	int mid = l + (r - l) / 2;
	update(start, end, l, mid, index * 2, val);
	update(start, end, mid + 1, r, index * 2 + 1, val);
	tree[index].value = tree[index * 2].value + tree[index * 2 + 1].value;
}

int query(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return 0;
	if (tree[index].lazy != -1) {
		tree[index].value = (r - l + 1) * tree[index].lazy;
		if (l != r) {
			tree[index * 2].lazy = tree[index * 2 + 1].lazy = tree[index].lazy;
		}
		tree[index].lazy = -1;
	}
	
	if (start > r || l > end) return 0;
	if (start <= l && r <= end) return tree[index].value;
	int mid = l + (r - l) / 2;
	return query(start, end, l, mid, index * 2) + query(start, end, mid + 1, r, index * 2 + 1);
}

void dfs(int v, int prev) {
	pred[v] = prev;
	subsize[v] = 1;
	dfsord[v] = k++;
	for (auto nextv : graph[v]) {
		if (nextv != prev) {
			dfs(nextv, v);
			subsize[v] += subsize[nextv];
		}
	}
}
