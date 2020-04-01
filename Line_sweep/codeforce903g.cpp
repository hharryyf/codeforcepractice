#include <bits/stdc++.h>
#define MAX_SIZE 262192
#define MID ((l+r)>>1)
#define LEFT (index << 1)
#define RIGHT (index << 1 | 1)
typedef long long ll;
using namespace std;

struct rangetree {
	struct segt {
		ll value, lz;
	};
	
	segt tree[MAX_SIZE << 1];
	void build(int l, int r, int index, ll a[]) {
		if (l > r) return;
		if (l == r) {
			tree[index].value = a[l];
			return;
		}
		
		build(l, MID, LEFT, a);
		build(MID + 1, r, RIGHT, a);
		tree[index].value = min(tree[LEFT].value, tree[RIGHT].value);
	}

	void pushdown(int l, int r, int index) {
		if (l > r) return;
		if (tree[index].lz) {
			if (l != r) {
				tree[LEFT].lz += tree[index].lz;
				tree[RIGHT].lz += tree[index].lz;
				tree[LEFT].value += tree[index].lz;
				tree[RIGHT].value += tree[index].lz;
			}
			tree[index].lz = 0;
		}
	}
	
	void update(int start, int end, int l, int r, int index, ll val) {
		if (start > end || l > r) return;
		pushdown(l, r, index);
		if (start > r || l > end) return;
		if (start <= l && r <= end) {
			tree[index].lz += val;
			tree[index].value += val;
			return;
		}
		
		if (end <= MID) {
			update(start, end, l, MID, LEFT, val);
		} else if (start >= MID + 1) {
			update(start, end, MID + 1, r, RIGHT, val);
		} else {
			update(start, end, l, MID, LEFT, val);
			update(start, end, MID + 1, r, RIGHT, val);
		}
		tree[index].value = min(tree[LEFT].value, tree[RIGHT].value);
	}
	
	ll query() {
		return tree[1].value;
	}
};

rangetree t1, t2;
vector<pair<int, int>> g[MAX_SIZE];
ll b[MAX_SIZE], a[MAX_SIZE];
ll cost[MAX_SIZE];
int n, m, q;

int main() {
	scanf("%d%d%d", &n, &m, &q);
	int i;
	for (i = 1; i < n; ++i) {
		scanf("%I64d%I64d", &a[i], &b[i]);
	}
	
	for (i = 0 ; i < m; ++i) {
		int l, r;
		ll w;
		scanf("%d%d%I64d", &l, &r, &w);
		g[l].emplace_back(r, w);
	}
	// init the right-hand-side range trees
	t1.build(0, n - 1, 1, b);
	// first phase of the problem, line sweep and find the 
	// optimal cost for each i
	for (i = 1; i <= n; ++i) {
		for (auto p : g[i]) {
			t1.update(0, p.first - 1, 0, n - 1, 1, p.second);
		}
		cost[i] = a[i] + t1.query();
	}
	
	// build the range tree based on the cost
	t2.build(1, n, 1, cost);
	
	printf("%I64d\n", t2.query());
	
	while (q > 0) {
		int v;
		ll w;
		scanf("%d%I64d", &v, &w);
		t2.update(v, v, 1, n, 1, w - a[v]);
		//cout << w << " <- " << a[v] << endl;
		//cout << "update " << w - a[v] << endl;
		printf("%I64d\n", t2.query());
		a[v] = w;
		q--;
	}
	return 0;
}