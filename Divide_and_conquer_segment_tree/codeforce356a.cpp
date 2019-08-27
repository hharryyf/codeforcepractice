#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#define MAX_SIZE 1048601

using namespace std;

int tree[MAX_SIZE];
int lazy[MAX_SIZE];
int n, q;
int first[300100];
int second[300100];
int win[300100];
void update(int st, int ed, int value);

void updateUtil(int st, int ed, int l, int r, int index, int value);

int queryUtil(int st, int ed, int l, int r, int index);

int query(int st, int ed);

/*
	process the query in a reverse order
	maintain a max segment tree
	query all (i, i) in the end
*/

int main() {
	int l, r, w, m;
	scanf("%d%d", &n, &q);
	m = q;
	q--;
	while (q >= 0) {
		scanf("%d%d%d", &l, &r, &w);
		l = l - 1;
		r = r - 1;
		if (l > r) {
			swap(l, r);
		}
		
		first[q] = l;
		second[q] = r;
		win[q] = w;
		q--;
	}
	
	for (int i = 0 ; i < m; i++) {
		//cout << first[i] << " " << win[i] - 2 << endl; 
		update(first[i], win[i] - 2, win[i]);
		//cout << win[i] << " " << second[i] << endl; 
		update(win[i], second[i], win[i]);
	}
	
	int t = query(0, 0);
	printf("%d", t);
	for (int i = 1 ; i < n; i++) {
		printf(" %d", query(i, i));
	}
	printf("\n");
	return 0;
}

int query(int st, int ed) {
	return queryUtil(st, ed, 0, n - 1, 1);
}


int queryUtil(int st, int ed, int l, int r, int index) {
	if (ed < st || l > r) return 0;
	if (lazy[index] != 0) {
		tree[index] = lazy[index];
		if (l != r) {
			lazy[index * 2] = lazy[2 * index + 1] = lazy[index];
		}
		lazy[index] = 0;
	}
	
	if (st > r || ed < l) {
		return 0;
	}
	
	if (st <= l && ed >= r) {
		return tree[index];
	}
	
	int mid = l + (r - l) / 2;
	return max(queryUtil(st, ed, l, mid, index * 2), queryUtil(st, ed, mid + 1, r, index * 2 + 1));
}

void update(int st, int ed, int value) {
	if (ed < st || st < 0 || ed >= n) return;
	updateUtil(st, ed, 0, n - 1, 1, value);
}

void updateUtil(int st, int ed, int l, int r, int index, int value) {
	// invalid query
	if (ed < st || l > r) return;
	if (lazy[index] != 0) {
		tree[index] = lazy[index];
		if (l != r) {
			lazy[index * 2] = lazy[index];
			lazy[index * 2 + 1] = lazy[index];
		}
		lazy[index] = 0;
	}
	// no overlap
	if (st > r || ed < l) {
		return;
	}	
	
	if (st <= l && r <= ed) {
		tree[index] = value;
		if (l != r) {
			lazy[2 * index] = value;
			lazy[2 * index + 1] = value;
		}
		return;
	}
	
	int mid = l + (r - l) / 2;
	updateUtil(st, ed, l, mid, index * 2, value);
	updateUtil(st, ed, mid + 1, r, index * 2 + 1, value);
	tree[index] = max(tree[index * 2], tree[index * 2 + 1]);
}
