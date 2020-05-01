#include <bits/stdc++.h>
#define MAX_SIZE 524292
#define MID ((l+r)>>1)
#define LEFT (index << 1)
#define RIGHT (index << 1 | 1)
using namespace std;

const int inf = (1<<30);

struct rangemaxtree {
    struct segt {
        int value, lz;
    };

    segt tree[MAX_SIZE];

    void pushdown(int l, int r, int index) {
        if (l > r) return;
        if (tree[index].lz != inf) {
            if (l != r) {
                tree[LEFT].lz = min(tree[LEFT].lz, tree[index].lz);
                tree[RIGHT].lz = min(tree[RIGHT].lz, tree[index].lz);
                tree[LEFT].value = min(tree[LEFT].value, tree[index].lz);
                tree[RIGHT].value = min(tree[RIGHT].value, tree[index].lz);
            }       
        }
        tree[index].lz = inf;
    }

    void update(int start, int end, int l, int r, int index, int val) {
        if (start > end || l > r || start > r || l > end) return;
        pushdown(l, r, index);
        if (start <= l && r <= end) {
            tree[index].value = min(tree[index].value, val);
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
        tree[index].value = max(tree[LEFT].value, tree[RIGHT].value);
    }

    int query(int start, int end, int l, int r, int index) {
        if (start > end || l > r || start > r || l > end) return -inf;
        pushdown(l, r, index);
        if (start <= l && r <= end) return tree[index].value;
        if (end <= MID) {
            return query(start, end, l, MID, LEFT);
        } else if (start >= MID + 1) {
            return query(start, end, MID + 1, r, RIGHT);
        } 
        return max(query(start, end, l, MID, LEFT), query(start, end, MID + 1, r, RIGHT));
    }
};
// t1 maintains the range max of the mst-edges, t2 is used for updates
rangemaxtree t1, t2;
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
int cnt = 0;
int n;

int f[MAX_SIZE];

void init() {
    int i;
    for (i = 0 ; i < MAX_SIZE; ++i) {
        t1.tree[i].lz = t2.tree[i].lz 
        = t1.tree[i].value = t2.tree[i].value = inf;
        f[i] = i;
    }
}

int find(int x) {
    if (f[x] == x) return f[x];
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int a = find(x), b = find(y);
    f[a] = b;
}

struct edge {
    int from, to, w, id, select;
    bool operator < (edge other) const {
        return w < other.w;
    }
};

edge edg[MAX_SIZE];

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

int hld(int x, int y) {
	int ret = -inf;
	int fx = top[x], fy = top[y];
	while (fx != fy) {
		if (depth[fx] >= depth[fy]) {
		    ret = max(ret, t1.query(id[fx], id[x], 1, n, 1));
		    x = parent[fx], fx = top[x];
		} else {
            ret = max(ret, t1.query(id[fy], id[y], 1, n, 1));
            y = parent[fy], fy = top[y];
		}  
	}
	
    if (x == y) return ret;
	if (id[x] <= id[y]) {
	   ret = max(ret, t1.query(id[son[x]], id[y], 1, n, 1));
	} else {
	   ret = max(ret, t1.query(id[son[y]], id[x], 1, n, 1));
	}
	return ret;
}
// change all edge's weight from x->y to min(original weight, v)
void change(int x, int y, int v) {
    int fx = top[x], fy = top[y];
	while (fx != fy) {
		if (depth[fx] >= depth[fy]) {
		    t2.update(id[fx], id[x], 1, n, 1, v);
		    x = parent[fx], fx = top[x];
		} else {
            t2.update(id[fy], id[y], 1, n, 1, v);
            y = parent[fy], fy = top[y];
		}  
	}
	
    if (x == y) return;
	if (id[x] <= id[y]) {
	   t2.update(id[son[x]], id[y], 1, n, 1, v);
	} else {
	   t2.update(id[son[y]], id[x], 1, n, 1, v);
	}
}

int ans[MAX_SIZE];
int wt[MAX_SIZE];

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        t1.tree[index].value = wt[rid[l]];
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    t1.tree[index].value = max(t1.tree[LEFT].value, t1.tree[RIGHT].value);
}

int main() {
    init();
    int m, i;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; ++i) {
        scanf("%d%d%d", &edg[i].from, &edg[i].to, &edg[i].w);
        edg[i].id = i;
    }

    sort(edg + 1, edg + 1 + m);

    for (i = 1; i <= m; ++i) {
        if (find(edg[i].from) != find(edg[i].to)) {
            edg[i].select = 1;
            unionset(edg[i].from, edg[i].to);
            g[edg[i].from].push_back(edg[i].to);
            g[edg[i].to].push_back(edg[i].from);
            // cout << "edge: " << edg[i].from << " " << edg[i].to << endl;
        }
    }

    dfs1(1, 0);
    dfs2(1, 1);

    for (i = 1; i <= m; ++i) {
        if (edg[i].select == 1) {
            if (depth[edg[i].from] > depth[edg[i].to]) swap(edg[i].from, edg[i].to);
            wt[edg[i].to] = edg[i].w;
        }
    }

    build(1, n, 1);

    for  (i = 1; i <= m; ++i) {
        // this edge is not in the mst, the way to make it in all mst
        // is to make it smaller than the largest edge in the mst from edg[i].from, to edg[i].to
        if (edg[i].select == 0) {
            ans[edg[i].id] = hld(edg[i].from, edg[i].to) - 1;
            change(edg[i].from, edg[i].to, edg[i].w - 1);
        }
    }

    for (i = 1; i <= m; ++i) {
        if (edg[i].select == 1) {
            ans[edg[i].id] = t2.query(id[edg[i].to], id[edg[i].to], 1, n, 1);
            if (ans[edg[i].id] >= inf) {
                ans[edg[i].id] = -1;
            }
        }
    }
    
    for (i = 1; i <= m; ++i) {
        printf("%d ", ans[i]);
    }
    printf("\n");
    return 0;
}