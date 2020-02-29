#include <bits/stdc++.h>
#define MOD 1000000007
#define INF 3000000000000000000ll
#define MAX_SIZE 524292
typedef long long ll;
using namespace std;

int n;
ll wt[MAX_SIZE];
// we maintain a product tree but with a special multiplication type
ll tree[MAX_SIZE];
int id[MAX_SIZE], rid[MAX_SIZE], son[MAX_SIZE], sz[MAX_SIZE];
int parent[MAX_SIZE][18], top[MAX_SIZE], dep[MAX_SIZE], f[MAX_SIZE];
int cnt = 1;
vector<pair<int, ll> > g[MAX_SIZE];
struct edge {
	   int u, v;
	   ll w;
};

edge edg[MAX_SIZE];

ll mul(ll v1, ll v2) {
   return v1 >= INF / v2 ? INF : v1 * v2;
}

void build(int l, int r, int index) {
   if (l > r) return;
   if (l == r) {
   	  tree[index] = wt[rid[l]];
   	  return;
   }
   int mid = (l + r) >> 1;
   build(l, mid, index * 2);
   build(mid + 1, r, index * 2 + 1);
   tree[index] = mul(tree[index * 2], tree[index * 2 + 1]);
}

void update(int pos, int l, int r, int index, ll val) {
   if (pos < l || pos > r || l > r) return;
   if (l == r && pos == l) {
   	  tree[index] = val;
   	  return;
   }
   
   int mid = (l + r) >> 1;
   if (pos <= mid) {
   	  update(pos, l, mid, index * 2, val);
   } else {
   	  update(pos, mid + 1, r, index * 2 + 1, val);
   }
   tree[index] = mul(tree[index * 2], tree[index * 2 + 1]);
}

ll query(int start, int end, int l, int r, int index) {
   if (start > end || l > r || start > r || l > end) return 1ll;
   if (start <= l && r <= end) return tree[index];
   int mid = (l + r) >> 1;
   if (end <= mid) return query(start, end, l, mid, index * 2);
   if (start >= mid + 1) return query(start, end, mid + 1, r, index * 2 + 1);
   return mul(query(start, end, l, mid, index * 2), 
              query(start, end, mid + 1, r, index * 2 + 1));
}

void dfs1(int v, int pre) {
   dep[v] = dep[pre] + 1;
   f[v] = parent[v][0] = pre;
   int i;
   for (i = 1; i <= 17; i++) parent[v][i] = parent[parent[v][i-1]][i-1];
   sz[v] = 1;
   int max_child = 0;
   for (auto np : g[v]) {
   	   int nv = np.first;
	   if (nv != pre) {
	   	  wt[nv] = np.second;
	   	  dfs1(nv, v);
	   	  sz[v] += sz[nv];
	   	  if (sz[nv] > max_child) {
		  	 max_child = sz[nv];
		  	 son[v] = nv;
		  }
	   }
   }
}

void dfs2(int v, int tp) {
   top[v] = tp;
   id[v] = cnt++;
   rid[id[v]] = v;
   if (son[v]) {
   	  dfs2(son[v], tp);
   }
   
   for (auto np : g[v]) {
   	   int nv = np.first;
   	   if (nv != f[v] && nv != son[v]) {
	   	  dfs2(nv, nv);
	   }
   }
}

int LCA(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	int i;
	for (i = 17; i >= 0; i--) {
		if (dep[u] >= (1 << i) + dep[v]) u = parent[u][i];
	}
	
	if (u == v) return u;
	
	for (i = 17 ; i >= 0; i--) {
		if (parent[u][i] != parent[v][i]) {
		   u = parent[u][i], v = parent[v][i];
		}
	}
	return parent[u][0];
}

ll hld(int x, int y) {
   int lca = LCA(x, y);
   // cout << "lca= " << lca << endl;
   update(id[lca], 1, n, 1, 1);
   ll ret = 1ll;
   int fx = top[x], fy = top[y];
   while (fx != fy) {
   		 if (dep[fx] >= dep[fy]) {
		 	ret = mul(ret, query(id[fx], id[x], 1, n, 1));
			x = f[fx], fx = top[x];	
         } else {
		    ret = mul(ret, query(id[fy], id[y], 1, n, 1));
		    y = f[fy], fy = top[y];
		 } 
   }
   
   if (id[x] <= id[y]) {
   	  ret = mul(ret, query(id[x], id[y], 1, n, 1));
   } else {
   	  ret = mul(ret, query(id[y], id[x], 1, n, 1));
   }
   
   update(id[lca], 1, n, 1, wt[lca]);
   // cout << "ret= " << ret << endl;
   return ret;
}

int main() {
	int m, i;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n - 1; i++) {
		scanf("%d%d%lld", &edg[i].u, &edg[i].v, &edg[i].w);
		g[edg[i].u].emplace_back(edg[i].v, edg[i].w);
		g[edg[i].v].emplace_back(edg[i].u, edg[i].w);
	}
	
	dfs1(1, 0);
	dfs2(1, 1);
	wt[1] = 1ll;
	build(1, n, 1);
	
	while (m > 0) {
		  int tp;
		  scanf("%d", &tp);
		  if (tp == 1) {
		  	 int v1, v2;
		  	 ll y;
		  	 scanf("%d%d%lld", &v1, &v2, &y);
		  	 ll ret = hld(v1, v2);
		  	 printf("%lld\n", y / ret);
		  } else {
		  	 int vd;
		  	 ll w;
		  	 scanf("%d%lld", &vd, &w);
		  	 if (dep[edg[vd].v] < dep[edg[vd].u]) {
	         	update(id[edg[vd].u], 1, n, 1, w);
				wt[edg[vd].u] = w;	
			 } else {
			    update(id[edg[vd].v], 1, n, 1, w);
			 	wt[edg[vd].v] = w;
			 }
		  }
		  m--;
	}
	return 0;
}

