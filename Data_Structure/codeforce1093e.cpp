#include <bits/stdc++.h>
#define MAX_SIZE 200111

using namespace std;

int tree[MAX_SIZE];
int n;

int shift(int x) {
	return x & (-x);
}

void update(int pos, int v) {
	if (pos < 1) return;
	while (pos <= n) {
		tree[pos] += v;
		pos += shift(pos);
	}
}

int query(int pos) {
	int ret = 0;
	while (pos > 0) {
		ret += tree[pos];
		pos -= shift(pos);
	}
	return ret;
}

struct qrs {
	// x, y, v, id
	int x, y, v, id, si;
};

qrs vc[MAX_SIZE << 3];
int ans[MAX_SIZE];
qrs tmp[MAX_SIZE << 3];
int cnt = 0;
// we need to support 2 types of queries
// increment(x, y) by 1, increment(x, y) by -1
// and query(1, 1, x, y)
// good news is the timestamp has already be sorted
// in ascending order, we don't need to worry about that
void cdq(int l, int r) {
	if (l >= r) return;
	int mid = (l + r) >> 1;
	cdq(l, mid);
	cdq(mid + 1, r);
	vector<pair<int, int>> hist;
	int i = l, j = mid + 1, k = 0;
	while (i <= mid && j <= r) {
		if (vc[i].x <= vc[j].x) {
			update(vc[i].y, vc[i].v);
			hist.emplace_back(vc[i].y, -vc[i].v);
			tmp[k++] = vc[i++];
		} else {
			ans[vc[j].id] += vc[j].si * query(vc[j].y);
			tmp[k++] = vc[j++];
		}
	}
	
	while (i <= mid) {
		tmp[k++] = vc[i++];
	}
		
	while (j <= r) {
		ans[vc[j].id] += vc[j].si * query(vc[j].y);
		tmp[k++] = vc[j++];
	}
	
	for (i = l; i <= r; ++i) {
		vc[i] = tmp[i-l];
	}
	
	for (auto h : hist) {
		update(h.first, h.second);
	}
}

int a[MAX_SIZE], b[MAX_SIZE], px[MAX_SIZE], py[MAX_SIZE];

int main() {
	int i, q = 1, m;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		px[a[i]] = i;
	}
	
	for (i = 1; i <= n; ++i) {
		scanf("%d", &b[i]);
		py[b[i]] = i;
	}
	
	for (i = 1; i <= n; ++i) {
		vc[cnt++] = qrs{px[i], py[i], 1, 0, 0};
	}
	
	for (i = 1; i <= m; ++i) {
		int tp;
		scanf("%d", &tp);
		if (tp == 1) {
			int x1, y1, x2, y2;
			scanf("%d%d%d%d", &x1, &x2, &y1, &y2);
			vc[cnt++] = qrs{x1-1, y1-1, 0, q, 1};
			vc[cnt++] = qrs{x1-1, y2, 0, q, -1};
			vc[cnt++] = qrs{x2, y1-1, 0, q, -1};
			vc[cnt++] = qrs{x2, y2, 0, q++, 1};
		} else {
			int x, y;
			scanf("%d%d", &x, &y);
			vc[cnt++] = qrs{px[b[x]], py[b[x]], -1, 0, 0};
			vc[cnt++] = qrs{px[b[y]], py[b[y]], -1, 0, 0};
			py[b[x]] = y, py[b[y]] = x;
			swap(b[x], b[y]);
			vc[cnt++] = qrs{px[b[x]], py[b[x]], 1, 0, 0};
			vc[cnt++] = qrs{px[b[y]], py[b[y]], 1, 0, 0};
		}
	}
	
	cdq(0, cnt - 1);
	
	for (i = 1; i < q; ++i) printf("%d\n", ans[i]);
	return 0;
}