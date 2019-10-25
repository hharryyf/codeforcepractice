#include <bits/stdc++.h>

#define MAX_SIZE 524292
#define INF 1000000000000000ll

typedef long long ll;

using namespace std;

struct segt {
	ll value, lz;
};

struct event {
	int start, end;
	ll value;
};

segt tree[MAX_SIZE];

ll dp[MAX_SIZE >> 1];

int n;

vector<event> a[MAX_SIZE], b[MAX_SIZE];

ll cost[MAX_SIZE >> 1];

void pushdown(int l, int r, int index) {
	if (tree[index].lz) {
		if (l != r) {
			tree[index * 2].value += tree[index].lz;
			tree[index * 2 + 1].value += tree[index].lz;
			tree[index * 2].lz += tree[index].lz;
			tree[index * 2 + 1].lz += tree[index].lz;
		}
		tree[index].lz = 0ll;
	}
}

ll query(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return -INF;
	pushdown(l, r, index);
	if (start > r || l > end) return -INF;
	if (start <= l && r <= end) return tree[index].value;
	int mid = l + (r - l) / 2;
	if (end <= mid) {
		return query(start, end, l, mid, index * 2);
	}
	
	if (start >= mid + 1) {
		return query(start, end, mid + 1, r, index * 2 + 1);
	}
	
	return max(query(start, end, l, mid, index * 2), query(start, end, mid + 1, r, index * 2 + 1));
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
	
	int mid = l + (r - l) / 2;
	update(start, end, l, mid, index * 2, val);
	update(start, end, mid + 1, r, index * 2 + 1, val);
	tree[index].value = max(tree[index * 2].value, tree[index * 2 + 1].value);
}


int main() {
	int m, i;
	scanf("%d%d", &n, &m);	
	for (i = 1; i <= n; i++) {
		scanf("%lld", &cost[i]);
	}
	
	for (i = 0 ; i < m; i++) {
		int st, ed;
		ll v;
		scanf("%d%d%lld", &st, &ed, &v);
		a[st].push_back(event{st, ed, v});
		b[ed].push_back(event{st, ed, v});
	}
	
	set<pair<int, int> > s;
	
	for (i = 1; i <= n; i++) {
		for (auto evt : a[i]) {
			s.insert(make_pair(evt.start, evt.end));
		}
		
		if (!s.empty()) {
			update(0, i-1, 0, n, 1, -cost[i]);
		}
		
		for (auto evt : b[i]) {
			update(0, evt.start-1, 0, n, 1, evt.value);
		}	
		
		dp[i] = max(dp[i-1], query(0, i-1, 0, n, 1));
		
		
		// change(i, 1, n, 1, dp[i]);
		update(i, i, 0, n, 1, dp[i]);
		
		// cout << dp[i] << " ";
		for (auto evt : b[i]) {
			s.erase(make_pair(evt.start, evt.end));
		}
	}
	
	// cout << endl;
	printf("%lld\n", dp[n]);
	return 0;
}
