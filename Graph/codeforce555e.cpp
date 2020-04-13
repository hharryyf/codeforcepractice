#include <bits/stdc++.h>
#define MAX_SIZE 524292
#define MID ((l+r)>>1)
#define LEFT (index << 1)
#define RIGHT (index << 1 | 1)
using namespace std;

int f[MAX_SIZE];

int find(int x) {
	return f[x] == x ? x : f[x] = find(f[x]);
}

void unionset(int a, int b) {
	int x = find(a), y = find(b);
	f[x] = y;
}


struct segt {
	int lz, rmax, rmin;
};

segt tree[MAX_SIZE];

void pushdown(int l, int r, int index) {
	if (l > r) return;
	if (tree[index].lz != 0) {
		if (l != r) {
			tree[LEFT].rmin = tree[LEFT].rmax = tree[RIGHT].rmin 
			                = tree[RIGHT].rmax = tree[LEFT].lz 
							= tree[RIGHT].lz = tree[index].lz;
		}
		tree[index].lz = 0;
	}
}

void update(int start, int end, int l, int r, int index, int val) {
	if (start > end || l > r || start > r || l > end) return;
	pushdown(l, r, index);
	if (start <= l && r <= end) {
		tree[index].rmax = val;
		tree[index].rmin = val;
		tree[index].lz = val;
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
	tree[index].rmax = max(tree[LEFT].rmax, tree[RIGHT].rmax);
	tree[index].rmin = min(tree[LEFT].rmin, tree[RIGHT].rmin);
}

pair<int, int> query(int start, int end, int l, int r, int index) {
	if (start > end || l > r || start > r || l > end) {
		return make_pair(-1, 1);
	} 
	
	pushdown(l, r, index);
	if (start <= l && r <= end) return make_pair(tree[index].rmax, tree[index].rmin);
	if (end <= MID) {
		return query(start, end, l, MID, LEFT);
	}
	
	if (start >= MID + 1) {
		return query(start, end, MID + 1, r, RIGHT);
	}
	
	auto p1 = query(start, end, l, MID, LEFT);
	auto p2 = query(start, end, MID + 1, r, RIGHT);
	return make_pair(max(p1.first, p2.first), min(p1.second, p2.second));
}

int parent[MAX_SIZE][19];
int son[MAX_SIZE], height[MAX_SIZE];
int id[MAX_SIZE], rid[MAX_SIZE], top[MAX_SIZE], sz[MAX_SIZE];
int visited[MAX_SIZE], low[MAX_SIZE], cmpid[MAX_SIZE];
// (v,edge_id) since we have parallel edges
// we should modify the tarjan's bcc algorithm a little bit
vector<pair<int, int>> g[MAX_SIZE];
unordered_set<int> h[MAX_SIZE];
int instack[MAX_SIZE];
stack<int> st;
int cnt = 1, cid = 1;

int LCA(int u, int v) {
	if (height[u] < height[v]) swap(u, v);
	int i;
    for (i = 18; i >= 0; i--) {
   	    if (height[u] >= (1 << i) + height[v]) {
			u = parent[u][i];	  
	    }
    }
   
   if (u == v) return u;
   
   for (i = 18; i >= 0; i--) {
   	   if (parent[u][i] != parent[v][i]) {
			 u = parent[u][i];
			 v = parent[v][i];	  
	   }
   }
   
   return parent[u][0];
}

int kthparent(int u, int k) {
	if (k == 0) return u;
	int i;
	for (i = 18; i >= 0; --i) {
		if (k >= (1 << i)) {
			u = parent[u][i];
			k -= (1 << i);
		}
	}
	return u;
}

void dfs(int v, int pd) {
	visited[v] = low[v] = cnt;
	cnt++;
	st.push(v);
	instack[v] = 1;
	for (auto np : g[v]) {
		int nv = np.first;
		if (np.second != pd) {
			if (!visited[nv]) {
				dfs(nv, np.second);
				low[v] = min(low[v], low[nv]);
			} else if (instack[nv]) {
				low[v] = min(low[v], visited[nv]);
			}
		}
	}
	
	if (low[v] == visited[v]) {
		while (st.top() != v) {
			cmpid[st.top()] = cid;
			instack[st.top()] = 0;
			st.pop();
		}
		
		cmpid[st.top()] = cid;
		instack[st.top()] = 0;
		st.pop();
		cid++;
	}
}

void dfs1(int v, int pre) {
	int i;
	height[v] = 1 + height[pre];
	parent[v][0] = pre;
	sz[v] = 1;
	int max_child = 0;
	for (i = 1; i <= 18; ++i) {
		parent[v][i] = parent[parent[v][i-1]][i-1];
	}
	
	for (auto nv : h[v]) {
		if (nv != pre) {
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
	
	for (auto nv : h[v]) {
		if (nv != parent[v][0] && nv != son[v]) {
		   dfs2(nv, nv);
		}
	}
}

bool ok = true;
// if val = -1
// check if u to v has value 1
// set val to -1
// otherwise
// check if u to v has value -1
// set val to 1
void hld(int x, int y, int val) {
	int fx = top[x], fy = top[y];
	while (fx != fy) {
		  if (height[fx] >= height[fy]) {
			 auto p = query(id[fx], id[x], 1, cnt-1, 1);
			 if ((p.first == 1 && val == -1) || (p.second == -1 && val == 1)) {
				 ok = false;
				 return;
			 }
			 update(id[fx], id[x], 1, cnt-1, 1, val);
		  	 x = parent[fx][0], fx = top[x];
		  } else {
			 auto p = query(id[fy], id[y], 1, cnt-1, 1);
			 if ((p.first == 1 && val == -1) || (p.second == -1 && val == 1)) {
				 ok = false;
				 return;
			 }
			 update(id[fy], id[y], 1, cnt-1, 1, val);
		  	 y = f[fy], fy = top[y];
		  }
	}	
	
	if (id[x] <= id[y]) {
	   auto p = query(id[x], id[y], 1, cnt-1, 1);
	   if ((p.first == 1 && val == -1) || (p.second == -1 && val == 1)) {
			ok = false;
			return;
	   }
	   update(id[x], id[y], 1, cnt-1, 1, val);
	} else {
	   auto p = query(id[y], id[x], 1, cnt-1, 1);
	   if ((p.first == 1 && val == -1) || (p.second == -1 && val == 1)) {
			ok = false;
			return;
	   }
	   update(id[y], id[x], 1, cnt-1, 1, val);
	}
}

bool linkpath(int u, int v) {
	int lca = LCA(u, v);
	int u1 = -1, v1 = -1;
	if (u != lca) {
		u1 = kthparent(u, height[u] - height[lca] - 1);
	}
	
	if (v != lca) {
		v1 = kthparent(v, height[v] - height[lca] - 1);
	}
	
	if (u1 != -1) {
		hld(u, u1, -1);
	}
	
	if (v1 != -1) {
		hld(v, v1, 1);
	}
	return ok;
}

int main() {
	int i, n, m, q;
	scanf("%d%d%d", &n, &m, &q);
	for (i = 1; i <= n; ++i) {
		f[i] = i;
	}
	
	for (i = 1; i <= m; ++i) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		g[v1].emplace_back(v2, i);
		g[v2].emplace_back(v1, i);
		unionset(v1, v2);
	}
	
	for (i = 1; i <= n; ++i) {
		if (!visited[i]) {
			dfs(i, 0);
		}
	}
	
	for (i = 1; i <= n; ++i) {
		for (auto np : g[i]) {
			if (cmpid[np.first] != cmpid[i]) {
				h[cmpid[np.first]].insert(cmpid[i]);
				h[cmpid[i]].insert(cmpid[np.first]);
			}
		}
	}
	
	cnt = 1;
	for (i = 1; i < cid; ++i) {
		if (!id[i]) {
			dfs1(i, 0);
			dfs2(i, i);
		}
	}
	
	while (q > 0) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		if (find(v1) != find(v2)) {
			printf("NO\n");
			return 0;
		}
		
		if (!linkpath(cmpid[v1], cmpid[v2])) {
			printf("NO\n");
			return 0;
		}
		--q;
	}
	
	printf("YES\n");
	return 0;
}