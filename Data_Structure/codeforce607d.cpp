#include <bits/stdc++.h>
#define MAX_SIZE 524312
#define MID ((l+r)>>1)
#define LEFT (index << 1)
#define RIGHT (index << 1 | 1)
typedef long long ll;
using namespace std;

const int mod = 1000000007;

ll mul(ll a, ll b) {
	return (a * b) % mod;
}

int fix(ll x) {
	int ret = (x % mod);
	return ret >= 0 ? ret : ret + mod;
}

struct segt {
	// lz, weighted value, weight
	ll lz, value, wt;
};

segt tree[MAX_SIZE];
vector<int> g[MAX_SIZE >> 1];
int f[MAX_SIZE];
// op[0] = type
// op[1] = vertex
// op[2] = parent
int op[MAX_SIZE >> 1][4];
int id[MAX_SIZE >> 1], sz[MAX_SIZE >> 1];
ll value[MAX_SIZE];
int rid[MAX_SIZE];
int deg[MAX_SIZE];
int cnt = 1;
int n = 1, q;

void dfs(int v) {
	id[v] = cnt++;
	rid[id[v]] = v;
	sz[v] = 1;
	for (auto nv : g[v]) {
		dfs(nv);
		sz[v] += sz[nv];
	}
}

ll ivt(int p) {
	ll base = p, ret = 1;
	int m = mod - 2;
	while (m > 0) {
		if (m & 1) {
			ret = mul(ret, base);
			--m;
		} else {
			base = mul(base, base);
			m >>= 1;
		}
	}
	
	return ret;
}

segt pullup(segt t1, segt t2) {
	segt ret;
	ret.lz = 1;
	ret.value = (t1.value + t2.value) % mod;
	ret.wt = (t1.wt + t2.wt) % mod;
	return ret;
}

void pushdown(int l, int r, int index) {
	if (l > r) return;
	if (tree[index].lz != 1) {
		if (l != r) {
			tree[LEFT].lz = mul(tree[LEFT].lz, tree[index].lz);
			tree[RIGHT].lz = mul(tree[RIGHT].lz, tree[index].lz);
			tree[LEFT].value = mul(tree[LEFT].value, tree[index].lz);
			tree[RIGHT].value = mul(tree[RIGHT].value, tree[index].lz);
			tree[LEFT].wt = mul(tree[LEFT].wt, tree[index].lz);
			tree[RIGHT].wt = mul(tree[RIGHT].wt, tree[index].lz);
		}
		tree[index].lz = 1;
	}
}
// set the value to be value and weight to be wt
void change(int pt, int l, int r, int index, ll w) {
	if (pt < l || pt > r || l > r) return;
	pushdown(l, r, index);
	if (pt == l && l == r) {
		// TODO
		tree[index].lz = 1;
		tree[index].wt = w;
		tree[index].value = mul(value[rid[l]], w);
		return;
	}
	
	if (pt <= MID) {
		change(pt, l, MID, LEFT, w);
	} else {
		change(pt, MID + 1, r, RIGHT, w);
	}
	tree[index] = pullup(tree[LEFT], tree[RIGHT]);
}

void update(int start, int end, int l, int r, int index, ll val) {
	if (start > end || l > r) return;
	pushdown(l, r, index);
	if (start > r || l > end) return;
	if (start <= l && r <= end) {
		// TODO
		tree[index].lz = val;
		tree[index].value = mul(tree[index].value, val);
		tree[index].wt = mul(tree[index].wt, val);
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
	tree[index] = pullup(tree[LEFT], tree[RIGHT]);
}

segt query(int pt, int l, int r, int index) {
	if (pt == 0) {
		return segt{1, 1, 1};
	}
	
	if (pt < l || l > r || pt > r) return tree[0];
	pushdown(l, r, index);
	if (pt == l && l == r) return tree[index];
	if (pt <= MID) {
		return query(pt, l, MID, LEFT);
	}
	return query(pt, MID + 1, r, RIGHT);
}

segt queryR(int start, int end, int l, int r, int index) {
	if (start == end && start == 0) return segt{1, 1, 1};
	if (start > end || l > r) return tree[0];
	pushdown(l, r, index);
	if (start <= l && r <= end) return tree[index];
	if (end <= MID) {
		return queryR(start, end, l, MID, LEFT);
	} else if (start >= MID + 1) {
		return queryR(start, end, MID + 1, r, RIGHT);
	}
	return pullup(queryR(start, end, l, MID, LEFT), queryR(start, end, MID + 1, r, RIGHT));
}

int main() {
	int i;
	scanf("%I64d%d", &value[1], &q);
	for (i = 1; i <= q; ++i) {
		scanf("%d", &op[i][0]);
		if (op[i][0] == 1) {
			ll v;
			op[i][1] = ++n;
			scanf("%d%I64d", &op[i][2], &v);
			g[op[i][2]].push_back(op[i][1]);
			f[op[i][1]] = op[i][2];
			value[op[i][1]] = v;
		} else {
			scanf("%d", &op[i][1]);
		}
	}
	
	dfs(1);
	
	for (i = 1; i < MAX_SIZE; ++i) {
		tree[i].lz = 1;
		tree[i].wt = 1;
	}
	
	for (i = 1; i <= n; ++i) deg[i] = 1;
	
	change(id[1], 1, n, 1, 1);
	for (i = 1; i <= q; ++i) {
		if (op[i][0] == 1) {
			// link op[i][1] to op[i][2]
			ll ml = mul(deg[op[i][2]] + 1, ivt(deg[op[i][2]]));
			deg[op[i][2]]++;
			update(id[op[i][2]], id[op[i][2]] + sz[op[i][2]] - 1, 1, n, 1, ml);
			// cout << id[op[i][2]] << " to " << id[op[i][2]] + sz[op[i][2]] - 1 << "multiply " << ml << endl;
			auto ret = query(id[op[i][2]], 1, n, 1);
			// cout << ret.wt << " " << ret.value << endl;
			change(id[op[i][1]], 1, n, 1, ret.wt);
		} else {
			auto ret1 = queryR(id[op[i][1]], id[op[i][1]] + sz[op[i][1]] - 1, 1, n, 1);
			auto ret2 = query(id[f[op[i][1]]], 1, n, 1);
			// cout << ret1.value << "   " << ret1.wt << endl;
			printf("%d\n", fix(mul(ret1.value, ivt(ret2.wt))));
		}
	}
	return 0;
}