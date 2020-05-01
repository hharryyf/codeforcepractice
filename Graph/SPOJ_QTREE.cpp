#include <bits/stdc++.h>
#define MAX_SIZE 40011
#define MID ((l+r)>>1)
#define LEFT (index << 1)
#define RIGHT (index << 1 | 1)
using namespace std;

const int inf = (1<<28);

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
// the range max segment tree
int tree[MAX_SIZE];
int cnt = 0;
int n;

int query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return -inf;
    if (start <= l && r <= end) return tree[index];
    if (end <= MID) {
        return query(start, end, l, MID, LEFT);
    }

    if (start >= MID + 1) {
        return query(start, end, MID + 1, r, RIGHT);
    }

    return max(query(start, end, l, MID, LEFT), 
              query(start, end, MID + 1, r, RIGHT));
}

void update(int pos, int l, int r, int index, int val) {
    if (pos < l || pos > r || l > r) return;
    if (pos == l && r == pos) {
        tree[index] = val;
        return;
    }

    if (pos <= MID) {
        update(pos, l, MID, LEFT, val);
    } else {
        update(pos, MID + 1, r, RIGHT, val);
    }
    tree[index] = max(tree[LEFT], tree[RIGHT]);
}

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
		    ret = max(ret, query(id[fx], id[x], 1, n, 1));
		    x = parent[fx], fx = top[x];
		} else {
            ret = max(ret, query(id[fy], id[y], 1, n, 1));
            y = parent[fy], fy = top[y];
		}  
	}
	
    if (x == y) return ret;
	if (id[x] <= id[y]) {
	   ret = max(ret, query(id[son[x]], id[y], 1, n, 1));
	} else {
	   ret = max(ret, query(id[son[y]], id[x], 1, n, 1));
	}
	return ret;
}

void init() {
    memset(son, 0, sizeof(son));
    memset(parent, 0, sizeof(parent));
    memset(top, 0, sizeof(top));
    memset(id, 0, sizeof(id));
    memset(depth, 0, sizeof(depth));
    memset(sz, 0, sizeof(sz));
    memset(tree, -1, sizeof(tree));
    memset(rid, 0, sizeof(rid));
    int i;
    for (i = 0; i < MAX_SIZE; ++i) g[i].clear();
    cnt = 0;
}

char op[8];
pair<int, int> edg[MAX_SIZE];
int w[MAX_SIZE];
int wt[MAX_SIZE];
int e[MAX_SIZE];

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        tree[index] = wt[rid[l]];
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    tree[index] = max(tree[LEFT], tree[RIGHT]);
}

int main() {
    int T, i;
    scanf("%d", &T);
    while (T > 0) {
        init();
        scanf("%d", &n);
        for (i = 1; i < n; ++i) {
            scanf("%d%d%d", &edg[i].first, &edg[i].second, &w[i]);
            g[edg[i].first].push_back(edg[i].second);
            g[edg[i].second].push_back(edg[i].first);
        }

        dfs1(1, 0);
        dfs2(1, 1);

        for (i = 1; i < n; ++i) {
            if (depth[edg[i].first] > depth[edg[i].second]) swap(edg[i].first, edg[i].second);
            e[i] = edg[i].second;
            wt[edg[i].second] = w[i];
        }

        build(1, n, 1);
        while (scanf("%s", op) != EOF) {
            if (op[0] == 'D') break;
            int l, r;
            scanf("%d%d", &l, &r);
            if (op[0] == 'C') {
                update(id[e[l]], 1, n, 1, r);
            } else {
                printf("%d\n", hld(l, r));
            }
        }
        --T;
    }
    return 0;
}