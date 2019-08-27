#include <bits/stdc++.h>
#define MAX_CHAR 26
#define MAX_LEN 262202

using namespace std;

int tree[MAX_CHAR][MAX_LEN];
// lazy = 1 means update the current interval to be all 1, lazy = 0 means set
// the current inverval to be all 0, otherwise, remain unmodefied
int lazy[MAX_CHAR][MAX_LEN];

char arr[MAX_LEN >> 1];

// the number of occurrence of each character in the given [start, end]
int occ[MAX_CHAR];

int n;

void build(int l, int r, int index);

void update(int start, int end, int l, int r, int index, int val, int dim);

int query(int start, int end, int l, int r, int index, int dim);

void print_out(int l, int r, int index);

// similar to the problem 558E, diff=2600, but this problem is much more tricky
// an edge case need to be considered
// and the time limit is very unfriendly 

int main(int argc, char *argv[]) {
	int m, i, valid = 1, count = 0, pivot = -1;
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d%d", &n, &m);
	scanf("%s", arr);
	build(0, n - 1, 1);	
	
	while (m > 0) {
		int l, r;
		scanf("%d%d", &l, &r);
		l--;
		r--;
		valid = 1;
		count = 0;
		// pivot refers to the character that must be put in the centre
		pivot = -1;
		for (i = 0 ; i < MAX_CHAR; i++) {
			occ[i] = query(l, r, 0, n - 1, 1, i);
			if (occ[i] % 2 == 1) {
				count++;
				pivot = i;
				if (count > 1) {
					valid = 0;
					break;
				}
			}
		}
		
		if (valid == 1) {
			for (i = 0 ; i < MAX_CHAR; i++) {
				update(l, r, 0, n - 1, 1, 0, i);
			}
			
			for (i = 0 ; i < MAX_CHAR; i++) {
				if (occ[i] == 0) continue;
				int st_left = l, ed_left = l + (occ[i] / 2) - 1;
				int st_right = r - (occ[i] / 2) + 1, ed_right = r;
				update(st_left, ed_left, 0, n - 1, 1, 1, i);
				update(st_right, ed_right, 0 ,n - 1, 1, 1, i);
				l = ed_left + 1;
				r = st_right - 1;
			}
			// edge case!
			if (pivot != -1) {
				update(l, r, 0, n - 1, 1, 1, pivot);
			}
		}
		
		m--;
	}
	
	print_out(0, n - 1, 1);
	printf("\n");
	return 0;
}

void print_out(int l, int r, int index) {
	if (l > r) return;
	int i;
	for (i = 0 ; i < MAX_CHAR; i++) {
		if (lazy[i][index] != -1) {
			tree[i][index] = lazy[i][index] * (r - l + 1);
			if (l != r) {
				lazy[i][index * 2] = lazy[i][index * 2 + 1] = lazy[i][index]; 
			}
			lazy[i][index] = -1;
		}
	}
	
	if (l == r) {
		for (i = 0 ; i < MAX_CHAR; i++) {
			if (tree[i][index]) {
				printf("%c", i + 'a');
				break;
			}
		}
		return;
	}
	
	int mid = l + (r - l) / 2;
	print_out(l, mid, index * 2);
	print_out(mid + 1, r, index * 2 + 1);
}

void build(int l, int r, int index) {
	if (l > r) return;
	int i;
	if (l == r) {
		int ch = (int) (arr[l] - 'a');
		tree[ch][index] = 1;
		for (i = 0 ; i < 26; i++) {
			lazy[i][index] = -1;
		}
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	for (i = 0 ; i < 26; i++) {
		lazy[i][index] = -1;
		tree[i][index] = tree[i][index * 2] + tree[i][index * 2 + 1];
	}
}

void update(int start, int end, int l, int r, int index, int val, int dim) {
	if (start > end || l > r || dim >= MAX_CHAR || dim < 0) return;
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
	update(start, end, l, mid, index * 2, val, dim);
	update(start, end, mid + 1, r, index * 2 + 1, val, dim);
	for (int i = 0 ; i < MAX_CHAR; i++) {
		tree[dim][index] = tree[dim][index * 2] + tree[dim][index * 2 + 1];
	}
}

int query(int start, int end, int l, int r, int index, int dim) {
	if (start > end || l > r || dim >= MAX_CHAR || dim < 0) return 0;
	if (lazy[dim][index] != -1) {
		tree[dim][index] = lazy[dim][index] * (r - l + 1);
		if (l != r) {
			lazy[dim][index * 2] = lazy[dim][index * 2 + 1] = lazy[dim][index]; 
		}
		lazy[dim][index] = -1;
	}	
	// very important!! we know that the tree stores only non-negative number
	// and we only want to query positive terms, if the current range sum is already
	// 0 there's no meaning of keeps going down!!
	if (tree[dim][index] == 0) return 0;
	
	if (start > r || l > end) return 0;
	
	if (start <= l && r <= end) return tree[dim][index];
	
	int mid = l + (r - l) / 2;
	
	if (end <= mid) {
		return query(start, end, l, mid, index * 2, dim);
	} else if (start >= mid + 1) {
		return query(start, end, mid + 1, r, index * 2 + 1, dim);
	}
	
	return query(start, end, l, mid, index * 2, dim) + query(start, end, mid + 1, r, index * 2 + 1, dim);
	
}
