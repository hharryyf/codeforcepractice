#include <bits/stdc++.h>
#define MAX_SIZE 262192
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
using namespace std;

const int inf = 1 << 29;

struct rangetree {
    struct segt {
        int rmin, rmax, lz;
    };

    segt tree[MAX_SIZE];

    void init() {
        for (int i = 0 ; i < MAX_SIZE; ++i) tree[i].lz = inf;
    }

    void pushdown(int l, int r, int index) {
        if (l > r) return;
        if (tree[index].lz != inf) {
            if (l != r) {
                tree[LEFT].lz = tree[index].lz;
                tree[RIGHT].lz = tree[index].lz;
                tree[LEFT].rmin = tree[LEFT].rmax = tree[index].lz;
                tree[RIGHT].rmin = tree[RIGHT].rmax =  tree[index].lz;
            }       
        }
        tree[index].lz = inf;
    }

    segt pullup(segt t1, segt t2) {
        segt ret;
        ret.lz = inf;
        ret.rmax = max(t1.rmax, t2.rmax);
        ret.rmin = min(t1.rmin, t2.rmin);
        return ret;
    }

    void update(int start, int end, int l, int r, int index, int val) {
        // cout << "update " << start << " " << end << endl;
        if (start > end || l > r || start > r || l > end) return;
        pushdown(l, r, index);
        if (start <= l && r <= end) {
            tree[index].rmin = tree[index].rmax = val;
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

        tree[index] = pullup(tree[LEFT], tree[RIGHT]);
    }

    segt query(int start, int end, int l, int r, int index) {
        // cout << "query " << start << " " << end << endl;
        if (start > end || l > r || start > r || l > end) return tree[0];
        pushdown(l, r, index);
        if (start <= l && r <= end) return tree[index];
        if (end <= MID) {
            return query(start, end, l, MID, LEFT);
        } else if (start >= MID + 1) {
            return query(start, end, MID + 1, r, RIGHT);
        } 
        return pullup(query(start, end, l, MID, LEFT), query(start, end, MID + 1, r, RIGHT));
    }
};


rangetree tree;
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
int n, Q;

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

bool hld(int x, int y) {
	pair<int, int> ret = {inf, -inf};
	int fx = top[x], fy = top[y];
	while (fx != fy) {
		if (depth[fx] >= depth[fy]) {
		    auto curr = tree.query(id[fx], id[x], 1, n, 1);
            ret.first = min(ret.first, curr.rmin);
            ret.second = max(ret.second, curr.rmax);
		    x = parent[fx], fx = top[x];
		} else {
            auto curr = tree.query(id[fy], id[y], 1, n, 1);
            ret.first = min(ret.first, curr.rmin);
            ret.second = max(ret.second, curr.rmax);
            y = parent[fy], fy = top[y];
		}  
	}
	if (id[x] <= id[y]) {
	    auto curr = tree.query(id[x], id[y], 1, n, 1);
        ret.first = min(ret.first, curr.rmin);
        ret.second = max(ret.second, curr.rmax);
    } else {
        auto curr = tree.query(id[y], id[x], 1, n, 1);
        ret.first = min(ret.first, curr.rmin);
        ret.second = max(ret.second, curr.rmax);
	}

    return ret.first == ret.second;
}
// change all edge's weight from x->y to min(original weight, v)
void change(int x, int y, int v) {
    int fx = top[x], fy = top[y];
	while (fx != fy) {
		if (depth[fx] >= depth[fy]) {
		    tree.update(id[fx], id[x], 1, n, 1, v);
		    x = parent[fx], fx = top[x];
		} else {
            tree.update(id[fy], id[y], 1, n, 1, v);
            y = parent[fy], fy = top[y];
		}  
	}
    
    if (id[x] <= id[y]) {
	   tree.update(id[x], id[y], 1, n, 1, v);
	} else {
	   tree.update(id[y], id[x], 1, n, 1, v);
	}
}

int LCA(int x, int y) {
    int fx = top[x], fy = top[y];
    while (fx != fy) {
		if (depth[fx] >= depth[fy]) {
		    x = parent[fx], fx = top[x];
		} else {
            y = parent[fy], fy = top[y];
		}  
	}
    if (x == y) return x;
    if (depth[x] < depth[y]) return x;
    return y;
}

int dist(int u, int v) {
    return depth[v] + depth[u] - 2 * depth[LCA(u, v)];
}

struct edge {
    int from, to, d;
    bool operator < (edge other) const {
        return d > other.d;
    }
};

edge edg[MAX_SIZE];

int main() {
    int i;
    scanf("%d%d", &n, &Q);
    for (i = 0 ; i < n - 1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    tree.init();
    dfs1(1, 0);
    dfs2(1, 1);
    for (i = 0 ; i < Q; ++i) {
        scanf("%d%d", &edg[i].from, &edg[i].to);
        edg[i].d = dist(edg[i].from, edg[i].to);
    }

    sort(edg, edg + Q);

    for (i = 0 ; i < Q; ++i) {
        if (!hld(edg[i].from, edg[i].to)) {
            printf("No\n");
            return 0;
        }
        change(edg[i].from, edg[i].to, i + 1);
    }

    printf("Yes\n");
    return 0;
}