#include <bits/stdc++.h>
#define MAX_SIZE (262144 + 11)

typedef long long ll;

using namespace std;

typedef struct segt {
	ll rmax;
	ll rsum;
} segmenttree;

segmenttree tree[MAX_SIZE];
ll arr[MAX_SIZE >> 1];

void build(int l, int r, int index);
void update(int pt, int l, int r, int index, ll v);
segmenttree query(int start, int end, int l, int r, int index);
void modupdate(int start, int end, int l, int r, int index, ll x);

int main(int argc, char *argv[]) {
	int n, m, i;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n; i++) {
		scanf("%lld", &arr[i]);
	}
	
	build(1, n, 1);
	
	while (m > 0) {
		int t, l, r, k;
		ll v, x;
		scanf("%d", &t);
		if (t == 1) {
			scanf("%d%d", &l, &r);
			printf("%lld\n", query(l, r, 1, n, 1).rsum);
		} else if (t == 2) {
			scanf("%d%d%lld", &l, &r, &x);
			if (query(l, r, 1, n, 1).rmax >= x) {
				modupdate(l, r, 1, n, 1, x);
			} 
		} else {
			scanf("%d%lld", &k, &v);
			update(k, 1, n, 1, v);
		}
		m--;
	}
	return 0;
}

void modupdate(int start, int end, int l, int r, int index, ll x) {
	if (start > end || l > r || start > r || l > end || tree[index].rmax < x) return;
	if (start <= l && r <= end && l == r) {
		tree[index].rmax = tree[index].rmax % x;
		tree[index].rsum = tree[index].rsum % x;
		return;
	}
	
	int mid = l + (r - l) / 2;
	modupdate(start, end, l, mid, index * 2, x);
	modupdate(start, end, mid + 1, r, index * 2 + 1, x);
	tree[index].rmax = max(tree[index * 2].rmax, tree[index * 2 + 1].rmax);
	tree[index].rsum = tree[index * 2].rsum + tree[index * 2 + 1].rsum;
}

segmenttree query(int start, int end, int l, int r, int index) {
	segmenttree t = {0ll,0ll};
	if (start > end || l > r || start > r || l > end) return t;
	if (start <= l && r <= end) return tree[index];
	int mid = l + (r - l) / 2;
	segmenttree t1 = query(start, end, l, mid, index * 2);
	segmenttree t2 = query(start, end, mid + 1, r, index * 2 + 1);
	t.rsum = t1.rsum + t2.rsum;
	t.rmax = max(t1.rmax, t2.rmax);
	return t;
}

void update(int pt, int l, int r, int index, ll v) {
	if (l > r) return;
	if (l == r && r == pt) {
		tree[index].rmax = tree[index].rsum = v;
		return;
	}
	
	int mid = l + (r - l) / 2;
	if (pt <= mid) {
		update(pt, l, mid, index * 2, v);
	} else {
		update(pt, mid + 1, r, index * 2 + 1, v);
	}
	
	tree[index].rmax = max(tree[index * 2].rmax, tree[index * 2 + 1].rmax);
	tree[index].rsum = tree[index * 2].rsum + tree[index * 2 + 1].rsum;
}


void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index].rmax = tree[index].rsum = arr[l];
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	tree[index].rmax = max(tree[index * 2].rmax, tree[index * 2 + 1].rmax);
	tree[index].rsum = tree[index * 2].rsum + tree[index * 2 + 1].rsum;
}



