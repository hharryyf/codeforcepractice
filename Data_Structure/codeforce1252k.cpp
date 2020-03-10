#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 262192
typedef long long ll;
using namespace std;

struct Matrix {
	ll a[2][2];
	Matrix operator *(Matrix other) const {
		Matrix ret;
		ret.a[0][0] = ret.a[0][1] = ret.a[1][0] = ret.a[1][1] = 0;
		int i, j, k;
		for (i = 0 ; i < 2; ++i) {
			for (j = 0 ; j < 2; ++j) {
				for (k = 0 ; k < 2; ++k) {
					ret.a[i][j] += a[i][k] * other.a[k][j];
					ret.a[i][j] %= MOD;
				}
			}
		}
		return ret;
	}
};

Matrix A;
Matrix B;

struct segt {
	// ans means the answer to the current range
	// ivt means the invertion of the current range
	// when an update occurs, we swap ans and ivt
	// and set lz = 1
	Matrix ans, ivt;
	int lz;
};

segt tree[MAX_SIZE];
char st[MAX_SIZE];

void pushdown(int l, int r, int index) {
	if (l > r) return;
	if (tree[index].lz) {
		if (l != r) {
			swap(tree[index * 2].ans, tree[index * 2].ivt);
			swap(tree[index * 2 + 1].ans, tree[index * 2 + 1].ivt);
			tree[index * 2].lz ^= 1;
			tree[index * 2 + 1].lz ^= 1;
		}
		tree[index].lz = 0;
	}
}
// be very careful on this, because matrix multiplication
// is not commutitive
segt pullup(segt t1, segt t2) {
	segt t;
	t.lz = 0;
	t.ans = t2.ans * t1.ans;
	t.ivt = t2.ivt * t1.ivt;
	return t;
}

void update(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return;
	pushdown(l, r, index);
	if (start <= l && r <= end) {
		swap(tree[index].ans, tree[index].ivt);
		tree[index].lz = 1;
		return;
	}
	
	int mid = (l + r) >> 1;
	if (end <= mid) {
		update(start, end, l, mid, index * 2);
	} else if (start >= mid + 1) {
		update(start, end, mid + 1, r, index * 2 + 1);
	} else {
		update(start, end, l, mid, index * 2);
		update(start, end, mid + 1, r, index * 2 + 1);
	}
	tree[index] = pullup(tree[index * 2], tree[index * 2 + 1]);
}

segt query(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return tree[0];
	pushdown(l, r, index);
	if (start <= l && r <= end) return tree[index];
	int mid = (l + r) >> 1;
	if (end <= mid) return query(start, end, l, mid, index * 2);
	if (start >= mid + 1) return query(start, end, mid + 1, r, index * 2 + 1);
	return pullup(query(start, end, l, mid, index * 2), query(start, end, mid + 1, r, index * 2 + 1));
}

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		if (st[l] == 'A') {
			tree[index].ans = A;
			tree[index].ivt = B;
		} else {
			tree[index].ans = B;
			tree[index].ivt = A;
		}
		return;
	}
	
	int mid = (l + r) >> 1;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	tree[index] = pullup(tree[index * 2], tree[index * 2 + 1]);
}

int main() {
	int n, q;
	scanf("%d%d", &n, &q);
	A.a[0][0] = 1, A.a[0][1] = 1, A.a[1][0] = 0, A.a[1][1] = 1;
	B.a[0][0] = 1, B.a[0][1] = 0, B.a[1][0] = 1, B.a[1][1] = 1;
	scanf("%s", st + 1);
	build(1, n, 1);
	while (q > 0) {
		int tp, l, r;
		scanf("%d%d%d", &tp, &l, &r);
		if (tp == 1) {
			update(l, r, 1, n, 1);
		} else {
			ll a, b;
			scanf("%I64d%I64d", &a, &b);
			Matrix ret = query(l, r, 1, n, 1).ans;
			printf("%I64d %I64d\n", (ret.a[0][0] * a + ret.a[0][1] * b) % MOD, (ret.a[1][0] * a + ret.a[1][1] * b) % MOD);
		}
		q--;
	}
	return 0;
}