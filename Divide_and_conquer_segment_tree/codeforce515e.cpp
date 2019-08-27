#include <bits/stdc++.h>
#define MAX_LEN 525312


using namespace std;

typedef long long Long;
typedef struct segtree {
	Long leftside;
	Long rightside;
	Long interval;
} SegmentTree;

SegmentTree tree[MAX_LEN];

Long d[MAX_LEN >> 1], h[MAX_LEN >> 1], prefix[MAX_LEN >> 1];

int n, m;

Long dist(int st, int ed);

void build(int l, int r, int index);

SegmentTree query(int start, int end, int l, int r, int index);

int main(int argc, char *argv[]) {
	cin >> n >> m;
	for (int i = 0; i < 2 * n - 2; i++) {
		if (i < n) { 
			scanf("%lld", &d[i]);
		} else {
			d[i] = d[i - n];
		}
		prefix[i] = (i >= 1 ? prefix[i-1] : 0) + d[i];
	}
	
	for (int i = 0; i < 2 * n - 1; i++) {
		if (i < n) {
			scanf("%lld", &h[i]);
		} else {
			h[i] = h[i - n];
		}
	}
	
	build(0, 2 * n - 2, 1);
	
	for (int i = 0 ; i < m; i++) {
		int l, r;
		scanf("%d%d", &l, &r);
		l--;
		r--;
		if (l <= r) {
			cout << query(r + 1, l + n - 1, 0, 2 * n - 2, 1).interval << endl;
		} else {
			cout << query(r + 1, l - 1, 0, 2 * n - 2, 1).interval << endl;
		}
	}
	return 0;
}

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index].leftside = 2 * h[l];
		tree[index].rightside = 2 * h[l];
		tree[index].interval = 2 * h[l];
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	tree[index].leftside = max(tree[index * 2].leftside + dist(mid, r), tree[index * 2 + 1].leftside);
	tree[index].rightside = max(tree[index * 2 + 1].rightside + dist(l, mid + 1), tree[index * 2].rightside);
	tree[index].interval = max(tree[index * 2].interval, tree[index * 2 + 1].interval);
	tree[index].interval = max(tree[index].interval, tree[index * 2].leftside + dist(mid, mid + 1) +  tree[index * 2 + 1].rightside);
}

SegmentTree query(int start, int end, int l, int r, int index) {
	SegmentTree t;
	t.leftside = t.rightside = t.interval = 0;
	if (start > end || l > r) return t;
	if (start > r || end < l) return t;
	if (start <= l && r <= end) return tree[index];
	int mid = l + (r - l) / 2;
	if (end <= mid) {
		return query(start, end, l, mid, index * 2);
	} else if (start >= mid + 1) {
		return query(start, end, mid + 1, r, index * 2 + 1);
	}
	
	SegmentTree t1, t2;
	t1 = query(start, end, l, mid, index * 2);
	t2 = query(start, end, mid + 1, r, index * 2 + 1);
	t.leftside = max(t1.leftside + dist(mid, r), t2.leftside);
	t.rightside = max(t2.rightside + dist(l, mid + 1), t1.rightside);
	t.interval = max(t1.interval, t2.interval);
	t.interval = max(t.interval, t1.leftside + dist(mid, mid + 1) +  t2.rightside);
	return t;
}

Long dist(int st, int ed) {
	if (st >= ed) return 0;
	return prefix[ed - 1] - (st >= 1 ? prefix[st - 1] : 0);
}
