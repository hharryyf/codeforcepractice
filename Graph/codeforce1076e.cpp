#include <bits/stdc++.h>
#define MAX_SIZE (300000 + 21)
#define shift(x) (x & (-x))
using namespace std;

typedef long long ll;

typedef struct query {
	int pt;
	int dist;
	ll inc;
} Query;

vector<int> graph[MAX_SIZE];

typedef struct segt {
	ll lazy, value;
} segmenttree;

segmenttree tree[MAX_SIZE << 2];

int dfsord[MAX_SIZE];

int n;

int k = 1;

int m;

Query qrs[MAX_SIZE];

static bool cmp(const Query &a, const Query &b) {
	return dfsord[a.pt] < dfsord[b.pt];
}


void dfs_0(int v, int prev);

void update(int start, int end, int l, int r, int index, ll v);

ll query(int start, int end, int l, int r, int index);

void dfs(int v, int prev, int depth);

ll ans[MAX_SIZE];

int main(int argc, char *argv[]) {
	scanf("%d", &n);
	int i;
	for (i = 0 ; i < n - 1; i++) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		graph[v1].push_back(v2);
		graph[v2].push_back(v1);
	}
	
	dfs_0(1, -1);
	scanf("%d", &m);
	for (i = 0 ; i < m; i++) {
		scanf("%d%d%lld", &qrs[i].pt, &qrs[i].dist, &qrs[i].inc);
	}
	
	sort(qrs, qrs + m, cmp);
	
	k = 0;
	dfs(1, -1, 1);
	
	for (i = 1; i <= n; i++) {
		printf("%lld ", ans[i]);
	}
	printf("\n");
	return 0;
}

void dfs(int v, int prev, int depth) {
	int st = k, ed = k;
	// if the queries are all dealt with, we can ignore the following dfs
	while (k < m && dfsord[v] == dfsord[qrs[k].pt]) {
		update(depth, min(depth + qrs[k].dist, n), 1, n, 1, qrs[k].inc);
		k++;
	}
	
	ed = k - 1;
	
	ans[v] = query(depth, depth, 1, n, 1);
	
	for (auto nextv : graph[v]) {
		if (nextv != prev) {
			dfs(nextv, v, depth + 1);
		}
	}
	
	while (ed >= st) {
		update(depth, min(depth + qrs[ed].dist, n), 1, n, 1, -qrs[ed].inc);
		ed--;
	}
}

void dfs_0(int v, int prev) {
	dfsord[v] = k++;
	for (auto nextv : graph[v]) {
		if (nextv != prev) {
			dfs_0(nextv, v);
		}
	}
}


ll query(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return 0;
	if (tree[index].lazy) {
		tree[index].value += ((ll) (r - l + 1)) * tree[index].lazy;
		if (l != r) {
			tree[index * 2].lazy += tree[index].lazy;
			tree[index * 2 + 1].lazy += tree[index].lazy; 
		}
		tree[index].lazy = 0;
	}
	if (start > r || l > end) return 0;
	if (start <= l && r <= end) return tree[index].value;
	int mid = l + (r - l) / 2;
	return query(start, end, l, mid, index * 2) + query(start, end, mid + 1, r, index * 2 + 1);
}

void update(int start, int end, int l, int r, int index, ll v) {
	if (start > end || l > r) return;
	if (tree[index].lazy) {
		tree[index].value += ((ll) (r - l + 1)) * tree[index].lazy;
		if (l != r) {
			tree[index * 2].lazy += tree[index].lazy;
			tree[index * 2 + 1].lazy += tree[index].lazy; 
		}
		tree[index].lazy = 0;
	}
	if (start > r || l > end) return;
	if (start <= l && r <= end) {
		tree[index].value += ((ll) (r - l + 1)) * v;
		if (l != r) {
			tree[index * 2].lazy += v;
			tree[index * 2 + 1].lazy += v;
		}
		return;
	}
	
	int mid = l + (r - l) / 2;
	update(start, end, l, mid, index * 2, v);
	update(start, end, mid + 1, r, index * 2 + 1, v);
	tree[index].value = tree[index * 2].value + tree[index * 2 + 1].value;
}
