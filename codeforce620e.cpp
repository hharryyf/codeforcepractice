#include <bits/stdc++.h>
#define MAX_SIZE 1048590

typedef long long Long;
using namespace std;

Long tree[MAX_SIZE], lazy[MAX_SIZE];

vector<int> graph[MAX_SIZE >> 1];

int dfsorder[MAX_SIZE >> 1];
int subtree[MAX_SIZE >> 1];
int remap[MAX_SIZE >> 1];

int color[MAX_SIZE >> 1];

int visited[MAX_SIZE >> 1];

int n, q;

int k = 0;

// find the dfs order and the subtree size of each of the nodes
void dfs(int v);
// build the tree
void build(int l, int r, int index);
// update with lazy propagation
void update(int start, int end, int l, int r, int index, int c);

Long query(int start, int end, int l, int r, int index);

int main(int argc, char *argv[]) {
	int i;
	scanf("%d%d", &n, &q);
	for (i = 1; i <= n; i++) {
		scanf("%d", &color[i]);
	}
	
	for (i = 0 ; i < n - 1; i++) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		graph[v1].push_back(v2);
		graph[v2].push_back(v1);
	}
	
	dfs(1);
	build(0, n - 1, 1);/*
	for (i = 1; i <= n; i++) {
		printf("%d: %d %d %d\n", i, dfsorder[i], subtree[i], remap[dfsorder[i]]);
		cout << query(dfsorder[i], dfsorder[i], 0, n - 1, 1) << " " << (1ll << color[i]) << endl;
	}*/
	while (q > 0) {
		int type, v, c;
		scanf("%d%d", &type, &v);
		if (type == 1) {
			scanf("%d", &c);
			update(dfsorder[v], dfsorder[v] + subtree[v] - 1, 0, n - 1, 1, c);
		} else if (type == 2) {
			Long ans = query(dfsorder[v], dfsorder[v] + subtree[v] - 1, 0, n - 1, 1);
			int cnt = 0;
			while (ans > 0) {
				if (ans % 2 == 0) {
					ans >>= 1;
				} else {
					cnt++;
					ans = ans - 1;
				}
			}
			
			printf("%d\n", cnt);
		}
		q--;
	}
	
	return 0;
}



void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		// printf("dfsorder = %d map to color[%d] = %lld\n", l, remap[l], (1ll << color[remap[l]]));
		tree[index] = (1ll << color[remap[l]]);
		lazy[index] = 0;
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	tree[index] = tree[index * 2] | tree[index * 2 + 1];
}

void dfs(int v) {
	visited[v] = 1;
	dfsorder[v] = k;
	remap[k] = v;
	subtree[v] = 1;
	k++;
	// dfs and remember don't visit the parent twice!!
	for (auto nextv : graph[v]) {
		if (!visited[nextv]) {
			dfs(nextv);
			subtree[v] += subtree[nextv];
		}
	}
}

void update(int start, int end, int l, int r, int index, int c) {
	if (start > end || l > r) return;
	if (lazy[index] != 0) {
		tree[index] = 1ll << lazy[index];
		if (l != r) {
			lazy[index * 2] = lazy[index];
			lazy[index * 2 + 1] = lazy[index];
		}
		lazy[index] = 0;
	}
	
	if (start > r || end < l) return;
	if (start <= l && r <= end) {
		tree[index] = 1ll << c;
		if (l != r) {
			lazy[index * 2] = c;
			lazy[index * 2 + 1] = c;
		}
		return;
	}
	
	int mid = l + (r - l) / 2;
	update(start, end, l, mid, index * 2, c);
	update(start, end, mid + 1, r, index * 2 + 1, c);
	tree[index] = tree[index * 2] | tree[index * 2 + 1];
}

Long query(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return 0;
	if (lazy[index] != 0) {
		tree[index] = 1ll << lazy[index];
		if (l != r) {
			lazy[index * 2] = lazy[index];
			lazy[index * 2 + 1] = lazy[index];
		}
		lazy[index] = 0;
	}
	
	if (start > r || end < l) return 0;
	if (start <= l && r <= end) return tree[index];
	int mid = l + (r - l) / 2;
	Long t1 = query(start, end, l, mid, index * 2);
	Long t2 = query(start, end, mid + 1, r, index * 2 + 1);
	return t1 | t2;
}
