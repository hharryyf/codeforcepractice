#include <bits/stdc++.h>
#define MAX_SIZE 262222

using namespace std;

int n, m, k, q;

int tree[MAX_SIZE];

int ans[MAX_SIZE];

typedef struct point {
	int x;
	int y;
} Point;

typedef struct qp {
	Point left, right;
	int index;
} Queries;

Queries queries[MAX_SIZE];
Point rooks[MAX_SIZE];

static bool pcmp(Point &a, Point &b) {
	if (a.y != b.y) return a.y < b.y;
	return a.x < b.x;
}

static bool qcmp(Queries &a, Queries &b) {
	if (a.right.y != b.right.y) return a.right.y < b.right.y;
	return a.right.x < b.right.x;
}

// clear the tree
void build(int l, int r, int index);
// fill the ans
void fillans();

void update(int pt, int l, int r, int index, int val);

int main(int argc, char *argv[]) {
	int i;
	scanf("%d%d%d%d", &n, &m, &k, &q);
	for (i = 1; i <= k; i++) {
		scanf("%d%d", &rooks[i].x, &rooks[i].y);
	}
	
	for (i = 1; i <= q; i++) {
		scanf("%d%d%d%d", &queries[i].left.x, &queries[i].left.y, 
						  &queries[i].right.x, &queries[i].right.y);
		queries[i].index = i;
	}
	
	fillans();
	
	swap(n, m);
	
	for (i = 1; i <= k; i++) {
		swap(rooks[i].x, rooks[i].y);
	}
	
	for (i = 1; i <= q; i++) {
		swap(queries[i].left.x, queries[i].left.y);
		swap(queries[i].right.x, queries[i].right.y);
	}
	build(1, n, 1);
	fillans();
	for (i = 1; i <= q; i++) {
		if (ans[i]) {
			printf("YES\n");
		} else {
			printf("NO\n");
		}
	}
	return 0;
}

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index] = 0;
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	tree[index] = 0;
}

void update(int pt, int l, int r, int index, int val) {
	if (l > r) return;
	if (l == pt && pt == r) {
		tree[index] = max(tree[index], val);
		return;
	}
	
	int mid = l + (r - l) / 2;
	if (pt <= mid) {
		update(pt, l, mid, index * 2, val);
	} else {
		update(pt, mid + 1, r, index * 2 + 1, val);
	}
	
	tree[index] = min(tree[index * 2 + 1], tree[index * 2]);
}

int query(int start, int end, int l, int r, int index) {
	if (l > r || start > end) return MAX_SIZE;
	if (l > end || start > r) return MAX_SIZE;
	if (start <= l && r <= end) return tree[index];
	int mid = l + (r - l) / 2;
	return min(query(start, end, l, mid, index * 2), query(start, end, mid + 1, r, index * 2 + 1));
}

void fillans() {
	sort(rooks + 1, rooks + k + 1, pcmp);
	sort(queries + 1, queries + q + 1, qcmp);
	int i, j = 1;
	for (i = 1; i <= q; i++) {
		while (j <= k && (rooks[j].y < queries[i].right.y || 
			  (rooks[j].x <= queries[i].right.x && rooks[j].y == queries[i].right.y))) {
			update(rooks[j].x, 1, n, 1, rooks[j].y);
			// cout << i << "->update " << rooks[j].x << " " << rooks[j].y << endl;
			j++;
		}
		
		// cout << queries[i].left.x << " " << queries[i].right.x << " " << queries[i].left.y << "->";
		// cout << query(queries[i].left.x, queries[i].right.x, 1, n, 1)  << endl;
		if (query(queries[i].left.x, queries[i].right.x, 1, n, 1) >= queries[i].left.y) {
			ans[queries[i].index] = 1;
		}
	}	
}
