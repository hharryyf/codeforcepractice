#include <bits/stdc++.h>
#define MAX_SIZE 1048597
#define INF 10000000000000000ll
#define MID ((l+r) >> 1)
#define LEFT (index << 1)
#define RIGHT (index << 1 | 1)
typedef long long ll;
using namespace std;

struct segt {
	ll value, lz;
};

segt tree[MAX_SIZE];
ll dep[MAX_SIZE];
int subsz[MAX_SIZE];
int n, m;

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

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index].value = dep[l];
		return;
	}
	
	build(l, MID, LEFT);
	build(MID + 1, r, RIGHT);
	tree[index].value = min(tree[LEFT].value, tree[RIGHT].value);
}

void update(int start, int end, int l, int r, int index, ll val) {
	if (start > end || l > r) return;
	pushdown(l, r, index);
	if (start > r || l > end) return;
	if (start <= l && r <= end) {
		tree[index].value += val;
		tree[index].lz += val;
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

ll query(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return INF;
	pushdown(l, r, index);
	if (start > r || l > end) return INF;
	if (start <= l && r <= end) return tree[index].value;
	if (end <= MID) {
		return query(start, end, l, MID, LEFT);
	}
	
	if (start >= MID + 1) {
		return query(start, end, MID + 1, r, RIGHT);
	}
	
	return min(query(start, end, l, MID, LEFT), 
	           query(start, end, MID + 1, r, RIGHT));
}

struct qrs {
	int l, r, id;
};

vector<pair<int, ll> > g[MAX_SIZE >> 1];

vector<qrs> q[MAX_SIZE >> 1];

ll ans[MAX_SIZE >> 1];

void dfs(int v, int pre) {
	subsz[v] = 1;
	int cnt = 1;
	for (auto np : g[v]) {
		int nv = np.first;
		if (nv != pre) {
			dep[nv] = dep[v] + np.second;
			dfs(nv, v);
			subsz[v] += subsz[nv];
			cnt++;
		}
	}
	
	if (cnt != 1) {
		dep[v] = INF;
	}
}

void solve(int v, int pre) {
	for (auto qq : q[v]) {
		ans[qq.id] = query(qq.l, qq.r, 1, n, 1);
	}
	
	for (auto np : g[v]) {
		int nv = np.first;
		ll w = np.second;
		if (nv != pre) {
			// update
			int l = nv, r = nv + subsz[nv] - 1;
			update(1, l-1, 1, n, 1, w);
			update(r+1, n, 1, n, 1, w);
			update(l, r, 1, n, 1, -w);
			solve(nv, v);
			// cancel update
			update(1, l-1, 1, n, 1, -w);
			update(r+1, n, 1, n, 1, -w);
			update(l, r, 1, n, 1, w);
		}
	} 
}

int main() {
	int i;
	scanf("%d%d", &n, &m);
	for (i = 2; i <= n; ++i) {
		int v;
		ll w;
		scanf("%d%I64d", &v, &w);
		g[v].emplace_back(i, w);
	}
	
	dfs(1, 0);
	
	build(1, n, 1);
	
	for (i = 1; i <= m; ++i) {
		int v, l, r;
		scanf("%d%d%d", &v, &l, &r);
		q[v].push_back(qrs{l, r, i});
	}
	
	solve(1, 0);
	
	for (i = 1; i <= m; ++i) {
		printf("%I64d\n", ans[i]);
	}
	return 0;
}