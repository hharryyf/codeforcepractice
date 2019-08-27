#include <bits/stdc++.h>
#define MAX_CHAR 26
#define MAX_LEN 262202

using namespace std;

// tree[i][] counts the number of occurence of each character a to z 
// in each range
int tree[MAX_CHAR][MAX_LEN];
// lazy stores the update info, if lazy = -1 means the current range is not 
// modified, if lazy = 0 means the current range should be set to 0, if lazy = 1
// means the current range should be set to 1
int lazy[MAX_CHAR][MAX_LEN];
int n;
char arr[MAX_LEN >> 1];

// build the segment tree on original order
void build(int l, int r, int index);
// query the occurrence of 'a' + dim in range [start, end]
int query(int start, int end, int l, int r, int index, int dim);
// update all element [start, end] to val = 0,1
void update(int start, int end, int l, int r, int index, int dim, int val);
// this stores the update info in the current round
int upd[MAX_CHAR];

int main(int argc, char *argv[]) {
	int m, i;
	scanf("%d%d", &n, &m);
	scanf("%s", arr);
	build(0, n - 1, 1);
	while (m > 0) {
		int l, r, ord;
		scanf("%d%d%d", &l, &r, &ord);
		// change to zero index
		l--;
		r--;
		for (i = 0 ; i < MAX_CHAR; i++) {
			upd[i] = query(l, r, 0, n - 1, 1, i);
			update(l, r, 0, n - 1, 1, i, 0);
		}
		// non-increasing order
		if (ord == 0) {
			int k = r;
			for (i = 0 ; i < MAX_CHAR; i++) {
				if (upd[i] != 0) {
					// cout << (char) (i + 'a') << " " << l << ", " << r << " -->" << upd[i] << endl; 
					update(k - upd[i] + 1, k, 0, n - 1, 1, i, 1);
					k = k - upd[i];
				}
			}
		} else if (ord == 1) {
			// non- decreasing order
			int k = l;
			for (i = 0 ; i < MAX_CHAR; i++) {
				if (upd[i] != 0) {
					// cout << (char) (i + 'a') << " " << l << ", " << r << " -->" << upd[i] << endl; 
					update(k, k + upd[i] - 1, 0, n - 1, 1, i, 1);
					k = k + upd[i];
				}
			}
		}
		m--;
		/*
		for (i = 0 ; i < n; i++) {
			for (int j = 0 ; j < MAX_CHAR; j++) {
				if (query(i, i, 0, n - 1, 1, j) != 0) {
					printf("%c", (j + 'a'));
					break;
				}
			}
		}
		printf("\n");*/
	}
	
	
	for (i = 0 ; i < n; i++) {
		for (int j = 0 ; j < MAX_CHAR; j++) {
			if (query(i, i, 0, n - 1, 1, j) != 0) {
				printf("%c", (j + 'a'));
				break;
			}
		}
	}
	
	cout << endl;
	return 0;
}

void build(int l, int r, int index) {
	if (l > r) return;
	int i;
	if (l == r) {
		int numch = (int) (arr[l] - 'a');
		tree[numch][index] = 1;
		for (i = 0 ; i < MAX_CHAR; i++) {
			lazy[i][index] = -1;
		}
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	for (i = 0; i < MAX_CHAR; i++) {
		tree[i][index] = tree[i][index * 2] + tree[i][index * 2 + 1];
		lazy[i][index] = -1;
	}
}

int query(int start, int end, int l, int r, int index, int dim) {
	if (dim < 0 || dim >= MAX_CHAR) return 0;
	if (l > r || start > end) return 0;
	if (lazy[dim][index] != -1) {
		tree[dim][index] = lazy[dim][index] * (r - l + 1);
		if (l != r) {
			lazy[dim][index * 2] = lazy[dim][index * 2 + 1] = lazy[dim][index];
		}
		lazy[dim][index] = -1;
	}
	
	if (start > r || l > end) return 0;
	
	if (start <= l && r <= end) return tree[dim][index];
	int mid = l + (r - l) / 2;
	return query(start, end, l, mid, index * 2, dim) + query(start, end, mid + 1, r, index * 2 + 1, dim);
}

void update(int start, int end, int l, int r, int index, int dim, int val) {
	if (dim < 0 || dim >= MAX_CHAR) return;
	if (l > r || start > end) return;
	if (lazy[dim][index] != -1) {
		tree[dim][index] = lazy[dim][index] * (r - l + 1);
		if (l != r) {
			lazy[dim][index * 2] = lazy[dim][index * 2 + 1] = lazy[dim][index];
		}
		lazy[dim][index] = -1;
	}
	
	if (start > r || l > end) return;
	if (start <= l && r <= end) {
		tree[dim][index] = val * (r - l + 1);
		if (l != r) {
			lazy[dim][index * 2] = lazy[dim][index * 2 + 1] = val;
		}
		return;
	}
	
	int mid = l + (r - l) / 2;
	update(start, end, l, mid, index * 2, dim, val);
	update(start, end, mid + 1, r, index * 2 + 1, dim, val);
	tree[dim][index] = tree[dim][index * 2] + tree[dim][index * 2 + 1];
}
