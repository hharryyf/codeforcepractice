#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 262192
typedef long long ll;
using namespace std;

// dfs order of nodes
int visited[MAX_SIZE], rid[MAX_SIZE];
// range min/max segment tree
struct segt {
	int rmin, rmax;   
};

segt tree[MAX_SIZE];
int cnt = 0;
int parent[MAX_SIZE][18], depth[MAX_SIZE];
vector<int> g[MAX_SIZE];
void dfs(int v, int pre) {
	 depth[v] = 1 + depth[pre];
	 parent[v][0] = pre;
	 int i;
	 for (i = 1; i < 18; i++) parent[v][i] = parent[parent[v][i-1]][i-1];
	 visited[v] = ++cnt;
	 rid[visited[v]] = v;
	 for (auto nv : g[v]) {
	 	 if (nv != pre) dfs(nv, v);
	 }
}

segt pullup(segt t1, segt t2) {
	 segt t;
	 t.rmax = max(t1.rmax, t2.rmax);
	 t.rmin = min(t1.rmin, t2.rmin);
	 return t;
}

void build(int l, int r, int index) {
	 if (l > r) return;
	 if (l == r) {
	 	tree[index].rmin = tree[index].rmax = visited[l];
	 	return;
	 }
	 
	 int mid = (l + r) >> 1;
	 build(l, mid, index * 2);
	 build(mid + 1, r, index * 2 + 1);
	 tree[index] = pullup(tree[index * 2], tree[index * 2 + 1]);
}

void update(int pos, int l, int r, int index, int val) {
	 if (l > r || pos < l || pos > r) return;
	 if (l == r && pos == l) {
	 	tree[index].rmax = tree[index].rmin = val;
	 	return;
	 }
	 
	 int mid = (l + r) >> 1;
	 if (pos <= mid) update(pos, l, mid, index * 2, val);
	 else update(pos, mid + 1, r, index * 2 + 1, val);
	 tree[index] = pullup(tree[index * 2], tree[index * 2 + 1]);
}

segt query(int start, int end, int l, int r, int index) {
	 if (start > end || l > r || start > r || l > end) return segt{0,0};
	 if (start <= l && r <= end) return tree[index];
	 int mid = l + (r - l) / 2;
	 if (end <= mid) {
	 	return query(start, end, l, mid, index * 2);
	 } else if (start >= mid + 1) {
	 	  return query(start, end, mid + 1, r, index * 2 + 1);
	 } 
	 return pullup(query(start, end, l, mid, index * 2), query(start, end, mid + 1, r, index * 2 + 1));
}

int LCA(int u, int v) {
	if (depth[u] < depth[v]) swap(u, v);
	int i;
	for (i = 17; i >= 0; i--) {
		if (depth[u] >= depth[v] + (1 << i)) u = parent[u][i];
	}
	
	if (u == v) return u;
	for (i = 17; i >= 0; i--) {
		if (parent[u][i] != parent[v][i]) {
		   u = parent[u][i], v = parent[v][i];
		}
	}
	return parent[u][0];
}

int main() {
	int i, n, q;
	scanf("%d%d", &n, &q);
	for (i = 2 ; i <= n; ++i) {
		int v;
		scanf("%d", &v);
		g[v].push_back(i);
		g[i].push_back(v);
	}
	
	dfs(1, 0);
	
	build(1, n, 1);
	
	while (q > 0) {
		  int l, r;
		  scanf("%d%d", &l, &r);
		  // return the range max dfs ord and range min dfs ord
		  segt ret = query(l, r, 1, n, 1);
		  // cout << ret.rmin << "-----" << ret.rmax << endl;
		  // update the range max to range min and check the LCA
		  update(rid[ret.rmax], 1, n, 1, ret.rmin);
		  segt c1 = query(l, r, 1, n, 1);
		  update(rid[ret.rmax], 1, n, 1, ret.rmax);
		  update(rid[ret.rmin], 1, n, 1, ret.rmax);
		  segt c2 = query(l, r, 1, n, 1);
		  update(rid[ret.rmin], 1, n, 1, ret.rmin);
		  int v1 = LCA(rid[c1.rmin], rid[c1.rmax]), v2 = LCA(rid[c2.rmin], rid[c2.rmax]);
		  if (depth[v1] < depth[v2]) {
		  	 printf("%d %d\n", rid[ret.rmin], depth[v2] - 1);
		  } else {
		  	 printf("%d %d\n", rid[ret.rmax], depth[v1] - 1);
		  }
		  q--;
	}
	return 0;
}

