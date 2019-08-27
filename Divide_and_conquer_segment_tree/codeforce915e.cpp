#include <bits/stdc++.h>
#define MAX_SIZE 2497160

using namespace std;

typedef struct segTree {
	// the sum of all numbers exists in the l, r interval
	int allsum;
	// the lazy info
	int lazy;
	// the current value of the node
	int value;
} SegmentTree;

SegmentTree tree[MAX_SIZE << 1];

// total days
int n;

int oper[MAX_SIZE >> 3][3];
int disc[MAX_SIZE >> 2];
vector<int> days;
vector<int> weight;

void build(int l, int r, int index);
void update(int start, int end, int l, int r, int index, int val);
int query(int start, int end, int l, int r, int index);

int main(int argc, char *argv[]) {
	int i, j = 0, m;
	scanf("%d", &n);
	scanf("%d", &m);
	for (i = 0 ; i < m; i++) {
		scanf("%d%d%d", &oper[i][0], &oper[i][1], &oper[i][2]);
		disc[j++] = oper[i][0];
		disc[j++] = oper[i][1];
	}
	
	sort(disc, disc + 2 * m);
	
	for (i = 0 ; i < 2 * m; i++) {
		if (i == 0) {
			if (disc[i] == 1) {
				days.push_back(1);
				weight.push_back(1);
			} else {
				days.push_back(1);
				weight.push_back(disc[i] - 1);
				days.push_back(disc[i]);
				weight.push_back(1);
			}
		} else {
			if (disc[i] - disc[i-1] <= 0) continue;
			if (disc[i] - disc[i-1] == 1) {
				days.push_back(disc[i]);
				weight.push_back(1);
			} else {
				days.push_back(disc[i-1] + 1);
				weight.push_back(disc[i] - disc[i-1] - 1);
				days.push_back(disc[i]);
				weight.push_back(1);
			}
		}
	}
	
	if (n - disc[2 * m - 1] > 0) {
		days.push_back(disc[2 * m - 1] + 1);
		weight.push_back(n - disc[2 * m - 1]);
	}	
	
	int totalnode = weight.size();
	build(0, totalnode - 1, 1);
	
	for (i = 0 ; i < m; i++) {
		int l = lower_bound(days.begin(), days.end(), oper[i][0]) - days.begin();
		int r = lower_bound(days.begin(), days.end(), oper[i][1]) - days.begin();
		// this means adding
		if (oper[i][2] == 2) {
			update(l, r, 0, totalnode - 1, 1, 1);
		} else if (oper[i][2] == 1) {
			// this means cancel
			update(l, r, 0, totalnode - 1, 1, -1);
		}
		printf("%d\n", query(0, totalnode - 1, 0, totalnode - 1, 1));
	}
	return 0;
}

void update(int start, int end, int l, int r, int index, int val) {
	if (start > end || l > r) return;
	if (tree[index].lazy != 0) {
		// 1 refers to the current range should set to allsum, -1 means 0
		if (tree[index].lazy == 1) {
			tree[index].value = tree[index].allsum;
		} else {
			tree[index].value = 0;
		}
		if (l != r) {
			tree[index * 2].lazy = tree[index * 2 + 1].lazy = tree[index].lazy;
		}
		tree[index].lazy = 0;
	}
	
	if (start > r || end < l) return;
	if (start <= l && r <= end) {
		if (val == 1) {
			tree[index].value = tree[index].allsum;
		} else if (val == -1) {
			tree[index].value = 0;
		}
		
		if (l != r) {
			tree[index * 2].lazy = tree[index * 2 + 1].lazy = val;
		}
		return;
	}
	
	int mid = l + (r - l) / 2;
	update(start, end, l, mid, index * 2, val);
	update(start, end, mid + 1, r, index * 2 + 1, val);
	tree[index].value = tree[index * 2].value + tree[index * 2 + 1].value;
}

int query(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return 0;
	if (tree[index].lazy != 0) {
		// 1 refers to the current range should set to allsum, -1 means 0
		if (tree[index].lazy == 1) {
			tree[index].value = tree[index].allsum;
		} else {
			tree[index].value = 0;
		}
		if (l != r) {
			tree[index * 2].lazy = tree[index * 2 + 1].lazy = tree[index].lazy;
		}
		tree[index].lazy = 0;
	}
	
	if (start > r || end < l) return 0;
	if (start <= l && r <= end) return tree[index].value;
	int mid = l + (r - l) / 2;
	return query(start, end, l, mid, index * 2) + query(start, end, mid + 1, r, index * 2 + 1);
}


void build(int l, int r, int index) {
	if (l > r) return;
	tree[index].lazy = 0;
	if (l == r) {
		tree[index].value = tree[index].allsum = weight[l];
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	tree[index].value = tree[index].allsum = tree[index * 2].value + tree[index * 2 + 1].value;
}
