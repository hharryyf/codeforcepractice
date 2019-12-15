#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>
#define MAX_LEN 262191

using namespace std;

// total numbers in the array
int n;

// the segment tree
int tree[MAX_LEN];
// lazy array for propagation
int lazy[MAX_LEN];
// left->right->value
int a[MAX_LEN], b[MAX_LEN], c[MAX_LEN];
// update function
void update(int st, int ed, int l, int r, int op, int index);
// query [l, r] bitwise & result
int query(int st, int ed, int l, int r, int index);

int main(int argc, char *argv[]) {
	int m, i;
	cin >> n >> m;
	for (i = 0 ; i < m; i++) {
		cin >> a[i] >> b[i] >> c[i];
		update(a[i] - 1, b[i] - 1, 0, n-1, c[i], 1);
	}
	
	for (i = 0 ; i < m; i++) {
		if (query(a[i] - 1, b[i] - 1, 0, n - 1, 1) != c[i]) {
			cout << "NO" << endl;
			return 0;
		}
	}
	
	cout << "YES" << endl;
	cout << query(0, 0, 0, n-1, 1);
	for (i = 1 ; i < n; i++) {
		cout << " " << query(i, i, 0, n - 1, 1);
	}
	cout << endl;
	return 0;
}

int query(int st, int ed, int l, int r, int index) {
	if (st > ed || l > r) return 0;
	if (lazy[index] != 0) {
		tree[index] = tree[index] | lazy[index];
		if (l != r) {
			lazy[index * 2] |= lazy[index];
			lazy[index * 2 + 1] |=	lazy[index];
		}
		lazy[index] = 0;
	}
	
	if (l > ed || r < st) return 2147483647;
	if (st <= l && r <= ed) {
		return tree[index];
	}
	
	int mid = l + (r - l) / 2;
	return query(st, ed, l, mid, index * 2) & query(st, ed, mid + 1, r, index * 2 + 1);
}

void update(int st, int ed, int l, int r, int op, int index) {
	// invalid range
	if (st > ed || l > r) return;
	// lazy propagation -> push down
	if (lazy[index] != 0) {
		tree[index] = tree[index] | lazy[index];
		if (l != r) {
			lazy[index * 2] |= lazy[index];
			lazy[index * 2 + 1] |= lazy[index]; 
		}
		lazy[index] = 0;
	}
	
	// non-overlap
	if (l > ed || r < st) return;
	// total overlap
	if (st <= l && r <= ed) {
		tree[index] = tree[index] | op;
		if (l != r) {
			lazy[index * 2] |= op;
			lazy[index * 2 + 1] |= op;
		}
		return;
	}	
	
	// partial overlap
	int mid = l + (r - l) / 2;
	update(st, ed, l, mid, op, index * 2);
	update(st, ed, mid + 1, r, op, index * 2 + 1);
	tree[index] = tree[index * 2] & tree[index * 2 + 1]; 
}


