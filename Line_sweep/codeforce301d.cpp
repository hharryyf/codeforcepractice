#include <bits/stdc++.h>
#define MAX_SIZE 200111
typedef long long ll;

using namespace std;

struct qrs {
	int l, r, id;
};

int n, q;

ll tree_1[MAX_SIZE], tree_2[MAX_SIZE];

ll ans[MAX_SIZE];

static bool cmp_1(const qrs &a, const qrs &b) {
	if (a.r != b.r) return a.r < b.r;
	return a.l < b.l;
}

static bool cmp_2(const qrs &a, const qrs &b) {
	if (a.l != b.l) return a.l < b.l;
	return a.r < b.r;
}

int shift(int x) {
	return (x & (-x));
}

void update(ll b[], int pos) {
	while (pos <= n) {
		b[pos]++;
		pos = pos + shift(pos);
	}
}

ll query(ll b[], int index) {
	ll ret = 0;
	while (index > 0) {
		ret = ret + b[index];
		index = index - shift(index);
	}
	
	return ret;
}

int ps[MAX_SIZE];

vector<qrs> qr;

int arr[MAX_SIZE];

void preprocess() {
	int i;
	scanf("%d%d", &n, &q);
	for (i = 1; i <= n; i++) {
		int v;
		scanf("%d", &v);
		arr[i] = v;
		ps[v] = i;
	}
	
	for (i = 1; i <= q; i++) {
		int l, r;
		scanf("%d%d", &l, &r);
		qr.push_back(qrs{l, r, i});
	}
}

void solve_1() {
	sort(qr.begin(), qr.end(), cmp_1);
	int i, j, k;
	int m = (int) qr.size();
	for (i = 0, j = 1; i < m; i++) {
		while (j <= n && j <= qr[i].r) {
			for (k = 1; k * arr[j] <= n; k++) {
				if (ps[k * arr[j]] <= j) {
					update(tree_1, ps[k * arr[j]]);
				}
			}
				
			j++;
		}
		ans[qr[i].id] += query(tree_1, qr[i].r) - query(tree_1, qr[i].l - 1);
	}
}

void solve_2() {
	sort(qr.begin(), qr.end(), cmp_2);
	int i, j, k;
	int m = (int) qr.size();
	for (i = m - 1, j = n; i >= 0; i--) {
		while (j >= 1 && j >= qr[i].l) {
			for (k = 1; k * arr[j] <= n; k++) {
				if (ps[k * arr[j]] >= j) {
					update(tree_2, ps[k * arr[j]]);
				}
			}
			j--;
		}
		ans[qr[i].id] += query(tree_2, qr[i].r) - query(tree_2, qr[i].l - 1) - (qr[i].r - qr[i].l + 1);
	}	
}

void getans() {
	for (int i = 1; i <= q; i++) {
		printf("%lld\n", ans[i]);
	}
}

int main() {
	preprocess();
	solve_1();
	solve_2();
	getans();
	return 0;
}
