#pragma GCC optimize(3) 
#include <bits/stdc++.h>
#define MAX_SIZE 300011
#define MID ((l+r)>>1)
#define LEFT  (index<<1)
#define RIGHT  (index << 1 | 1)
typedef long long ll;
using namespace std;

ll a, c[MAX_SIZE], t[MAX_SIZE], d[MAX_SIZE];
int n;

struct segt {
	ll value, lz;
};

segt tree[MAX_SIZE << 2];

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
	if (start > end || l > r || start > r || l > end) return;
	pushdown(l, r, index);
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
	tree[index].value = max(tree[LEFT].value, tree[RIGHT].value);
}

ll query(int start, int end, int l, int r, int index) {
	if (start > end || l > r || start > r || l > end) return -1e18;
	pushdown(l, r, index);
	if (start <= l && r <= end) {
		return tree[index].value;
	}
	
	if (end <= MID) {
		return query(start, end, l, MID, LEFT);
	}
	
	if (start >= MID + 1) {
		return query(start, end, MID + 1, r, RIGHT);
	}
	
	return max(query(start, end, l, MID, LEFT), query(start, end, MID + 1, r, RIGHT));
}

int main() {
	vector<pair<ll, pair<int, int>>> q;
	int i;
	scanf("%d%I64d", &n, &a);
	for (i = 1; i <= n; ++i) {
		scanf("%I64d%I64d", &t[i], &c[i]);
		if (i > 1) {
			d[i] = (t[i] - t[i-1]) * (t[i] - t[i-1]);
		}
	}
	
	ll ans = 0;
	for (i = 1; i <= n; ++i) {
		// every node is incharge of itself-1 to the previous node
		
		while (!q.empty() && q.back().first <= d[i]) {
			// cout << "retrive " << q.back().second.first << " " << q.back().second.second << " by " << q.back().first << endl;
			update(q.back().second.first, q.back().second.second, 1, n, 1, q.back().first);
			q.pop_back();
		}
		
		int pre = 1;
		if (!q.empty()) {
			pre = q.back().second.second + 1;
		}
		q.push_back(make_pair(d[i], make_pair(pre, i - 1)));
		// cout << "update " << pre << " " << i-1  << " by " << d[i] << endl;
		update(pre, i - 1, 1, n, 1, -d[i]);
		update(1, i, 1, n, 1, a-c[i]);
		ans = max(ans, query(1, i, 1, n, 1));
	}
	
	printf("%I64d\n", ans);
	return 0;
}