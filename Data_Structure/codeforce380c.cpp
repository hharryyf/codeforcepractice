#include <bits/stdc++.h>
#define MAX_LEN 2097160


using namespace std;
/*
	From this problem we understand that segment tree is perfect on solving 
	divide and conquer problems
	leftchild is the lower region solution
	rightchild is the higher region solution 
	parent is the overall solution
*/
char str[MAX_LEN >> 1];
typedef struct segTree {
	int leftbracket;  // the remaining leftbracket after the best match
	int rightbracket; // the remaining rightbracket after the best match
	int matchpair; // the maximum number in matched pair in the given range
} SegmentTree;

SegmentTree tree[MAX_LEN];
int n;

SegmentTree newNode();

// build a tree
void build(int l, int r, int index);
int query(int start, int end, int l, int r, int index);
// implementation of query return a struct treeNode indicating the
// isolate l,r bracket and also the brackets in the match pair in the given range
SegmentTree queryUtil(int start, int end, int l, int r, int index);

int main(int argc, char *argv[]) {
	scanf("%s", str);
	n = strlen(str);
	build(0, n - 1, 1);
	/*
	for (int i = 1 ; i < 2 * n; i++) {
		cout << "(" << tree[i].leftbracket << ", " << tree[i].rightbracket << ", " << tree[i].matchpair << ")" << endl;
	}*/
	int m, l, r;
	scanf("%d", &m);
	while (m > 0) {
		scanf("%d%d", &l, &r);
		printf("%d\n", query(l-1, r-1, 0, n - 1, 1));
		m--;
	}
	return 0;
}


void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		if (str[l] == '(') {
			tree[index].leftbracket = 1;
		} else if (str[l] == ')') {
			tree[index].rightbracket = 1;
		}
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	int newpair = min(tree[index * 2].leftbracket, tree[index * 2 + 1].rightbracket);
	tree[index].matchpair = 
			tree[index * 2].matchpair + tree[index * 2 + 1].matchpair + 2 * newpair;
	tree[index].leftbracket = 
			tree[index * 2].leftbracket + tree[index * 2 + 1].leftbracket - newpair;
	tree[index].rightbracket = 
			tree[index * 2].rightbracket + tree[index * 2 + 1].rightbracket - newpair;
}

SegmentTree newNode() {
	SegmentTree t;
	t.leftbracket = t.rightbracket = t.matchpair = 0;
	return t;
}

int query(int start, int end, int l, int r, int index) {
	SegmentTree t = queryUtil(start, end, l, r, index);
	return t.matchpair;
}

SegmentTree queryUtil(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return newNode();
	if (start > r || end < l) return newNode();
	if (start <= l && end >= r) {
		return tree[index];
	}
	
	int mid = l + (r - l) / 2;
	SegmentTree t1 = queryUtil(start, end, l, mid, index * 2);
	SegmentTree t2 = queryUtil(start, end, mid + 1, r, index * 2 + 1);
	SegmentTree t;
	int newpair = min(t1.leftbracket, t2.rightbracket);
	t.matchpair = t1.matchpair + t2.matchpair + newpair * 2;
	t.leftbracket = t1.leftbracket + t2.leftbracket - newpair;
	t.rightbracket = t1.rightbracket + t2.rightbracket - newpair;
	return t;
}
