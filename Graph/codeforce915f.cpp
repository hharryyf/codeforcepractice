#include <bits/stdc++.h>
#define MAX_SIZE 1000111
using namespace std;
typedef long long ll;

struct node {
	int id, v;
};

int f[MAX_SIZE], sz[MAX_SIZE];
int value[MAX_SIZE];
vector<int> g[MAX_SIZE];
// the tree established after we run the kruskal modification algorithm
vector<int> tree[MAX_SIZE];
node nd[MAX_SIZE];
int n;
ll ans;

static bool cmp1(const node &a, const node &b) {
	return a.v != b.v ? a.v < b.v : a.id < b.id;
}

static bool cmp2(const node &a, const node &b) {
	return a.v != b.v ? a.v > b.v : a.id > b.id;
}

int find(int x) {
	return f[x] == x ? x : f[x] = find(f[x]);
}

void init() {
	int i;
	for (i = 0 ; i < MAX_SIZE; ++i) {
		tree[i].clear();
		f[i] = i;
	}
}

void dfs(int v) {
	sz[v] = 1;
	ans += 1ll * value[v] * sz[v];
	for (auto nv : tree[v]) {
		dfs(nv);
		ans += 1ll * sz[v] * sz[nv] * value[v];
		sz[v] += sz[nv];
	}
}

ll kruskal_modification(int tp) {
	int i;
	init();
	ans = 0;
	// tp=0 means we create the "max heap", tp=1 means we create the "min heap"
	if (tp == 0) {
		sort(nd + 1, nd + 1 + n, cmp2);
	} else {
		sort(nd + 1, nd + 1 + n, cmp1);
	}
	
	for (i = n; i >= 1; --i) {
		for (auto v : g[nd[i].id]) {
			if (tp == 0) {
				if (nd[i].v > value[v] || (nd[i].v == value[v] && nd[i].id > v)) {
					v = find(v);
					f[v] = nd[i].id;
					tree[nd[i].id].push_back(v);
					// cout << "addedge " << nd[i].id << " " << v << endl;
				}
			} else {
				if (nd[i].v < value[v] || (nd[i].v == value[v] && nd[i].id < v)) {
					v = find(v);
					f[v] = nd[i].id;
					tree[nd[i].id].push_back(v);
					// cout << "Addedge " << nd[i].id << " " << v << endl;
				}
			}
		}
	}
	
	dfs(nd[1].id);
	return ans;
}

int main() {
	int i;
	ll ret = 0;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) {
		scanf("%d", &value[i]);
		nd[i].id = i, nd[i].v = value[i];
	}
	
	for (i = 1; i < n; ++i) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		g[v1].push_back(v2);
		g[v2].push_back(v1);
	}
	
	ret += kruskal_modification(0);
	ret -= kruskal_modification(1);
	printf("%I64d\n", ret);
	return 0;
}