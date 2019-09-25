#include <bits/stdc++.h>
#define MAX_SIZE 262192
#define MOD 1000000007

typedef long long ll;
using namespace std;

struct segt {
	int len;
	ll first, second;
	ll lz1, lz2;
};

segt tree[MAX_SIZE];
ll x[MAX_SIZE >> 1];
int n, q;
ll fib[MAX_SIZE >> 1][2][2];
ll a, b;

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index].first = tree[index].second = tree[index].lz1 = tree[index].lz2 = 0;
		tree[index].len = 1;
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	tree[index].len = tree[index * 2].len + tree[index * 2 + 1].len;
}

void prepro() {
	fib[0][0][0] = b;
	fib[0][0][1] = a;
	fib[0][1][0] = 1;
	fib[0][1][1] = 0;
	fib[1][0][0] = b;
	fib[1][0][1] = a;
	fib[1][1][0] = 1;
	fib[1][1][1] = 0;
	int i;
	for (i = 2; i <= n + 1; i++) {
		fib[i][0][0] = (fib[i-1][0][0] * b + fib[i-1][0][1]) % MOD;
		fib[i][0][1] = (fib[i-1][0][0] * a) % MOD;
		fib[i][1][0] = (fib[i-1][1][0] * b + fib[i-1][1][1]) % MOD;
		fib[i][1][1] = (fib[i-1][1][0] * a) % MOD;
		// cout << fib[i][0][0] << " " << fib[i][0][1] << endl;
		// cout << fib[i][1][0] << " " << fib[i][1][1] << endl;
		// cout << endl;
	}
}

ll getfirst(ll f, ll s, int x) {
	if (x == 1) return f % MOD;
	if (x == 2) return s % MOD;
	return ((fib[x-2][0][0] * s) % MOD + (fib[x-2][0][1] * f) % MOD) % MOD;
}

void update(int start, int end, int l, int r, int index, ll f1, ll f2) {
	if (start > end || l > r) return;
	if (tree[index].lz1 != 0ll || tree[index].lz2 != 0ll) {
		tree[index].first = (tree[index].lz1 + tree[index].first) % MOD;
		tree[index].second = (tree[index].lz2 + tree[index].second) % MOD;
		if (l != r) {
			tree[index * 2].lz1 = (tree[index * 2].lz1 + tree[index].lz1) % MOD;
			tree[index * 2].lz2 = (tree[index * 2].lz2 + tree[index].lz2) % MOD;
			tree[index * 2 + 1].lz1 = (tree[index * 2 + 1].lz1 + getfirst(tree[index].lz1, tree[index].lz2, tree[index * 2].len + 1)) % MOD;
			tree[index * 2 + 1].lz2 = (tree[index * 2 + 1].lz2 + getfirst(tree[index].lz1, tree[index].lz2, tree[index * 2].len + 2)) % MOD;
			// TODO add code for lazy propagation on index * 2 + 1
		}
		tree[index].lz1 = tree[index].lz2 = 0ll;
	}
	
	if (start > r || l > end) return;
	if (start <= l && r <= end) {
		ll d1 = getfirst(f1, f2, l - start + 1);
		ll d2 = getfirst(f1, f2, l - start + 2);
		tree[index].first = (tree[index].first + d1) % MOD;
		tree[index].second = (tree[index].second + d2) % MOD;
		if (l != r) {
			tree[index * 2].lz1 = (tree[index * 2].lz1 + d1) % MOD;
			tree[index * 2].lz2 = (tree[index * 2].lz2 + d2) % MOD;
			tree[index * 2 + 1].lz1 = (tree[index * 2 + 1].lz1 + getfirst(d1,d2, tree[index * 2].len + 1)) % MOD;
			tree[index * 2 + 1].lz2 = (tree[index * 2 + 1].lz2 + getfirst(d1,d2, tree[index * 2].len + 2)) % MOD;
		}
		return;
	}
	
	int mid = l + (r - l) / 2;
	update(start, end, l, mid, index * 2, f1, f2);
	update(start, end, mid + 1, r, index * 2 + 1, f1, f2);
	tree[index].first = tree[index * 2].first;
	tree[index].second = tree[index * 2].second;
	tree[index].len = tree[index * 2].len + tree[index * 2 + 1].len;
}

ll query(int pt, int l, int r, int index) {
	if (l > r) return 0ll;
	if (tree[index].lz1 != 0ll || tree[index].lz2 != 0ll) {
		tree[index].first = (tree[index].lz1 + tree[index].first) % MOD;
		tree[index].second = (tree[index].lz2 + tree[index].second) % MOD;
		if (l != r) {
			tree[index * 2].lz1 = (tree[index * 2].lz1 + tree[index].lz1) % MOD;
			tree[index * 2].lz2 = (tree[index * 2].lz2 + tree[index].lz2) % MOD;
			tree[index * 2 + 1].lz1 = 
				(tree[index * 2 + 1].lz1 + getfirst(tree[index].lz1, tree[index].lz2, tree[index * 2].len + 1)) % MOD;
			tree[index * 2 + 1].lz2 = 
				(tree[index * 2 + 1].lz2 + getfirst(tree[index].lz1, tree[index].lz2, tree[index * 2].len + 2)) % MOD;
		}
		tree[index].lz1 = tree[index].lz2 = 0ll;
	}
	
	if (l == r && r == pt) return tree[index].first;
	int mid = l + (r - l) / 2;
	if (pt <= mid) {
		return query(pt, l, mid, index * 2);
	}
	
	return query(pt, mid + 1, r, index * 2 + 1);
}

int main() {
	ll f1, f2;
	scanf("%d%d", &n, &q);
	scanf("%lld%lld", &f1, &f2);	
	scanf("%lld%lld", &a, &b);
	prepro();
	build(1, n, 1);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &x[i]);	
	}
	
	while (q > 0) {
		int l, r;
		scanf("%d%d", &l, &r);
		update(l, r, 1, n, 1, f1, f2);
		q--;
	}
	
	for (int i = 1; i <= n; i++) {
		printf("%lld ", (x[i] + query(i, 1, n, 1)) % MOD);
	}
	cout << endl;
	return 0;
}
