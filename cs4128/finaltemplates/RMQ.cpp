#include <bits/stdc++.h>
#define MAX_SIZE 524292
#define INF 1000000000000000ll
typedef long long ll;

using namespace std;

struct segt {
	ll value, lz;	
};

segt tree[MAX_SIZE];

ll arr[MAX_SIZE >> 1];

int n;

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index].value = arr[l];
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	tree[index].value = min(tree[index * 2].value, tree[index * 2 + 1].value);
}

void pushdown(int l, int r, int index) {
	if (l > r) return;
	if (tree[index].lz) {
		if (l != r) {
			tree[index * 2].value += tree[index].lz;
			tree[index * 2].lz += tree[index].lz;
			tree[index * 2 + 1].value += tree[index].lz;
			tree[index * 2 + 1].lz += tree[index].lz;
		}
		tree[index].lz = 0;
	}
}

ll query(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return -INF;
	pushdown(l, r, index);
	if (start > r || l > end) return -INF;
	if (start <= l && r <= end) {
		return tree[index].value;
	}
	
	int mid = l + (r - l) / 2;
	if (end <= mid) {
		return query(start, end, l, mid, index * 2);
	}
	
	if (start >= mid + 1) {
		return query(start, end, mid + 1, r, index * 2 + 1);
	}
	
	return min(query(start, end, l, mid, index * 2), query(start, end, mid + 1, r, index * 2 + 1));
}

void update(int start, int end, int l, int r, int index, ll val) {
	if (start > end || l > r) return;
	pushdown(l, r, index);
	if (start > r || l > end) return;
	if (start <= l && r <= end) {
		tree[index].value += val;
		tree[index].lz += val;
		return;
	}
	
	int mid = l + (r - l) / 2;
	if (end <= mid) {
		update(start, end, l, mid, index * 2, val);
	} else if (start >= mid + 1) {
		update(start, end, mid + 1, r, index * 2 + 1, val);
	} else {
		update(start, end, l, mid, index * 2, val);
		update(start, end, mid + 1, r, index * 2 + 1, val);
	}
	
	tree[index].value = min(tree[index * 2].value, tree[index * 2 + 1].value);
	
}
