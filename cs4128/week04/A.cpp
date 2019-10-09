#include <bits/stdc++.h>
#define MAX_SIZE 262192

using namespace std;

struct segt {
	int d[3];
	int lz;
};

segt tree[MAX_SIZE];
int n, q;

void pullup(int index) {
	for (int i = 0; i < 3; i++) tree[index].d[i] = tree[index * 2].d[i] + tree[index * 2 + 1].d[i];
}

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index].d[2] = tree[index].d[1] = 0;
		tree[index].d[0] = 1;
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	pullup(index);
}

void pushdown(int l, int r, int index) {
	if (tree[index].lz != 0) {
		int val = tree[index].lz % 3;
		int d0 = tree[index].d[0];
		int d1 = tree[index].d[1];
		int d2 = tree[index].d[2];
		if (val == 1) {
			tree[index].d[1] = d0;
			tree[index].d[2] = d1;
			tree[index].d[0] = d2;
		} else if (val == 2) {
			tree[index].d[2] = d0;
			tree[index].d[0] = d1;
			tree[index].d[1] = d2;
		}
		if (l != r) {
			tree[index * 2].lz += tree[index].lz;
			tree[index * 2 + 1].lz += tree[index].lz;	
		}
		tree[index].lz = 0;
	}
}

void update(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return;
	pushdown(l, r, index);
	if (start > r || l > end) return;
	if (start <= l && r <= end) {
		int d0 = tree[index].d[0];
		int d1 = tree[index].d[1];
		int d2 = tree[index].d[2];
		tree[index].d[1] = d0;
		tree[index].d[2] = d1;
		tree[index].d[0] = d2;
		if (l != r) {
			tree[index * 2].lz += 1;
			tree[index * 2 + 1].lz += 1;
		}
		return;
	}
	
	int mid = l + (r - l) / 2;
	update(start, end, l, mid, index * 2);
	update(start, end, mid + 1, r, index * 2 + 1);
	pullup(index);
}

int query(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return 0;
	pushdown(l, r, index);
	if (start > r || l > end) return 0;
	if (start <= l && r <= end) return tree[index].d[0];
	int mid = l + (r - l) / 2;
	return query(start, end, l, mid, index * 2) 
		 + query(start, end, mid + 1, r, index * 2 + 1);
}

int main() {
	scanf("%d%d", &n, &q);
	build(0, n - 1, 1);	
	while (q > 0) {
		int v1, v2, v3;
		scanf("%d%d%d", &v1, &v2, &v3);
		if (v1 == 0) {
			update(v2, v3, 0, n - 1, 1);
		} else {
			printf("%d\n", query(v2, v3, 0, n - 1, 1));
		}
		q--;
	}
	return 0;
}
