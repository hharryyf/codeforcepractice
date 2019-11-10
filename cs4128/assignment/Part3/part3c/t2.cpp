#include <bits/stdc++.h>
#define MAX_SIZE 524292
using namespace std;

struct qrs {
	int l, r, dn, up, id;
};

struct pts {
	int x, y;
};

static bool cmp_1(const qrs &a, const qrs &b) {
	return a.up < b.up;
}

static bool cmp_2(const pts &a, const pts &b) {
	return a.y < b.y;
}

// n points, q queries
int n, q;

int tree[MAX_SIZE];

// all the points
vector<pts> pt;
// all the queries
vector<qrs> qr;
// add a point
void addpoint(int x, int y) {
	pt.push_back(pts{x, y});
}
// add a query
void addquery(int l, int r, int dn, int up, int id) {
	qr.push_back(qrs{l, r, dn, up, id});
}

// set pos to val
void update(int pos, int l, int r, int index, int val) {
	if (l > r) return;
	if (l == r && r == pos) {
		tree[index] = max(tree[index], val);
		return;
	}
	
	int mid = l + (r - l) / 2;
	if (pos <= mid) {
		update(pos, l, mid, index * 2, val);
	} else {
		update(pos, mid + 1, r, index * 2 + 1, val);
	}
	tree[index] = max(tree[index * 2], tree[index * 2 + 1]);
}

// range max query
int query(int start, int end, int l, int r, int index) {
	if (start > end || l > r || start > r || l > end) return 0;
	if (start <= l && r <= end) return tree[index];
	int mid = l + (r - l) / 2;
	return max(query(start, end, l, mid, index * 2), query(start, end, mid + 1, r, index * 2 + 1));
}

int ans[MAX_SIZE >> 1];

// solve all the points and queries, invariant, this function is only called when
// the points and queries are added and pt.size = n, qr.size = q
void solve() {
	sort(qr.begin(), qr.end(), cmp_1);
	sort(pt.begin(), pt.end(), cmp_2);
	int i = 0, j = 0;
	for (i = 0, j = 0; i < q; i++) {
		while (j < n && qr[i].up >= pt[j].y) {
			update(pt[j].x, 1, n, 1, pt[j].y);
			j++;
		}
		
		ans[qr[i].id] = (query(qr[i].l, qr[i].r, 1, n, 1) >= qr[i].dn);
	}	
	
	for (i = 1; i <= q; i++) {
		cout << ans[i] << endl;
	}
}


int main() {
	scanf("%d%d", &n, &q);
	int i;
	for (i = 1; i <= n; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		addpoint(x, y);
	}
	
	for (i = 1; i <= q; i++) {
		int l, r, dn, up;
		scanf("%d%d%d%d", &l, &r, &dn, &up);
		addquery(l, r, dn, up, i);
	}
	
	solve();
	return 0;
}
