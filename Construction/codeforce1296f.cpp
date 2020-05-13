#include <bits/stdc++.h>
#define MAX_SIZE 16394
#define MID ((l+r)>>1)
#define LEFT (index << 1)
#define RIGHT (index << 1 | 1)
using namespace std;

struct rangetree {
    struct segt {
        int value, lz;
    };

    segt tree[MAX_SIZE];

    void pushdown(int l, int r, int index) {
        if (l > r) return;
        if (tree[index].lz != 0) {
            if (l != r) {
                tree[LEFT].lz = max(tree[LEFT].lz, tree[index].lz);
                tree[RIGHT].lz = max(tree[RIGHT].lz, tree[index].lz);
                tree[LEFT].value = max(tree[LEFT].value, tree[index].lz);
                tree[RIGHT].value = max(tree[RIGHT].value, tree[index].lz);
            }       
        }
        tree[index].lz = 0;
    }

    void update(int start, int end, int l, int r, int index, int val) {
        if (start > end || l > r || start > r || l > end) return;
        pushdown(l, r, index);
        if (start <= l && r <= end) {
            tree[index].value = max(tree[index].value, val);
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
        tree[index].value = min(tree[LEFT].value, tree[RIGHT].value);
    }

    int query(int start, int end, int l, int r, int index) {
        if (start > end || l > r || start > r || l > end) return 0;
        pushdown(l, r, index);
        if (start <= l && r <= end) return tree[index].value;
        if (end <= MID) {
            return query(start, end, l, MID, LEFT);
        } else if (start >= MID + 1) {
            return query(start, end, MID + 1, r, RIGHT);
        } 
        return min(query(start, end, l, MID, LEFT), query(start, end, MID + 1, r, RIGHT));
    }
};

rangetree tree;
// v->edge id
vector<pair<int, int>> g[MAX_SIZE];
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

void dfs1(int v, int pre) {
	 parent[v] = pre;
	 depth[v] = depth[pre] + 1;
	 sz[v] = 1;
	 int max_subsz = 0;
	 for (auto np : g[v]) {
         int nv = np.first;
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
	 
	 for (auto np : g[v]) {
         int nv = np.first;
	 	 if (nv != parent[v] && nv != son[v]) {
		 	dfs2(nv, nv); 
         }
	 }
}

int hld(int x, int y) {
	int ret = 1e6;
	int fx = top[x], fy = top[y];
	while (fx != fy) {
		if (depth[fx] >= depth[fy]) {
		    ret = min(ret, tree.query(id[fx], id[x], 1, n, 1));
		    x = parent[fx], fx = top[x];
		} else {
            ret = min(ret, tree.query(id[fy], id[y], 1, n, 1));
            y = parent[fy], fy = top[y];
		}  
	}
	
    if (x == y) return ret;
	if (id[x] <= id[y]) {
	   ret = min(ret, tree.query(id[son[x]], id[y], 1, n, 1));
	} else {
	   ret = min(ret, tree.query(id[son[y]], id[x], 1, n, 1));
	}
	return ret;
}
// change all edge's weight from x->y to max(original weight, v)
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
	
    if (x == y) return;
	if (id[x] <= id[y]) {
	   tree.update(id[son[x]], id[y], 1, n, 1, v);
	} else {
	   tree.update(id[son[y]], id[x], 1, n, 1, v);
	}
}

pair<int, pair<int, int>> qrs[MAX_SIZE];

void fix(int v, int pre) {
    for (auto np : g[v]) {
        int nv = np.first;
        if (nv != pre) {
            if (hld(v, nv) == 0) {
                change(v, nv, 1e6);
            }
            fix(nv, v);
        }
    }
}

int ans[MAX_SIZE];

void fillans(int v, int pre) {
    for (auto np : g[v]) {
        int nv = np.first;
        if (nv != pre) {
            ans[np.second] = hld(nv, v);
            fillans(nv, v);
        }
    }
}

int main() {
    int q, i;
    scanf("%d", &n);
    for (i = 1; i < n; ++i) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        g[v1].emplace_back(v2, i);
        g[v2].emplace_back(v1, i);
    }

    dfs1(1, 0);
    dfs2(1, 1);

    scanf("%d", &q);
    for (i = 0 ; i < q; ++i) {
        scanf("%d%d%d", &qrs[i].second.first, &qrs[i].second.second, &qrs[i].first);
    }

    sort(qrs, qrs + q);

    for (i = 0 ; i < q; ++i) {
        change(qrs[i].second.first, qrs[i].second.second, qrs[i].first);
    }
    
    fix(1, 0);

    for (i = 0 ; i < q; ++i) {
        if (hld(qrs[i].second.first, qrs[i].second.second) != qrs[i].first) {
            printf("-1\n");
            return 0;
        }
    }

    fillans(1, 0);

    for (i = 1; i < n; ++i) {
        printf("%d ", ans[i]);
    }
    printf("\n");
    return 0;
}