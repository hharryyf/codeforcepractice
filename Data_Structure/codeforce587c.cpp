#include <bits/stdc++.h>
#define INF 1000000007
#define MAX_SIZE 262192
typedef long long ll;
using namespace std;

int n, m, q;

vector<int> g[MAX_SIZE];
// id means the dfs order in the HLD of a node
// rid means the reverse of the id, i.e. v = rid[id[v]]
int id[MAX_SIZE], rid[MAX_SIZE];
// son is the heavy child of a node, son[i] = 0 if i is a leaf
int son[MAX_SIZE], parent[MAX_SIZE];
// top means the top node of the current heavy link
int top[MAX_SIZE], depth[MAX_SIZE];
// sz means the subtree size, use to determine the heavy child
int sz[MAX_SIZE];
// the range min segment tree
int tree[MAX_SIZE];
// record the id in the root node
set<int> st[MAX_SIZE];
int cnt = 0;

void dfs1(int v, int pre) {
	 parent[v] = pre;
	 depth[v] = depth[pre] + 1;
	 sz[v] = 1;
	 int max_subsz = 0;
	 for (auto nv : g[v]) {
	 	 if (nv != pre) {
         	dfs1(nv, v);
         	sz[v] += sz[nv];
         	if (max_subsz < sz[nv]) {
			   son[v] = nv, max_subsz = sz[nv]; 
	        }
		 }
	 }
}

void dfs2(int v, int tp) {
	 top[v] = tp, id[v] = ++cnt, rid[id[v]] = v;
	 if (son[v]) {
	 	dfs2(son[v], tp);
	 }
	 
	 for (auto nv : g[v]) {
	 	 if (nv != parent[v] && nv != son[v]) {
		 	dfs2(nv, nv); 
         }
	 }
}

void update(int pos, int l, int r, int index, int val, int tp) {
	 if (pos < l || pos > r || l > r) return;
	 if (pos == l && l == r) {
	 	// 1 means insert, 2 means delete
	    if (tp == 1) {
		   st[l].insert(val);
		   tree[index] = *st[l].begin();
	    } else {
		   st[l].erase(val);
		   if (st[l].empty()) {
		   	  tree[index] = INF;
		   } else {
		   	  tree[index] = *st[l].begin();
		   }  
		}
	 	return;
	 }
	 
	 int mid = (l+r) >> 1;
	 if (pos <= mid) {
	 	update(pos, l, mid, index * 2, val, tp);
	 } else {
	    update(pos, mid + 1, r, index * 2 + 1, val, tp);
	 }
	 
	 tree[index] = min(tree[index * 2], tree[index * 2 + 1]);
}
// return the range_min and index
pair<int, int> query(int start, int end, int l, int r, int index) {
     if (start > end || l > r || start > r || l > end) return make_pair(INF, -1);
     int mid = (l + r) >> 1;
	 if (start <= l && r <= end) {
	 	if (l == r) return make_pair(tree[index], l);
	 	if (tree[index * 2] <= tree[index * 2 + 1]) return query(start, end, l, mid, index * 2);
	 	return query(start, end, mid + 1, r, index * 2 + 1);
	 }
	 
	 if (end <= mid) return query(start, end, l, mid, index * 2);
	 if (start >= mid + 1) return query(start, end, mid + 1, r, index * 2 + 1);
	 return min(query(start, end, l, mid, index * 2), query(start, end, mid + 1, r, index * 2 + 1));
}

// query the minimum vertex weight from x to y and the vertex id
pair<int, int> hld(int x, int y) {
	pair<int, int> ret = {INF, -1};
	int fx = top[x], fy = top[y];
	while (fx != fy) {
		if (depth[fx] >= depth[fy]) {
		    ret = min(ret, query(id[fx], id[x], 1, n, 1));
		    x = parent[fx], fx = top[x];
		} else {
            ret = min(ret, query(id[fy], id[y], 1, n, 1));
            y = parent[fy], fy = top[y];
		}  
	}
	
	if (id[x] <= id[y]) {
	   ret = min(ret, query(id[x], id[y], 1, n, 1));
	} else {
	   ret = min(ret, query(id[y], id[x], 1, n, 1));
	}
	return ret;
}

int main() {
	int i;
	scanf("%d%d%d", &n, &m, &q);
	for (i = 1; i < MAX_SIZE; i++) tree[i] = INF;
	for (i = 1; i < n; i++) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		g[v1].push_back(v2), g[v2].push_back(v1);
	}
	
	dfs1(1, 0);
	dfs2(1, 1);
	for (i = 1; i <= m; i++) {
		int v;
		scanf("%d", &v);
		update(id[v], 1, n, 1, i, 1);
	}
	
	while (q > 0) {
		int v1, v2, k;
		scanf("%d%d%d", &v1, &v2, &k);
		vector<pair<int, int> > ans;
		for (i = 0 ; i < k; i++) {
			pair<int, int> ret = hld(v1, v2);
			if (ret.first != INF) {
			   ans.emplace_back(ret.first, ret.second);
			   update(ret.second, 1, n, 1, ret.first, 2);
			} else {
			   break;
			}
		}  
		
		printf("%d", (int) ans.size());
		for (auto np : ans) {
			printf(" %d", np.first);
			update(np.second, 1, n, 1, np.first, 1);
		}
		printf("\n");
		
        q--;
	}
	return 0;
}

