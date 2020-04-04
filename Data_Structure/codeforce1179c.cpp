#include <bits/stdc++.h>
#define MAX_SIZE 2097312
#define MID ((l+r)>>1)
#define LEFT (index << 1)
#define RIGHT (index << 1 | 1)
using namespace std;

const int maxn = 1e6;
struct segt {
	int ans;
	int lz;
};

segt tree[MAX_SIZE];

void pushdown(int l, int r, int index) {
	if (l > r) return;
	if (tree[index].lz != 0) {
		if (l != r) {
			tree[LEFT].lz += tree[index].lz;
			tree[RIGHT].lz += tree[index].lz;
			tree[LEFT].ans += tree[index].lz;
			tree[RIGHT].ans += tree[index].lz;
		}
		tree[index].lz = 0;
	}
}

void update(int start, int end, int l, int r, int index, int val) {
	if (start > end || l > r) return;
	pushdown(l, r, index);
	if (start > r || l > end) return;
	if (start <= l && r <= end) {
		tree[index].lz += val;
		tree[index].ans += val;
		return;
	}
	
	if (start >= MID + 1) {
		update(start, end, MID + 1, r, RIGHT, val);
	} else if (end <= MID) {
		update(start, end, l, MID, LEFT, val);
	} else {
		update(start, end, l, MID, LEFT, val);
		update(start, end, MID + 1, r, RIGHT, val);
	}
	
	tree[index].ans = max(tree[LEFT].ans, tree[RIGHT].ans);
}

int query(int l, int r, int index) {
	if (l > r) return 0;
	pushdown(l, r, index);
	if (l == r) {
		return l;
	}
	
	if (tree[RIGHT].ans >= 1) return query(MID + 1, r, RIGHT);
	return query(l, MID, LEFT);
}

int a[MAX_SIZE], b[MAX_SIZE];

int main() {
	int i, n, m;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		update(1, a[i], 1, maxn, 1, 1);
	}
	
	for (i = 1; i <= m; ++i) {
		scanf("%d", &b[i]);
		update(1, b[i], 1, maxn, 1, -1);
	}
	
	int q;
	scanf("%d", &q);
	while (q > 0) {
		int tp, pos, p;
		scanf("%d%d%d", &tp, &pos, &p);
		if (tp == 1) {
			update(1, a[pos], 1, maxn, 1, -1);
			update(1, p, 1, maxn, 1, 1);
			a[pos] = p;
		} else {
			update(1, b[pos], 1, maxn, 1, 1);
			update(1, p, 1, maxn, 1, -1);
			b[pos] = p;
		}
		
		if (tree[1].ans < 1) printf("-1\n");
		else {
			printf("%d\n", query(1, maxn, 1));
		}
		q--;
	}
	return 0;
}