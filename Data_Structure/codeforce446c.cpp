#include <bits/stdc++.h>
#pragma GCC optimize(3)
#define MAX_SIZE 300011
#define MOD 1000000009
#define LEFT (index << 1)
#define RIGHT (index << 1 | 1)
typedef long long ll;
using namespace std;

/*
	Two properties are used in this problem
	F[n] = first * Fib[n-2] + second * Fib[n-1]
	S[n] = F[n+2] - second
*/

struct segt {
	// range sum
	ll rsum;
	// range first, second increment value
	ll lz1, lz2;
};

ll fib[MAX_SIZE];
int a[MAX_SIZE];
segt tree[MAX_SIZE << 2];

ll add(ll v1, ll v2) {
	return ((v1 + v2) % MOD + MOD) % MOD;
}

ll getn(ll first, ll second, int x) {
	if (x == 1) return first;
	if (x == 2) return second;
	return add(first * fib[x-2], second * fib[x-1]);
}

void pushdown(int l, int r, int index) {
	if (l > r) return;
	if (tree[index].lz1 || tree[index].lz2) {
		int mid = (l + r) >> 1;
		int len1 = mid - l + 1;
		int len2 = r - mid;
		if (l != r) {
			tree[LEFT].lz1 = add(tree[LEFT].lz1, tree[index].lz1);
			tree[LEFT].lz2 = add(tree[LEFT].lz2, tree[index].lz2);
			ll delta = getn(tree[index].lz1, tree[index].lz2, len1 + 2) - tree[index].lz2;
			tree[LEFT].rsum = add(tree[LEFT].rsum, delta);
			ll v1 = getn(tree[index].lz1, tree[index].lz2, len1 + 1);
			ll v2 = getn(tree[index].lz1, tree[index].lz2, len1 + 2);
			tree[RIGHT].lz1 = add(tree[RIGHT].lz1, v1);
			tree[RIGHT].lz2 = add(tree[RIGHT].lz2, v2);
			delta = getn(v1, v2, len2 + 2) - v2;
			tree[RIGHT].rsum = add(tree[RIGHT].rsum, delta);
		} 
		
		tree[index].lz1 = tree[index].lz2 = 0;
		// cout << l << " " << r << " = " << tree[index].rsum << endl;
	}
}

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index].rsum = a[l];
		return;
	}
	
	int mid = (l + r) >> 1;
	build(l, mid, LEFT);
	build(mid + 1, r, RIGHT);
	tree[index].rsum = add(tree[LEFT].rsum, tree[RIGHT].rsum);
}

void update(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return;
	pushdown(l, r, index);
	if (start > r || l > end) return;
	if (start <= l && r <= end) {
		// TODO
		tree[index].lz1 = fib[l - start + 1];
		tree[index].lz2 = fib[l - start + 2];
		ll delta = getn(tree[index].lz1, tree[index].lz2, r - l + 3);
		tree[index].rsum = add(tree[index].rsum, delta - tree[index].lz2);
		return;
	}
	
	int mid = (l + r) >> 1;
	if (end <= mid) {
		update(start, end, l, mid, LEFT);
	} else if (start >= mid + 1) {
		update(start, end, mid + 1, r, RIGHT);
	} else {
		update(start, end, l, mid, LEFT);
		update(start, end, mid + 1, r, RIGHT);
	}
	tree[index].rsum = add(tree[LEFT].rsum, tree[RIGHT].rsum);
}

ll query(int start, int end, int l, int r, int index) {
	if (start > end || l > r || start > r || l > end) return 0;
	pushdown(l, r, index);
	if (start <= l && r <= end) {
		// cout << l << " " << r << " -> " << tree[index].rsum << endl;
		return tree[index].rsum;
	}
	int mid = (l + r) >> 1;
	if (end <= mid) {
		return query(start, end, l, mid, LEFT);
	}
	
	if (start >= mid + 1) {
		return query(start, end, mid + 1, r, RIGHT);
	}
	
	return add(query(start, end, l, mid, LEFT), query(start, end, mid + 1, r, RIGHT));
}

int main() {
	int n, i, q;
	scanf("%d%d", &n, &q);
	for (i = 1; i <= n; ++i) scanf("%d", &a[i]);
	
	fib[1] = fib[2] = 1;
	for (i = 3; i < MAX_SIZE; ++i) fib[i] = add(fib[i-1], fib[i-2]);
	
	build(1, n, 1);
	
	while (q > 0) {
		int tp, l, r;
		scanf("%d%d%d", &tp, &l, &r);
		if (tp == 1) {
			update(l, r, 1, n, 1);
		} else {
			printf("%I64d\n", query(l, r, 1, n, 1));
		}
		q--;
	}
	return 0;
}