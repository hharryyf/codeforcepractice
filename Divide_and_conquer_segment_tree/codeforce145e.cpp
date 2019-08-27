#include <bits/stdc++.h>
#define MAX_LEN 2097200

using namespace std;

typedef struct treeNode {
	// the number of 4, the number of 7, length of the longest non-decreasing sequence
	// length of the longest non-increasing sequence 
	// in the current interval
	int count4, count7, lis, lds;
	// lazy indicates whether the current interval is flipped or not
	int lazy;
} SegmentTree;

SegmentTree tree[MAX_LEN];
int n;
char str[MAX_LEN >> 1], oper[8];

void mergeinterval(int l, int r, int index);
void build(int l, int r, int index);
void update(int start, int end, int l, int r, int index);
SegmentTree query(int start, int end, int l, int r, int index);
SegmentTree newNode();
void pushdown(int l, int r, int index);
SegmentTree mergeNode(SegmentTree t1, SegmentTree t2);

int main(int argc, char * argv[]) {
	int m;
	cin >> n >> m;
	int l, r;
	scanf("%s", str);
	build(0, n - 1, 1);
	while (m > 0) {
		scanf("%s", oper);
		if (oper[0] == 'c') {
			SegmentTree t = query(0, n-1, 0, n-1, 1);
			printf("%d\n", t.lis);
		} else if (oper[0] == 's') {
			scanf("%d%d", &l, &r);
			update(l-1, r-1, 0, n-1, 1);
		}
		m--;
	}
	return 0;
}

SegmentTree newNode() {
	SegmentTree t;
	t.count4 =  t.count7= t.lis = t.lds = t.lazy = 0;
	return t;
}

SegmentTree mergeNode(SegmentTree t1, SegmentTree t2) {
	SegmentTree t;
	t.count4 = t1.count4 + t2.count4;
	t.count7 = t1.count7 + t2.count7;
	// lis update
	t.lis = max(t1.lis + t2.count7, t1.count4 + t2.count7);
	t.lis = max(t.lis, max(t.count7, t.count4));
	t.lis = max(t.lis, t1.count4 + t2.lis);	
	// lds update
	t.lds = max(t1.lds + t2.count4, t1.count7 + t2.count4);
	t.lds = max(t.lds, max(t.count7, t.count4));
	t.lds = max(t.lds, t1.count7 + t2.lds);
	return t;
}

SegmentTree query(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return newNode();
	pushdown(l, r, index);
	if (start > r || end < l) return newNode();
	if (start <= l && r <= end) {
		return tree[index];
	}
	
	int mid = l + (r - l) / 2;
	SegmentTree t1 = query(start, end, l, mid, index * 2);
	SegmentTree t2 = query(start, end, mid + 1, r, index * 2 + 1);
	SegmentTree t = mergeNode(t1, t2);
	return t;
}


void update(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return;
	pushdown(l, r, index);
	if (start > r || end < l) return;
	if (start <= l && r <= end) {
		swap(tree[index].count4, tree[index].count7);
		swap(tree[index].lis, tree[index].lds);
		if (l != r) {
			tree[index * 2].lazy ^= 1;
			tree[index * 2 + 1].lazy ^= 1;
		}
		return;
	}
	
	int mid = l + (r - l) / 2;
	update(start, end, l, mid, index * 2);
	update(start, end, mid + 1, r, index * 2 + 1);
	mergeinterval(l, r, index);	
}


void pushdown(int l, int r, int index) {
	if (tree[index].lazy != 0) {
		swap(tree[index].count4, tree[index].count7);
		swap(tree[index].lis, tree[index].lds);
		if (l != r) {
			tree[index * 2].lazy ^= 1;
			tree[index * 2 + 1].lazy ^= 1;
		}
		tree[index].lazy = 0;
	}
}

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		mergeinterval(l, r, index);
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	mergeinterval(l, r, index);
}

void mergeinterval(int l, int r, int index) {
	if (l == r) {
		tree[index].count4 = (str[l] == '4');
		tree[index].count7 = (str[l] == '7');
		tree[index].lis = tree[index].lds = 1;
		return;
	}
	tree[index].count4 = tree[index * 2].count4 + tree[index * 2 + 1].count4;
	tree[index].count7 = tree[index * 2].count7 + tree[index * 2 + 1].count7;
	// lis update
	tree[index].lis = max(tree[index * 2].lis + tree[index * 2 + 1].count7, 
						  tree[index * 2].count4 + tree[index * 2 + 1].count7);
	tree[index].lis = max(tree[index].lis, max(tree[index].count7, tree[index].count4));
	tree[index].lis = max(tree[index].lis, tree[index * 2].count4 + tree[index * 2 + 1].lis);	
	// lds update
	tree[index].lds = max(tree[index * 2].lds + tree[index * 2 + 1].count4, 
						  tree[index * 2].count7 + tree[index * 2 + 1].count4);
	tree[index].lds = max(tree[index].lds, max(tree[index].count7, tree[index].count4));
	tree[index].lds = max(tree[index].lds, tree[index * 2].count7 + tree[index * 2 + 1].lds);
}
