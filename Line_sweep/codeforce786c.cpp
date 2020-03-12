#include <bits/stdc++.h>
#define MAX_SIZE 262192
using namespace std;

struct segt {
	int left, right, value;
};

segt tree[MAX_SIZE * 35];
int root[MAX_SIZE];
// id[i] refers to the actual root index of the query with
// a left bound i
int id[MAX_SIZE];
int nxt[MAX_SIZE];
int a[MAX_SIZE];
int cnt;

int build(int l, int r) {
	if (l > r) return 0;
	int curr = ++cnt;
	if (l == r) {
		return curr;
	}
	int mid = (l + r) >> 1;
	tree[curr].left = build(l, mid);
	tree[curr].right = build(mid + 1, r);
	return curr;
}

// set pos the tree with rt to val
int update(int rt, int pos, int l, int r, int val) {
	if (pos < l || pos > r || l > r || rt == 0) return rt;
	int curr = ++cnt;
	tree[curr] = tree[rt];
	if (l == r) {
		tree[curr].value = val;
		return curr;
	}
	
	int mid = (l + r) >> 1;
	if (pos <= mid) {
		tree[curr].left = update(tree[rt].left, pos, l, mid, val);
	} else {
		tree[curr].right = update(tree[rt].right, pos, mid + 1, r, val);
	}
	tree[curr].value = tree[tree[curr].left].value + tree[tree[curr].right].value;
	return curr;
}

// return the smallest index such that query[idx, n] > k
int query(int rt, int l, int r, int k) {
	if (l > r) return 0;
	if (l == r) {
		return l;
	}
	// cout << l << " " << r << " left= " << tree[tree[rt].left].value << " k= " << k << endl;
	int mid = (l + r) >> 1;
	if (tree[tree[rt].left].value > k) {
		return query(tree[rt].left, l, mid, k);
	}
	return query(tree[rt].right, mid + 1, r, k - tree[tree[rt].left].value);
}

int main() {
	int n, version, i, j, ans;
	scanf("%d", &n);
	version = 2 * n + 1;
	for (i = 1; i <= n; ++i) scanf("%d", &a[i]);
	root[version--] = build(1, n);
	for (i = n; i >= 1; --i) {
		if (nxt[a[i]]) {
			root[version] = update(root[version + 1], nxt[a[i]], 1, n, 0);
			version--;
		}
		
		root[version] = update(root[version+1], i, 1, n, 1);
		id[i] = version;
		version--;
		nxt[a[i]] = i;
	}
	
	
	for (i = 1; i <= n; ++i) {
		j = 1;
		ans = 0;
		while (j <= n) {
			if (tree[root[id[j]]].value <= i) {
				ans++;
				j = n + 1;
			} else {
				ans++;
				j = query(root[id[j]], 1, n, i);
				// cout << j << endl;
			}
		}
		printf("%d ", ans);
	}
	printf("\n");
	return 0;
}