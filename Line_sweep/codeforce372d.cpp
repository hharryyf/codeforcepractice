#include <bits/stdc++.h>
#define MAX_SIZE 262192
#define MID ((l+r)>>1)
#define LEFT (index << 1)
#define RIGHT (index << 1 | 1)
using namespace std;

vector<int> g[MAX_SIZE];
int visited[MAX_SIZE], parent[MAX_SIZE][19];
int son[MAX_SIZE], height[MAX_SIZE];
int id[MAX_SIZE], rid[MAX_SIZE], top[MAX_SIZE], sz[MAX_SIZE];
int cnt = 1;
// all active nodes visited[v]->v
map<int, int> mp;
int n;

struct rangetree {
	int tree[MAX_SIZE];
	int lz[MAX_SIZE];
	void pushdown(int l, int r, int index) {
		if (l > r) return;
		int mid = l + (r - l) / 2;
		int len1 = mid - l + 1;
		int len2 = r - mid;
		if (lz[index] != -1) {
			if (l != r) {
				tree[LEFT] = lz[index] * len1;
				tree[RIGHT] = lz[index] * len2;
				lz[LEFT] = lz[RIGHT] = lz[index];
			}
			lz[index] = -1;
		}
	}
	
	void update(int start, int end, int l, int r, int index, int val) {
		if (start > end || l > r || start > r || l > end) return;
		pushdown(l, r, index);
		if (start <= l && r <= end) {
			tree[index] = val * (r - l + 1);
			lz[index] = val;
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
		tree[index] = tree[LEFT] + tree[RIGHT];
	}
	
	int query(int start, int end, int l, int r, int index) {
		if (start > r || l > end || start > end || l > r) return 0;
		pushdown(l, r, index);
		if (start <= l && r <= end) return tree[index];
		if (end <= MID) {
			return query(start, end, l, MID, LEFT);
		}
		
		if (start >= MID + 1) {
			return query(start, end, MID + 1, r, RIGHT);
		}
		
		return query(start, end, l, MID, LEFT) + query(start, end, MID + 1, r, RIGHT);
	}
};

rangetree t1, t2;

int LCA(int u, int v) {
	if (height[u] < height[v]) swap(u, v);
	int i;
    for (i = 17; i >= 0; i--) {
   	    if (height[u] >= (1 << i) + height[v]) {
			u = parent[u][i];	  
	    }
    }
   
   if (u == v) return u;
   
   for (i = 17; i >= 0; i--) {
   	   if (parent[u][i] != parent[v][i]) {
			 u = parent[u][i];
			 v = parent[v][i];	  
	   }
   }
   
   return parent[u][0];
}

void dfs1(int v, int pre) {
	int i;
	height[v] = 1 + height[pre];
	parent[v][0] = pre;
	visited[v] = cnt++;
	sz[v] = 1;
	int max_child = 0;
	for (i = 1; i <= 17; ++i) {
		parent[v][i] = parent[parent[v][i-1]][i-1];
	}
	
	for (auto nv : g[v]) {
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
	
	for (auto nv : g[v]) {
		if (nv != parent[v][0] && nv != son[v]) {
		   dfs2(nv, nv);
		}
	}
}

void hld(int x, int y, int val) {
	//cout << "set " << x << " " << y << " to " << val << endl;
	int fx = top[x], fy = top[y];
	while (fx != fy) {
		  if (height[fx] >= height[fy]) {
			 t1.update(id[fx], id[x], 1, n, 1, val);
			 //cout << "set " << fx << " " << x << endl;
		  	 x = parent[fx][0], fx = top[x];
		  } else {
			 t1.update(id[fy], id[y], 1, n, 1, val);
			 //cout << "set " << fy << " " << y << endl;
		  	 y = parent[fy][0], fy = top[y];
		  }
	}	
	
	if (id[x] <= id[y]) {
	   t1.update(id[x], id[y], 1, n, 1, val);
	   //cout << "set " << x << " " << y << endl;
	} else {
	   t1.update(id[y], id[x], 1, n, 1, val);
	   //cout << "set " << y << " " << x << endl;
	}
}
// remove vertex x from the tree
void remove(int x) {
	int lca = LCA(mp.begin()->second, mp.rbegin()->second);
	mp.erase(visited[x]);
	t2.update(visited[x], visited[x], 1, n, 1, 0);
	int lca2 = LCA(mp.begin()->second, mp.rbegin()->second);
	int i, u = x;
	for (i = 17; i >= 0; --i) {
		int l = visited[parent[u][i]], r = sz[parent[u][i]] + visited[parent[u][i]] - 1;
		if (height[u] > (1 << i) + height[lca]) {
			if (t2.query(l, r, 1, n, 1) == 0) {
				u = parent[u][i];
			}
		}
	}
	
	if (u != x) {
		hld(u, x, 0);
		//cout << "clear " << u << " " << x << endl;
	} else if (t2.query(visited[u], visited[x] + sz[x] - 1, 1, n, 1) == 0) {
		hld(u, x, 0);
	}
	
	if (lca2 != lca) {
		hld(parent[lca2][0], lca, 0);
		// cout << "clear " << parent[lca2][0] << " " << lca << endl;
	}
	//cout << "remove result " << t1.tree[1] << endl;
}

void add(int x) {
	int l = (x == 1 ? 1 : x - 1);
	hld(l, x, 1);
	mp[visited[x]] = x;
	t2.update(visited[x], visited[x], 1, n, 1, 1);
}

int main() {
	int i, k, l = 1, ans = 0;
	
	for (i = 1; i < MAX_SIZE; ++i) t1.lz[i] = t2.lz[i] = -1;
	
	scanf("%d%d", &n, &k);
	for (i = 1; i < n; ++i) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		g[v1].push_back(v2);
		g[v2].push_back(v1);
	}
	
	dfs1(1, 0);
	cnt = 1;
	dfs2(1, 1);
	for (i = 1; i <= n; ++i) {
		add(i);
		//cout << "add " << i << endl;
		//cout << "query " << t1.tree[1] << endl;
		while (t1.tree[1] > k) {
			// cout << "remove " << l << endl; 
			remove(l++);
		}
		ans = max(ans, i - l + 1);
		// cout << l << " " << i << " " << t1.tree[1] << endl;
	}
	printf("%d\n", ans);
	return 0;
}