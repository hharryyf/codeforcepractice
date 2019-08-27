#include <bits/stdc++.h>
#define MAX_SIZE 524300
#define INF (1 << 29) 
typedef long long Long;

using namespace std;

typedef struct segTree {
	Long arr[2][2];
} SegmentTree;


SegmentTree tree[MAX_SIZE];

char grid[2][MAX_SIZE];

/*
	.X..
	...X
	
	for the given maze, we need to find the shortest path from point a to point b
	for a given point a, it can only moves to a + 1, a - 1, a + n, a - n without
	considering the boundaries
	
	it can be easily seen that we can only go in a col. non-decreasong order,
	we maintain a segment tree tree[i][j][k] refers to the shortest path
	from col i.left, row j to col i.right, row k
	
	then we can use divide and conquer and segment tree to answer the queries	
*/

int n;
int m;
SegmentTree merge_interval(int mid, SegmentTree t1, SegmentTree t2);
void build(int l, int r, int index);
SegmentTree query(int start, int end, int l, int r, int index);

int main(int argc, char *argv[]) {
	scanf("%d%d", &n, &m);
	scanf("%s", grid[0]);
	scanf("%s", grid[1]);
	build(0, n - 1, 1);
	
	while (m > 0) {
		int l, r, col1, col2, row1, row2;
		scanf("%d%d", &l, &r);
		col1 = (l - 1) % n;
		col2 = (r - 1) % n;
		row1 = (l - 1) / n;
		row2 = (r - 1) / n;
		SegmentTree t = query(min(col1, col2), max(col1, col2), 0, n - 1, 1);
		if (col1 <= col2) {
			cout << (t.arr[row1][row2] < INF ? t.arr[row1][row2] : -1) << endl;
		} else {
			cout << (t.arr[row2][row1] < INF ? t.arr[row2][row1] : -1) << endl;
		}
		m--;
	}
	return 0;
}

SegmentTree merge_interval(int mid, SegmentTree t1, SegmentTree t2) {
	SegmentTree t;
	Long len1 = (grid[0][mid] == '.' && grid[0][mid+1] == '.' ? 1 : INF);
	Long len2 = (grid[1][mid] == '.' && grid[1][mid+1] == '.' ? 1 : INF);
	t.arr[0][0] = min(t1.arr[0][0] + t2.arr[0][0] + len1, t1.arr[0][1] + t2.arr[1][0] + len2);
	t.arr[1][0] = min(t1.arr[1][0] + t2.arr[0][0] + len1, t1.arr[1][1] + t2.arr[1][0] + len2);
	t.arr[0][1] = min(t1.arr[0][0] + t2.arr[0][1] + len1, t1.arr[0][1] + t2.arr[1][1] + len2);
	t.arr[1][1] = min(t1.arr[1][0] + t2.arr[0][1] + len1, t1.arr[1][1] + t2.arr[1][1] + len2);
	return t;
}

void build(int l, int r, int index) {
	if (l > r) return;
	tree[index].arr[0][0] = tree[index].arr[0][1] = tree[index].arr[1][0] = tree[index].arr[1][1] = INF;
	if (l == r) {
		if (grid[0][l] == '.') {
			tree[index].arr[0][0] = 0;
		} 
		
		if (grid[1][l] == '.') {
			tree[index].arr[1][1] = 0;
		}
		
		if (grid[0][l] == '.' && grid[1][l] == '.') {
			tree[index].arr[0][1] = 1;
			tree[index].arr[1][0] = 1;
		}
		
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	tree[index] = merge_interval(mid, tree[index * 2], tree[index * 2 + 1]);
}

SegmentTree query(int start, int end, int l, int r, int index) {
	SegmentTree t;
	t.arr[0][0] = t.arr[0][1] = t.arr[1][0] = t.arr[1][1] = INF;
	if (start > end || l > r) return t;
	if (start > r || end < l) {
		t.arr[0][0] = t.arr[0][1] = t.arr[1][0] = t.arr[1][1] = 0;
		return t;
	}
	
	if (start <= l && r <= end) return tree[index];
	
	int mid = l + (r - l) / 2;
	if (end <= mid) {
		return query(start, end, l, mid, index * 2);
	} else if (start > mid) {
		return query(start, end, mid + 1, r, index * 2 + 1);
	}
	SegmentTree t1 = query(start, end, l, mid, index * 2);
	SegmentTree t2 = query(start, end, mid + 1, r, index * 2 + 1);
	t = merge_interval(mid, t1, t2);
	return t;
}
