#include <bits/stdc++.h>
#define MAX_LEN 524311

typedef long long ll;
using namespace std;

ll lazy[MAX_LEN], tree[MAX_LEN];
const ll INF = 3000000000000;

// build a segment tree
void build(int start, int end, int index);
// query a segment tree
ll query(int start, int end, int l, int r, int index);
// increment inc from start to end in the segment tree
void update(int start, int end, int l, int r, int index, ll inc);

int main(int argc, char *argv[]) {
	int i, n, m;
	cin >> n;
	build(0, n - 1, 1);
	cin >> m;
	for (i = 0 ; i < m; i++) {
		int from = 0, to = 0, inc = 0;
		scanf("%d%d", &from, &to);
		// cout << from << " " << to << endl;
		if (getchar() != '\n') {
			scanf("%d", &inc);
			if (to >= from) {
				update(from, to, 0, n - 1, 1, inc);
			} else {
				update(from, n - 1, 0, n - 1, 1, inc);
				update(0, to, 0, n - 1, 1, inc);
			}
		} else {
			// cout << "we enter here" << endl;
			if (to >= from) {
				cout << query(from, to, 0, n - 1, 1) << endl;
			} else {
				cout << min(query(from, n - 1, 0, n - 1, 1), query(0, to, 0, n - 1, 1)) << endl;
			}
		}
	    // cout << i << endl;
	}
	return 0;
}

void build(int start, int end, int index) {
	if (start > end) return;
	if (start == end) {
		cin >> tree[index];
		return;
	}
	int mid = start + (end - start) / 2;
	build(start, mid, index * 2);
	build(mid + 1, end, index * 2 + 1);
	tree[index] = min(tree[index * 2], tree[index * 2 + 1]);
}

ll query(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return INF;
	if (lazy[index] != 0) {
		tree[index] += lazy[index];
		if (l != r) {
			lazy[index * 2] += lazy[index];
			lazy[index * 2 + 1] += lazy[index];
		}
		lazy[index] = 0;
	}
	
	if (start > r || end < l) return INF;
	
	if (start <= l && r <= end) {
		return tree[index];
	}
	
	int mid = l + (r - l) / 2;
	return min(query(start, end, l, mid, index * 2), 
			   query(start, end, mid + 1, r, index * 2 + 1));
}

// increment inc from start to end in the segment tree
void update(int start, int end, int l, int r, int index, ll inc) {
	if (start > end || l > r) return;
	if (lazy[index] != 0) {
		tree[index] += lazy[index];
		if (l != r) {
			lazy[index * 2] += lazy[index];
			lazy[index * 2 + 1] += lazy[index];
		}
		lazy[index] = 0;
	}
	
	if (start > r || end < l) return;
	
	if (start <= l && r <= end) {
		tree[index] += inc;
		if (l != r) {
			lazy[index * 2] += inc;
			lazy[index * 2 + 1] += inc;
		}
		return;
	}
	
	int mid = l + (r - l) / 2;
	update(start, end, l, mid, index * 2, inc);
	update(start, end, mid + 1, r, index * 2 + 1, inc);
	tree[index] = min(tree[index * 2], tree[index * 2 + 1]);
}
