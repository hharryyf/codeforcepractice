#include <bits/stdc++.h>
#define MAX_SIZE 524312
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
using namespace std;
typedef long long ll;

struct segt {
	ll val, lz;	
};

segt tree[MAX_SIZE << 1];
pair<int, ll> costa[MAX_SIZE];
pair<int, ll> costb[MAX_SIZE];
vector<int> disc;
vector<int> cost;

void pushdown(int l, int r, int index) {
	if (l > r) return;
	if (tree[index].lz != 0) {
		if (l != r) {
			tree[LEFT].lz += tree[index].lz;
			tree[LEFT].val += tree[index].lz;
			tree[RIGHT].val += tree[index].lz;
			tree[RIGHT].lz += tree[index].lz;
		}
		tree[index].lz = 0;
	}
}

void update(int start, int end, int l, int r, int index, int val) {
	if (start > end || l > r || start > r || l > end) return;
	pushdown(l, r, index);
	if (start <= l && r <= end) {
		tree[index].lz += val;
		tree[index].val += val;
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

	tree[index].val = max(tree[LEFT].val, tree[RIGHT].val);
}

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index].val = -cost[l];
		return;
	}

	build(l, MID, LEFT);
	build(MID + 1, r, RIGHT);
	tree[index].val = max(tree[LEFT].val, tree[RIGHT].val);
}

int n, m, p;
struct profit {
	int x, y;
	ll price;
	bool operator < (profit other) const{
		return x < other.x;
	}
};

profit g[MAX_SIZE];

int main() {
	int i, j;
	scanf("%d%d%d", &n, &m, &p);
	for (i = 1; i <= n; ++i) {
		scanf("%d%I64d", &costa[i].first, &costa[i].second);
	}

	for (i = 1; i <= m; ++i) {
		scanf("%d%I64d", &costb[i].first, &costb[i].second);
	}

	for (i = 1; i <= p; ++i) {
		scanf("%d%d%I64d", &g[i].x, &g[i].y, &g[i].price);
	}

	sort(costa + 1, costa + 1 + n);
	sort(costb + 1, costb + 1 + m);
	sort(g + 1, g + 1 + p);
	for (i = 1; i <= m; ++i) {
		if (i == 1 || costb[i].first != costb[i-1].first) {
			disc.push_back(costb[i].first);
			cost.push_back(costb[i].second);
		}
	}

	int sz = disc.size();
	ll ans = -1e12;
	build(0, sz - 1, 1);
	for (i = 1, j = 1; i <= n; ++i) {
		while (j <= p && g[j].x < costa[i].first) {
			int idx = upper_bound(disc.begin(), disc.end(), g[j].y) - disc.begin();
			update(idx, sz - 1, 0, sz - 1, 1, g[j].price);
			++j;
		}

		ans = max(ans, tree[1].val - costa[i].second);
	}

	cout << ans << endl;
	return 0;
}