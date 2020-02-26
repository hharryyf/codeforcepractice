#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 524292
typedef long long ll;
using namespace std;

struct segt {
	   int left, right;
	   int rsum;
};

segt tree[MAX_SIZE * 28];
int root[MAX_SIZE >> 1];
int cnt = 0;
int n;
int build(int l, int r) {
	 if (l > r) return 0;
	 int curr = ++cnt;
	 if (l == r) return curr;
	 int mid = l + (r - l) / 2;
	 tree[curr].left = build(l, mid);
	 tree[curr].right = build(mid + 1, r);
	 return curr;
}

int update(int rt, int pos, int l, int r, int val) {
	if (rt == 0 || l > r || pos < l || pos > r) return rt;
	int curr = ++cnt;
	tree[curr] = tree[rt];
	if (pos == l && l == r) {
	   tree[curr].rsum = val;
	   return curr;
	}
	
	int mid = l + (r - l) / 2;
	if (pos <= mid) {
	   tree[curr].left = update(tree[rt].left, pos, l, mid, val);
	} else {
	   tree[curr].right = update(tree[rt].right, pos, mid + 1, r, val);
	}
	
	tree[curr].rsum = tree[tree[curr].left].rsum + tree[tree[curr].right].rsum;
	return curr;
}

int getans(int rt, int start, int end, int l, int r) {
	if (start > end || l > r || rt == 0 || start > r || l > end) return 0;
	if (start <= l && r <= end) return tree[rt].rsum;
	int mid = l + (r - l) / 2;
	if (end <= mid) return getans(tree[rt].left, start, end, l, mid);
	if (start >= mid + 1) return getans(tree[rt].right, start, end, mid + 1, r);
	return getans(tree[rt].left, start, end, l, mid) + getans(tree[rt].right, start, end, mid + 1, r);
}

int query(int l, int r, int d, int u) {
	int ret = getans(root[r], d, u, 1, n) - 
          (l >= 1 ? getans(root[l-1], d, u, 1, n) : 0);
    // cout << ret << endl;
    return ret;
}

int main() {
	int q, i;
	scanf("%d%d", &n, &q);
	root[0] = build(1, n);
	for (i = 1; i <= n; i++) {
		int v;
		scanf("%d", &v);
		root[i] = update(root[i-1], v, 1, n, 1);
	}
	
	while (q > 0) {
		  ll ans = 0;
		  int l, d, r, u;
		  scanf("%d%d%d%d", &l, &d, &r, &u);
		  int v1 = query(1, l-1, u+1, n);
		  int v2 = query(l, r, u+1, n);
		  int v3 = query(r+1, n, u+1, n);
		  int v4 = query(1, l-1, d, u);
		  int v5 = query(l, r, d, u);
		  int v6 = query(r+1, n, d, u);
		  int v7 = query(1, l-1, 1, d-1);
		  int v8 = query(l, r, 1, d-1);
		  int v9 = query(r+1, n, 1, d-1);
		  ans += 1ll * v9 * (v1 + v2 + v4 + v5);
		  ans += 1ll * v6 * (v1 + v2 + v4 + v5 + v7 + v8);
		  ans += 1ll * v3 * (v4 + v5 + v7 + v8);
		  ans += 1ll * v2 * (v4 + v7);
		  ans += 1ll * v8 * (v1 + v4);
		  ans += 1ll * v5 * (v1 + v4 + v7);
		  ans += 1ll * v2 * v5 + 1ll * v2 * v8 + 1ll * v5 * v8;
		  ans += 1ll * v5 * (v5-1) / 2;
		  printf("%lld\n", ans);
		  q--;
	}
	return 0;
}
