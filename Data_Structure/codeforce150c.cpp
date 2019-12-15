#include <bits/stdc++.h>
#define MAX_LEN 524292

using namespace std;

typedef long long Long;

int n, m, c;

typedef struct segTree {
	Long left;
	Long right;
	Long interval;
	Long tol;
} SegmentTree;

SegmentTree tree[MAX_LEN];

Long x[MAX_LEN >> 1], p[MAX_LEN >> 1];;

void build(int l, int r, int index);

SegmentTree query(int start, int end, int l, int r, int index);

int main(int argc, char *argv[]) {
	scanf("%d%d%d", &n, &m, &c);
	for (int i = 0 ; i < n; i++) {
		scanf("%lld", &x[i]);
	}
	
	for (int i = 0 ; i < n - 1; i++) {
		scanf("%lld", &p[i]);
		x[i] = 50 * (x[i+1] - x[i]) - p[i] * c;
	}	
	
	build(0, n - 2, 1);
	
	Long ans = 0;
	
	for (int i = 0 ; i < m; i++) {
		int l, r;
		scanf("%d%d", &l, &r);
		ans += max(0ll, query(l - 1, r - 2, 0, n - 2, 1).interval);	
	}
	
	printf("%lf\n", ans * 0.01);
	return 0;
}

SegmentTree mergeInterval(SegmentTree t1, SegmentTree t2) {
	SegmentTree t;
	t.left = max(t1.left, t2.left + t1.tol);
	t.right = max(t2.right, t1.right + t2.tol);
	t.tol = t1.tol + t2.tol;
	t.interval = max(t1.right + t2.left, max(t1.interval, t2.interval));
	t.interval = max(t.interval, max(t.left, t.right));
	return t;
}

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index].left = tree[index].right = tree[index].interval = tree[index].tol = x[l];
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	tree[index] = mergeInterval(tree[index * 2], tree[index * 2 + 1]);
}

SegmentTree query(int start, int end, int l, int r, int index) {
	SegmentTree t;
	t.left = t.right = t.interval = t.tol = 0;
	if (start > end || l > r) {
		return t;
	}
	
	if (start > r || end < l) return t;
	if (start <= l && r <= end) return tree[index];
	int mid = l + (r - l) / 2;
	if (end <= mid) {
		return query(start, end, l, mid, index * 2);
	} else if (start >= mid + 1) {
		return query(start, end, mid + 1, r, index * 2 + 1);
	}
	
	SegmentTree t1 = query(start, end, l, mid, index * 2);
	SegmentTree t2 = query(start, end, mid + 1, r, index * 2 + 1);
	t = mergeInterval(t1, t2);
	return t;
}
