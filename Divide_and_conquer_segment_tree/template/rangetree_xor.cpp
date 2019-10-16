#include <bits/stdc++.h>
#define MAX_SIZE 524292

using namespace std;

vector<int> g[MAX_SIZE >> 1];

struct segt {
	int value, lz;
};

segt tree[MAX_SIZE];

int subsize[MAX_SIZE], dfsord[MAX_SIZE];
int rmap[MAX_SIZE];

int arr[MAX_SIZE];
int n;
int k = 1;
char st[8];

void dfs(int v) {
	subsize[v] = 1;
	dfsord[v] = k++;
	rmap[dfsord[v]] = v;
	for (auto nextv : g[v]) {
		dfs(nextv);
		subsize[v] = subsize[v] + subsize[nextv];
	}
}

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index].value = arr[rmap[l]];
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	tree[index].value = tree[index * 2].value + tree[index * 2 + 1].value;
}

void pushdown(int l, int r, int index) {
	int mid = l + (r - l) / 2;
	if (tree[index].lz) {
		if (l != r) {
			int len1 = mid - l + 1, len2 = r - mid;
			tree[index * 2].value = len1 - tree[index * 2].value;
			tree[index * 2 + 1].value = len2 - tree[index * 2 + 1].value;
			tree[index * 2].lz = 1 - tree[index * 2].lz;
			tree[index * 2 + 1].lz = 1 - tree[index * 2 + 1].lz;
		}
	
		tree[index].lz = 0;
	}
}

int query(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return 0;
	pushdown(l, r, index);
	if (start > r || l > end) return 0;
	if (start <= l && r <= end) {
		return tree[index].value;
	}
	
	int mid = l + (r - l) / 2;
	if (end <= mid) return query(start, end, l, mid, index * 2);
	if (start >= mid + 1) return query(start, end, mid + 1, r, index * 2 + 1);
	return query(start, end, l, mid, index * 2) + query(start, end, mid + 1, r, index * 2 + 1);
}

void update(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return;
	pushdown(l, r, index);
	if (start > r || l > end) return;
	if (start <= l && r <= end) {
		tree[index].value = (r - l + 1) - tree[index].value;
		tree[index].lz = 1;
		return;
	}
	
	int mid = l + (r - l) / 2;
	if (end <= mid) {
		update(start, end, l, mid, index * 2);
	} else if (start >= mid + 1) {
		update(start, end, mid + 1, r, index * 2 + 1);
	} else {
		update(start, end, l, mid, index * 2);
		update(start, end, mid + 1, r, index * 2 + 1);
	}
	
	tree[index].value = tree[index * 2].value + tree[index * 2 + 1].value;
}

int main() {
	scanf("%d", &n);
	int i, q;
	for (i = 2 ; i <= n; i++) {
		int v;
		scanf("%d", &v);
		g[v].push_back(i);
	}
	
	dfs(1);
	for (i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
	}
	
	build(1, n, 1);
	
	scanf("%d", &q);
	while (q > 0) {
		int v;
		scanf("%s%d", st, &v);
		if (st[0] == 'g') {
			printf("%d\n", query(dfsord[v], dfsord[v] + subsize[v] - 1, 1, n, 1));
		} else {
			update(dfsord[v], dfsord[v] + subsize[v] - 1, 1, n, 1);
		}
		q--;
	}
	return 0;
}
