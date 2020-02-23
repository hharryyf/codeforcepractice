#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 1100002
typedef long long ll;
using namespace std;

struct segt {
	   int left, right;
	   int value;
};

int root[MAX_SIZE];
segt tree[MAX_SIZE * 25];
int cnt = 0;
int a[MAX_SIZE], b[MAX_SIZE];
int build(int l, int r) {
	 if (l > r) return 0;	 
	 int curr = ++cnt;
	 if (l == r) {
	 	return curr;
	 }
	 int mid = l + (r - l) / 2;
	 tree[curr].left = build(l, mid);
	 tree[curr].right = build(mid + 1, r);
	 return curr;
}

int update(int rt, int pos, int l, int r, int val) {
	if (!rt || pos < l || pos > r || l > r) return rt;
	int curr = ++cnt;
	tree[curr] = tree[rt];
	if (l == r) {
	   tree[curr].value += val;
	   return curr;
	}
	
	int mid = l + (r - l) / 2;
	if (pos <= mid) {
	   tree[curr].left = update(tree[rt].left, pos, l, mid, val);
	} else {
	   tree[curr].right = update(tree[rt].right, pos, mid + 1, r, val);
	}
	tree[curr].value = tree[tree[curr].left].value + tree[tree[curr].right].value;
	return curr;
}

int query(int rt, int start, int end, int l, int r) {
	if (!rt || start > end || l > r || start > r || l > end) return 0;
	if (start <= l && r <= end) return tree[rt].value;
	int mid = l + (r - l) / 2;
	if (end <= mid) return query(tree[rt].left, start, end, l, mid);
	if (start >= mid + 1) return query(tree[rt].right, start, end, mid + 1, r);
	return query(tree[rt].left, start, end, l, mid) + query(tree[rt].right, start, end, mid + 1, r);
}

int decode(int x, int ret, int n) {
	return ((x + ret - 1) % n) + 1;
}

int main() {
	int i, n;
	scanf("%d", &n);
	root[0] = build(1, n);
	for (i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (i = 1; i <= n; i++) {
		int v;
		scanf("%d", &v);
		b[v] = i;
	}
	
	for (i = 1; i <= n; i++) {
		root[i] = update(root[i-1], b[a[i]], 1, n, 1);
	}
	
	int q, lst = 0;
	scanf("%d", &q);
	while (q > 0) {
		  int l1, r1, l2, r2;
		  scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
 	  	  l1 = decode(l1, lst, n);
 	  	  r1 = decode(r1, lst, n);
 	  	  l2 = decode(l2, lst, n);
 	  	  r2 = decode(r2, lst, n);
 	  	  if (l1 > r1) swap(l1, r1);
 	  	  if (l2 > r2) swap(l2, r2);
 	  	  lst = query(root[r1], l2, r2, 1, n) - query(root[l1-1], l2, r2, 1, n);
 	  	  printf("%d\n", lst++);
 	  	  q--;
	}
	return 0;
}
