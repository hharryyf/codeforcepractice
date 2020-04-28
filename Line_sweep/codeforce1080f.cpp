#include <bits/stdc++.h>
#define MAX_SIZE 262192
#define MID ((l+r)>>1)
using namespace std;

struct segt {
	int left, right, rmin;
};

struct interval {
	int l, r, id;
	bool operator < (interval other) const {
		if (r != other.r) return r < other.r;
		return l < other.l;
	}
};

int n, k, q;
segt tree[MAX_SIZE * 40];
int root[MAX_SIZE << 1];
int cnt = 0;
vector<int> disc;
interval itv[MAX_SIZE << 1];

int build(int l, int r) {
	int curr = ++cnt;
	if (l > r) return curr;
	if (l == r) return curr;
	tree[curr].left = build(l, MID);
	tree[curr].right = build(MID + 1, r);
	return curr;
}

int update(int rt, int pos, int l, int r, int val) {
	if (rt == 0 || pos < l || pos > r || l > r) return rt;
	int curr = ++cnt;
	tree[curr] = tree[rt];
	if (pos == l && r == pos) {
		tree[curr].rmin = max(tree[curr].rmin, val);
		return curr;
	}
	
	if (pos <= MID) {
		tree[curr].left = update(tree[rt].left, pos, l, MID, val);
	} else {
		tree[curr].right = update(tree[rt].right, pos, MID + 1, r, val);
	}
	tree[curr].rmin = min(tree[tree[curr].left].rmin, tree[tree[curr].right].rmin);
	return curr;
}

int query(int rt, int start, int end, int l, int r) {
	if (start > end || l > r || start > r || l > end) return 1000000001;
	if (start <= l && r <= end) return tree[rt].rmin;
	if (end <= MID) {
		return query(tree[rt].left, start, end, l, MID);
	}
	
	if (start >= MID + 1) {
		return query(tree[rt].right, start, end, MID + 1, r);
	}
	return min(query(tree[rt].left, start, end, l, MID), 
	           query(tree[rt].right, start, end, MID + 1, r));
}

int main() {
	int i;
	scanf("%d%d%d", &n, &q, &k);
	root[0] = build(1, n);
	for (i = 1; i <= k; ++i) {
		scanf("%d%d%d", &itv[i].l, &itv[i].r, &itv[i].id);
	}
	
	sort(itv + 1, itv + 1 + k);
	
	for (i = 1; i <= k; ++i) {
		root[i] = update(root[i-1], itv[i].id, 1, n, itv[i].l);
		disc.push_back(itv[i].r);
	}
	
	while (q > 0) {
		int l, r, x, y;
		scanf("%d%d%d%d", &l, &r, &x, &y);
		int vs = upper_bound(disc.begin(), disc.end(), y) - disc.begin();
		int v = query(root[vs], l, r, 1, n);
		printf("%s\n", v >= x ? "yes" : "no");
		fflush(stdout);
		--q;
	} 
	return 0;
}