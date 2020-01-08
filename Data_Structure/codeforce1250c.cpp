#include <bits/stdc++.h>
#define MAX_SIZE 524292

typedef long long ll;
using namespace std;

struct segt {
	ll value, lz;
};

segt tree[MAX_SIZE];
ll ans = 0;
int L, R;
struct money {
	int l, id;
	ll p;
};

vector<money> g[MAX_SIZE >> 1];

void pushdown(int l, int r, int index) {
	if (l > r) return;
	if (tree[index].lz) {
		if (l != r) {
			tree[index * 2].lz += tree[index].lz;
			tree[index * 2 + 1].lz += tree[index].lz;
			tree[index * 2].value += tree[index].lz;
			tree[index * 2 + 1].value += tree[index].lz;
		}
		tree[index].lz = 0;
	}
}

pair<ll, int> query(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return make_pair(0, 0);
	pushdown(l, r, index);
	if (start > r || l > end) return make_pair(0, 0);
	int mid = l + (r - l) / 2;
	if (start <= l && r <= end) {
		if (l == r) { 
			return make_pair(tree[index].value, l);
		}
		if (tree[index * 2].value >= tree[index * 2 + 1].value) {
			return query(start, end, l, mid, index * 2);
		}
		return query(start, end, mid + 1, r, index * 2 + 1);
	}
	
	return max(query(start, end, l, mid, index * 2), query(start, end, mid + 1, r, index * 2 + 1));
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
	
	int mid = l + (r - l) / 2;
	update(start, end, l, mid, index * 2, val);
	update(start, end, mid + 1, r, index * 2 + 1, val);
	tree[index].value = max(tree[index * 2].value, tree[index * 2 + 1].value);
}

int U = 200000;

int main() {
	int n;
	ll k;
	scanf("%d%lld", &n, &k);
	int i;
	for (i = 1; i <= n; i++) {
		int l, r;
		ll p;
		scanf("%d%d%lld", &l, &r, &p);
		g[r].push_back(money{l, i, p});
	}
	
	for (i = 1; i <= U; i++) {
		update(1, i, 1, U, 1, -k);
		for (auto p : g[i]) {
			update(1, p.l, 1, U, 1, p.p);
			// cout << "update " << p.l << " by " << p.p << endl;
		}
		
		pair<ll, int> curr = query(1, i, 1, U, 1);
		//cout << i << "->" << curr.second << " " << curr.first << endl;
		if (curr.first > ans) {
			ans = curr.first;
			L = curr.second;
			R = i;
		}
	}
	
	if (ans == 0) {
		printf("0\n");
		return 0;
	}
	printf("%lld %d %d ", ans, L, R);
	vector<int> ret;
	for (i = 1; i <= R; i++) {
		for (auto p : g[i]) {
			if (p.l >= L) {
				ret.push_back(p.id);
			}
		}
	}
	
	printf("%d\n", (int) ret.size());
	for (auto p : ret) {
		printf("%d ", p);
	}
	printf("\n");
	return 0;
}
