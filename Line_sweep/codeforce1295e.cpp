#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 524292
typedef long long ll;
using namespace std;

struct segt {
	ll value, lz;
};

segt tree[MAX_SIZE];
// cost of the ith element
ll a[MAX_SIZE];
// the permutation 
int p[MAX_SIZE];
// prefix sum array of a
ll prefix[MAX_SIZE];

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index].value = prefix[l];
		return;
	}
	
	int mid = (l + r) >> 1;
	build(l, mid, index << 1);
	build(mid + 1, r, index << 1 | 1);
	tree[index].value = min(tree[index << 1].value, tree[index << 1 | 1].value);
}

void pushdown(int l, int r, int index) {
	if (l > r || !tree[index].lz) return;
	if (l != r) {
		tree[index << 1].value += tree[index].lz;
		tree[index << 1 | 1].value += tree[index].lz;
		tree[index << 1].lz += tree[index].lz;
		tree[index << 1 | 1].lz += tree[index].lz;
	}
	tree[index].lz = 0;
}

// +v to range
void update(int start, int end, int l, int r, int index, ll v) {
	if (start > end || l > r) return;
	pushdown(l, r, index);
	if (start > r || l > end) return;
	if (start <= l && r <= end) {
		tree[index].value += v;
		tree[index].lz += v;
		return;
	}
	
	int mid = (l + r) >> 1;
	if (end <= mid) {
		update(start, end, l, mid, index << 1, v);
	} else if (start >= mid + 1) {
		update(start, end, mid + 1, r, index << 1 | 1, v);
	} else {
		update(start, end, l, mid, index << 1, v);
		update(start, end, mid + 1, r, index << 1 | 1, v);
	}
	tree[index].value = min(tree[index << 1].value, tree[index << 1 | 1].value);
}


int main() {
	int i, n;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) scanf("%d", &p[i]);
	for (i = 1; i <= n; ++i) {
		ll v;
		scanf("%I64d", &v);
		a[p[i]] = v;
		prefix[p[i]] = v;
	}
	
	for (i = 1; i <= n; ++i) {
		prefix[i] += prefix[i-1];
	}
	
	build(1, n, 1);
	
	ll ans = a[p[1]];
	
	for (i = 1; i < n; ++i) {
		update(p[i], n, 1, n, 1, -a[p[i]]);
		update(1, p[i] - 1, 1, n, 1, a[p[i]]);
		ans = min(ans, tree[1].value);
	}
	
	printf("%I64d\n", ans);
	return 0;
}