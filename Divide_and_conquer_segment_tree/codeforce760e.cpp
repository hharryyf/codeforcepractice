#include <bits/stdc++.h>
#define MAX_SIZE 262152

using namespace std;
/**
* For a push and pop operation we can imagine it as push = 1 and pop = -1
* To make it clearer let's say an array arr[1: n] which arr[i] = {0,-1,1}
* 0 is undetermined, 1 means the ith order operation is a push operation, -1 similarly
* Then we are interested in the largest index value such that 
* 	arr[i] + arr[i+1] + ... + arr[n] > 0
* But this would be too difficult to maintain if a single array or even BIT is used, 
* because the suffix sum itself has no monitonically increasing or decreasing feature
* 
* What we can do is to rewrite b[i] = sum(arr[i] + arr[i+1] + ... +arr[n])
* and we can observe that either a push or pop operation is down, all the suffix
* sum of the elements from arr[1] to arr[i] could be affected and later elements
* has no effect, hence we use a segment tree to maintain a maximal suffix sum
* of element [i:j]
* when a push or pop operation is iniciated, we increment the values from 1 to i
* by 1 or -1, and then we query the maximum index value such that it suffix sum
* is greater than 0 return it as an answer
*/
int value[MAX_SIZE >> 1];

// total operations
int n;

int lazy[MAX_SIZE], tree[MAX_SIZE];

// increment [start, end] by delta
// update the maximal in that range 
void update(int start, int end, int l, int r, int index, int delta);

// this query returns the maximum l/r such that l==r and
int query(int l, int r, int index);

int main(int argc, char *argv[]) {
	cin >> n;
	int i, order, t, val;
	for (i = 0 ; i < n; i++) {
		cin >> order >> t;
		if (t == 0) {
			update(0, order - 1, 0, n - 1, 1, -1);
		} else {
			cin >> val;
			value[order - 1] = val;
			update(0, order - 1, 0, n - 1, 1, 1);
		}
		
		int index = query(0, n - 1, 1);
		cout << (index >= 0 ? value[index] : -1) << endl;
	}
	return 0;
}

// increment [start, end] by delta
// update the maximal in that range 
void update(int start, int end, int l, int r, int index, int delta) {
	if (start > end || l > r) {
		return;
	}	
	
	if (lazy[index] != 0) {
		tree[index] += lazy[index];
		if (l != r) {
			lazy[index * 2] += lazy[index];
			lazy[index * 2 + 1] += lazy[index];
		}
		lazy[index] = 0;
	}
	
	if (start > r || l > end) return;
	if (start <= l && r <= end) {
		tree[index] += delta;
		if (l != r) {
			lazy[index * 2] += delta;
			lazy[index * 2 + 1] += delta;
		}
		return;
	}
	
	int mid = l + (r - l) / 2;
	update(start, end, l, mid, index * 2, delta);
	update(start, end, mid + 1, r, index * 2 + 1, delta);
	tree[index] = max(tree[index * 2], tree[index * 2 + 1]);
}

// this query returns the maximum l/r such that l==r and
int query(int l, int r, int index) {
	if (l > r) return -1;
	if (lazy[index] != 0) {
		tree[index] += lazy[index];
		if (l != r) {
			lazy[index * 2] += lazy[index];
			lazy[index * 2 + 1] += lazy[index];
		}
		lazy[index] = 0;
	}
	
	if (l == r) {
		return (tree[index] > 0 ? l : -1);
	}
	
	int mid = l + (r - l) / 2;
	if (tree[index * 2 + 1] + lazy[index * 2 + 1] > 0) {
		return query(mid + 1, r, index * 2 + 1);
	} else if (tree[index * 2] + lazy[index * 2] > 0) {
		return query(l, mid, index * 2);
	}
	return -1;
}
