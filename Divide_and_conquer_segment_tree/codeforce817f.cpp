#include <bits/stdc++.h>

#define MAX_SIZE 131082 

typedef long long Long;

using namespace std;

unordered_map<Long, int> mymap;

Long order[MAX_SIZE * 3];

Long discrete[MAX_SIZE * 3];


typedef struct segTree {
	int value;
	// update information 1 for 1/0 for 0/-1 for up-to-date; 
	int lazy; 
	// invert information 1 for yes and 0 for no; 
	int ivt;
} SegmentTree;

SegmentTree tree[MAX_SIZE * 8];

int n;

Long command[MAX_SIZE][3];

// set the lazy mark to be -1
void build(int l, int r, int index);
// a binary search in the segment tree
int minZero(int l, int r, int index);

void inverted(int start, int end, int l, int r, int index);

void lazyupdate(int l, int r, int index);

void update(int start, int end, int l, int r, int index, int v);

int main(int argc, char *argv[]) {
	int i, cnt = 0, m;
	mymap = unordered_map<Long, int>();
	cin >> m;
	// discreate the data into intervals, l, r and more importantly insert 1 into data
	for (i = 0 ; i < m; i++) {
		cin >> command[i][0] >> command[i][1] >> command[i][2];
		// for the add command, insert l, r and r + 1
		order[cnt++] = command[i][1];
		order[cnt++] = ++command[i][2];
	}
	
	order[cnt++] = 1;
	sort(order, order + cnt);
	
	n = 0;
	for (i = 0 ; i < cnt; i++) {
		if (i == 0) {
			mymap[order[i]] = n;
			discrete[n++] = order[i];
		} else {
			if (order[i] != order[i-1]) {
				mymap[order[i]] = n;
				discrete[n++] = order[i];
			}
		}
	}
	/*
	for (i = 0 ; i < n; i++) {
		cout << discrete[i] << " ";
	}
	
	cout << endl;
	*/
	build(0, n - 1, 1);
	
	for (i = 0 ; i < m; i++) {
		if (command[i][0] == 1) {
			update(mymap[command[i][1]], mymap[command[i][2]] - 1, 0, n - 1, 1, 1);
		} else if (command[i][0] == 2) {
			update(mymap[command[i][1]], mymap[command[i][2]] - 1, 0, n - 1, 1, 0);
		} else if (command[i][0] == 3) {
			inverted(mymap[command[i][1]], mymap[command[i][2]] - 1, 0, n - 1, 1);
		}
		
		int index =  minZero(0, n - 1, 1);
		cout << discrete[index] << endl;
	}
	
	return 0;
}

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index].lazy = -1;
		return;
	}
	
	build(l, l + (r - l) / 2, index * 2);
	build(1 + l + (r - l) / 2, r, index * 2 + 1);
	tree[index].lazy = -1;
}


void lazyupdate(int l, int r, int index) {
	if (l != r) {
		int mid = l + (r - l) / 2;
		if (tree[index].lazy != -1) {
			tree[index * 2].lazy = tree[index * 2 + 1].lazy = tree[index].lazy;
			tree[index * 2].value = (mid - l + 1) * tree[index].lazy;
			tree[index * 2 + 1].value = (r - mid) * tree[index].lazy; 
			tree[index * 2].ivt = tree[index * 2 + 1].ivt = 0;
		}
		
		if (tree[index].ivt != 0) {
			tree[index * 2].ivt ^= 1;
			tree[index * 2 + 1].ivt ^= 1;
			tree[index * 2].value = (mid - l + 1) - tree[2 * index].value;
			tree[index * 2 + 1].value = (r - mid) - tree[2 * index + 1].value;
		}
	}
	
	tree[index].lazy = -1;
	tree[index].ivt = 0;
}

void update(int start, int end, int l, int r, int index, int v) {
	if (start > end || l > r) return;
	lazyupdate(l, r, index);
	if (start > r || end < l) return;
	if (start <= l && r <= end) {
		tree[index].value = (r - l + 1) * v;
		tree[index].lazy = v;
		tree[index].ivt = 0;
		return;
	}
	
	update(start, end, l, l + (r - l) / 2, index * 2, v);
	update(start, end, 1 + l + (r - l) / 2, r, index * 2 + 1, v);
	tree[index].value = tree[index * 2].value + tree[index * 2 + 1].value;
}

void inverted(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return;
	lazyupdate(l, r, index);
	if (start > r || end < l) return;
	if (start <= l && r <= end) {
		tree[index].value = (r - l + 1) - tree[index].value;
		tree[index].ivt = 1 - tree[index].ivt;
		return;
	}
	
	inverted(start, end, l, l + (r - l) / 2, index * 2);
	inverted(start, end, 1 + l + (r - l) / 2, r, index * 2 + 1);
	tree[index].value = tree[index * 2].value + tree[index * 2 + 1].value;
}

int minZero(int l, int r, int index) {
	if (l > r) return 0;
	if (l == r) return l;
	lazyupdate(l, r, index);
	int mid = l + (r - l) / 2;
	if (tree[index * 2].value < (mid - l + 1)) {
		return minZero(l, mid, index * 2);
	}
	return minZero(mid + 1, r, index * 2 + 1);
}
