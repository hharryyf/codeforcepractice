#pragma GCC optimize(3)
#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 100111
using namespace std;


struct BIT {
	int n;
	ll tree[MAX_SIZE];
	int shift(int x) {
		return x & (-x);
	}
	
	void update(int pos, int v) {
		if (pos <= 0) return;
		while (pos <= n) {
			tree[pos] += v;
			pos += shift(pos);
		}
	}
	
	ll query(int pos) {
		ll ret = 0;
		while (pos > 0) {
			ret += tree[pos];
			pos -= shift(pos);
		}
		return ret;
	}
};

BIT tree;
set<int> st[MAX_SIZE];

struct qrs {
	// right bound, type, increment value, id, sign, previous
	int r, tp, v, id, si, pos;
};

qrs vc[MAX_SIZE << 3];
qrs tmp[MAX_SIZE << 3];
ll ans[MAX_SIZE];
int num[MAX_SIZE];
// the event counter
int cnt = 0;

void divc(int l, int r) {
	if (l >= r) return;
	int mid = (l + r) >> 1;
	divc(l, mid);
	divc(mid + 1, r);
	int i = l, j = mid + 1, k = 0;
	vector<pair<int, int>> his;
	while (i <= mid && j <= r) {
		if (vc[i].r < vc[j].r || (vc[i].r == vc[j].r && vc[i].tp < vc[j].tp)) {
			tree.update(vc[i].pos, vc[i].v);
			his.emplace_back(vc[i].pos, -vc[i].v);
			tmp[k++] = vc[i++];
		} else {
			ans[vc[j].id] += (tree.query(vc[j].r) - tree.query(vc[j].pos)) * vc[j].si;
			tmp[k++] = vc[j++];
		}
	}
	
	while (i <= mid) {
		tmp[k++] = vc[i++];
	}
	
	while (j <= r) {
		ans[vc[j].id] += (tree.query(vc[j].r) - tree.query(vc[j].pos)) * vc[j].si;
		tmp[k++] = vc[j++];
	}
	
	for (i = l; i <= r; ++i) vc[i] = tmp[i-l];
	
	for (auto h : his) {
		tree.update(h.first, h.second);
	}
}
// return the greatest index in st[num[idx]] which ret < idx
int getpre(int idx) {
	if (idx <= 0) return 0;
	auto iter = st[num[idx]].lower_bound(idx);
	if (iter == st[num[idx]].begin()) return 0;
	iter = prev(iter);
	return *iter;
}

// return the smallest index in st[num[idx]] which ret > idx
int getnxt(int idx) {
	if (idx <= 0) return 0;
	auto iter = st[num[idx]].upper_bound(idx);
	if (iter != st[num[idx]].end()) return *iter;
	return 0;
}

int main() {
	int i, n, q = 1, m;
	scanf("%d%d", &n, &m);
	tree.n = n;
	for (i = 1; i <= n; ++i) {
		scanf("%d", &num[i]);
		st[num[i]].insert(i);
	}
	
	for (i = 1; i <= n; ++i) {
		int pos = getpre(i);
		if (pos) {
			vc[cnt++] = qrs{i, 0, i - pos, 0, 0, pos};
		}
	}
	
	for (i = 1; i <= m; ++i) {
		int tp;
		scanf("%d", &tp);
		if (tp == 1) {
			int p, x;
			// num[p] <-| x
			// 
			scanf("%d%d", &p, &x);
			int nt = getnxt(p);
			int pr = getpre(p);
			if (pr) {
				vc[cnt++] = qrs{p, 0, -p + pr, 0, 0, pr};
			}
			
			if (nt) {
				vc[cnt++] = qrs{nt, 0, -nt+p, 0, 0, p};
				vc[cnt++] = qrs{nt, 0, nt - pr, 0, 0, pr};
			}
			st[num[p]].erase(p);
			num[p] = x;
			st[num[p]].insert(p);
			nt = getnxt(p), pr = getpre(p);
			if (nt) {
				vc[cnt++] = qrs{nt, 0, -nt+pr, 0, 0, pr};
				vc[cnt++] = qrs{nt, 0, nt-p, 0, 0, p};
			}
			
			if (pr) {
				vc[cnt++] = qrs{p, 0, p-pr, 0, 0, pr};
			}
			
		} else {
			int l, r;
			scanf("%d%d", &l, &r);
			vc[cnt++] = qrs{r, 1, 0, q++, 1, l-1};
		}
	}
	
	divc(0, cnt - 1);
	
	
	for (i = 1; i < q; ++i) printf("%I64d\n", ans[i]);
	
	return 0;
}