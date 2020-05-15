#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 1048597
#define MID ((l+r)>>1)
#define LEFT (index << 1)
#define RIGHT (index << 1 | 1)
using namespace std;
typedef long long ll;

const int inf = 1 << 30;

struct rangemaxtree {
    struct segt {
        int value, lz;
    };

    segt tree[MAX_SIZE];

    void init() {
        int i;
        for (i = 0 ; i < MAX_SIZE; ++i) {
            tree[i].lz = inf;
            tree[i].value = 0;
        }
    }
 
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

rangemaxtree tree;

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

struct edge {
    int from, to, weight;
    bool select;
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
	
    if (x == y) return;
	if (id[x] <= id[y]) {
	   tree.update(id[son[x]], id[y], 1, n, 1, v);
	} else {
	   tree.update(id[son[y]], id[x], 1, n, 1, v);
	}
}

int f[MAX_SIZE];

int find(int x) {
    if (x == f[x]) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int a = find(x), b = find(y);
    f[a] = b;
}

void init() {
    int i;
    for (i = 0 ; i < MAX_SIZE; ++i) f[i] = i;
    tree.init();
}

int wt[MAX_SIZE];

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        tree.tree[index].value = wt[rid[l]];
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    tree.tree[index].value = max(tree.tree[LEFT].value, tree.tree[RIGHT].value);
}

ll getsum(int l, int r, int index) {
    if (l > r) return 0ll;
    tree.pushdown(l, r, index);
    if (l == r) {
        return tree.tree[index].value;
    }

    return 1ll * getsum(l, MID, LEFT) + 1ll * getsum(MID + 1, r, RIGHT);
}

int main() {
    int k, m, i;
    scanf("%d%d%d", &n, &k, &m);
    init();
    for (i = 1; i <= k; ++i) {
        scanf("%d%d", &edg[i].from, &edg[i].to);
        edg[i].weight = inf - 1;
        edg[i].select = true;
        unionset(edg[i].from, edg[i].to);
        g[edg[i].from].push_back(edg[i].to);
        g[edg[i].to].push_back(edg[i].from);
    }

    for (i = 1; i <= m; ++i) {
        scanf("%d%d%d", &edg[i+k].from, &edg[i+k].to, &edg[i+k].weight);
        if (find(edg[i + k].from) != find(edg[i + k].to)) {
            unionset(edg[i + k].from, edg[i + k].to);
            edg[i + k].select = true;
            g[edg[i+k].from].push_back(edg[i+k].to);
            g[edg[i+k].to].push_back(edg[i+k].from);
        }
    }
    
    dfs1(1, 0);
    dfs2(1, 1);
    ll ret = 0;
    for (i = 1; i <= m + k; ++i) {
        if (edg[i].select) {
            if (parent[edg[i].from] == edg[i].to) {
                wt[edg[i].from] = edg[i].weight;
            } else {
                wt[edg[i].to] = edg[i].weight;
            }
            if (i > k) {
                ret += edg[i].weight;
            }
        }
    }

    build(1, n, 1);

    for (i = 1; i <= m + k; ++i) {
        if (!edg[i].select) {
            change(edg[i].from, edg[i].to, edg[i].weight);
        }
    }

    if (tree.tree[1].value > 1e9) {
        printf("-1\n");
        return 0;
    }

    printf("%I64d\n", getsum(1, n, 1) - ret);
    return 0;
}