#include <cstdio>
#include <iostream>
#include <algorithm>
#define MAX_LEN 262211
using namespace std;

typedef struct treeNode {
	int depth; // the depth is increasing from leaf to root 
	int value;
} TreeNode;

// the segment tree
TreeNode tree[MAX_LEN];
// total element
int n;
// build a segment tree
void build(int l, int r, int index);
// update the pos with v
void update(int l, int r, int pos, int v, int index);

int main(int argc, char *argv[]) {
	int  m, i, index, p;
	cin >> n >> m;
	build(0, (1 << n) - 1, 1);
	for (i = 0 ; i < m; i++) {
		cin >> index >> p;
		update(0, (1 << n) - 1, index - 1, p, 1);
		cout << tree[1].value << endl;
	}
	return 0;
}

void build(int l, int r, int index) {
	int v;
	// invalid range
	if (l > r) return;
	// leaf node, input the value, set depth = 0
	if (l == r) {
		cin >> v;
		tree[index].value = v;
		tree[index].depth = 0;
		return; 
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	tree[index].depth = tree[index * 2].depth + 1;
	// two operations |, ^ according to the depth
	if (tree[index].depth % 2 == 1) {
		tree[index].value = tree[2 * index].value | tree[2 * index + 1].value;
	} else {
		tree[index].value = tree[2 * index].value ^ tree[2 * index + 1].value;
	}
}

void update(int l, int r, int pos, int v, int index) {
	// invalid range
	if (pos < l || pos > r || l > r) return;
	// find the position, update
	if (pos == l && pos == r) {
		tree[index].value = v;
		// cout << "the value is fixed " << index << " " << v << endl;
		return;
	}
	// general case
	int mid = l + (r - l) / 2;
	if (pos <= mid) {
		update(l, mid, pos, v, 2 * index);
	} else {
		update(mid + 1, r, pos, v, 2 * index + 1);
	}
	
	// two operations |, ^ according to the depth
	if (tree[index].depth % 2 == 1) {
		tree[index].value = tree[2 * index].value | tree[2 * index + 1].value;
	} else {
		tree[index].value = tree[2 * index].value ^ tree[2 * index + 1].value;
	}	
}
