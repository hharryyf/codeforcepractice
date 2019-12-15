#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#define MAX_SIZE 262151
#define INF 2000000000
using namespace std;

typedef struct TreeNode {
	// the min value of the current range
	int value;
	// the gcd of the current range
	int gcd;
	// the number of occurrence of the min number in the current range
	int num;
	
	
} TreeNode;

// number of element in the tree
int n;

// a segment tree of
TreeNode tree[MAX_SIZE];

// build a segment tree (quite special type)
void build(int l, int r, int index);

// helper function gcd of two numbers
int gcd(int a, int b);

// the query on l, r
void query(int l, int r);

// implementation of query
void queryUtil(int queryl, int queryr, int l, int r, int index);

/*
	we use segment tree to solve this problem, firstly establish a gcd+min
	segment tree, and record the occurrence of the min number in each range
	
	when the query part begins, we simply see if the minvalue in the range
	is equal to the gcd in the given range, if so, we return the number of
	occurrence of the minvalue, and r - l + 1 - num is the final answer
*/

// the queried range's gcd, occurence of the min, minvalue

TreeNode ans;

int main(void) {
	int m, l, r;
	scanf("%d", &n);
	build(0, n - 1, 1);
	scanf("%d", &m);
	for (int i = 0 ; i < m; i++) {
		scanf("%d%d", &l, &r);
		ans.value = INF;
		ans.gcd = 0;
		ans.num = 0;
		query(l-1, r-1);
		if (ans.value == ans.gcd) {
			printf("%d\n", r - l + 1 - ans.num);
		} else {
			printf("%d\n", r - l + 1);
		}
	}
	return 0;
}

void query(int l, int r) {
	queryUtil(l, r, 0, n - 1, 1);
}

void queryUtil(int queryl, int queryr, int l, int r, int index) {
	// invalid range
	if (queryl > queryr || l > r) return;
	// non-overlap
	if (queryl > r || queryr < l) return;
	// total overlap
	if (queryl <= l && r <= queryr) {
		ans.gcd = gcd(ans.gcd, tree[index].gcd);
		if (ans.value > tree[index].value) {
			ans.num = tree[index].num;
		} else if (ans.value == tree[index].value) {
			ans.num += tree[index].num;
		}
		ans.value = min(tree[index].value, ans.value);
		return;
	}
	
	int mid = l + (r - l) / 2;
	queryUtil(queryl, queryr, l, mid, index * 2);
	queryUtil(queryl, queryr, mid + 1, r, index * 2 + 1);
}

int gcd(int a, int b) {
	if (a == 0) return b;
	return gcd(b % a, a);
}

void build(int l, int r, int index) {
	int value;
	// invalid range
	if (l > r) return;
	// leaf TreeNodes
	if (l == r) {
		scanf("%d", &value);
		tree[index].value = value;
		tree[index].gcd = value;
		tree[index].num = 1;
		return;
	}
	
	// internal TreeNodes
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	tree[index].num = 0;
	tree[index].value = min(tree[index * 2].value, tree[index * 2 + 1].value);
	if (tree[index].value == tree[index * 2].value) {
		tree[index].num += tree[index * 2].num;
	}
	
	if (tree[index].value == tree[index * 2 + 1].value) {
		tree[index].num += tree[index * 2 + 1].num;
	}
	
	tree[index].gcd = gcd(tree[index * 2].gcd, tree[index * 2 + 1].gcd); 
}
