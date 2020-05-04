#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 262192
#define MID ((l+r)>>1)
#define LEFT (index << 1)
#define RIGHT (index << 1 | 1)

typedef long long ll;
using namespace std;

struct segt {
    ll value, lz;
};

segt tree[MAX_SIZE];
int id[MAX_SIZE], rid[MAX_SIZE], a[MAX_SIZE];
int sz[MAX_SIZE];
int cnt = 0;
int parent[MAX_SIZE][18], depth[MAX_SIZE];
vector<int> g[MAX_SIZE];
int n;

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        tree[index].value = a[rid[l]];
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    tree[index].value = tree[LEFT].value + tree[RIGHT].value;
}

void pushdown(int l, int r, int index) {
    if (l > r) return;
    if (tree[index].lz != 0) {
        if (l != r) {
            int len1 = (MID) - l + 1, len2 = r - (MID);
            tree[LEFT].lz += tree[index].lz;
            tree[RIGHT].lz += tree[index].lz;
            tree[LEFT].value += tree[index].lz * len1;
            tree[RIGHT].value += tree[index].lz * len2;
        }
        tree[index].lz = 0;
    }
}

void update(int start, int end, int l, int r, int index, ll val) {
    if (start > end || l > r || start > r || l > end) return;
    pushdown(l, r, index);
    if (start <= l && r <= end) {
        tree[index].lz += val;
        tree[index].value += val * (r - l + 1);
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
    tree[index].value = tree[LEFT].value + tree[RIGHT].value;
}

ll query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return 0;
    pushdown(l, r, index);
    if (start <= l && r <= end) {
        return tree[index].value;
    }

    if (end <= MID) {
        return query(start, end, l, MID, LEFT);
    }

    if (start >= MID + 1) {
        return query(start, end, MID + 1, r, RIGHT);
    }

    return query(start, end, l, MID, LEFT) + query(start, end, MID + 1, r, RIGHT);
}

void dfs(int v, int pre) {
    id[v] = ++cnt;
    rid[id[v]] = v;
    parent[v][0] = pre, depth[v] = depth[pre] + 1;
    sz[v] = 1;
    int i;
    for (i = 1; i <= 17; ++i) {
        parent[v][i] = parent[parent[v][i-1]][i-1];
    }

    for (auto nv : g[v]) {
        if (nv != pre) {
            dfs(nv, v);
            sz[v] += sz[nv];
        }
    }
}

int LCA(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int i;
    for (i = 17; i >= 0; --i) {
        if (depth[u] >= (1 << i) + depth[v]) u = parent[u][i];
    }

    if (u == v) return u;
    for (i = 17; i >= 0; --i) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i], v = parent[v][i];
        }
    }

    return parent[u][0];
}

int getkth(int v, int k) {
    if (k < 0) return v;
    int i, ret = v;
    for (i = 17; i >= 0; --i) {
        if (k >= (1 << i)) {
            ret = parent[ret][i];
            k -= (1 << i);
        }
    }
    return ret;
}

int dst(int u, int v) {
    int d1 = depth[u] - 1, d2 = depth[v] - 1;
    int lca = LCA(u, v);
    int d3 = depth[lca] - 1;
    return d1 + d2 - 2 * d3;
}

// get the real LCA of u and v given the root is rt
int getnewLCA(int u, int v, int rt) {
    int lca = LCA(u, v);
    if (lca == rt) return rt;
    int lca2 = LCA(lca, rt);
    if (lca2 != lca) return lca;
    // here is the toughest case, the lca is not the original LCA
    // we use the math property of the LCA
    // dist(u, rt) + dist(v, rt) - 2 * dist(real_lca, rt) = dist(u, v)
    int dist = (dst(u, rt) + dst(v, rt) - dst(u, v)) / 2;
    return getkth(rt, dist);
}
// update the subtree of v given that the root is rt
void updateSub(int v, ll val, int rt) {
    if (v == rt) {
        update(1, n, 1, n, 1, val);
        return;
    }
    int lca = LCA(v, rt);
    if (lca == v) {
        int dist = depth[rt] - depth[v];
        int nv = getkth(rt, dist - 1);
        int l = id[nv], r = id[nv] + sz[nv] - 1;
        update(1, n, 1, n, 1, val);
        update(l, r, 1, n, 1, -val);
        return;
    } 
    int l = id[v], r = id[v] + sz[v] - 1;
    update(l, r, 1, n, 1, val);
}
// output the sum of the subtree of v, given the root is rt
ll querySub(int v, int rt) {
    if (v == rt) return query(1, n, 1, n, 1);
    int lca = LCA(v, rt);
    if (lca == v) {
        int dist = depth[rt] - depth[v];
        int nv = getkth(rt, dist - 1);
        int l = id[nv], r = id[nv] + sz[nv] - 1;
        return query(1, n, 1, n, 1) - query(l, r, 1, n, 1);
    } 
    int l = id[v], r = id[v] + sz[v] - 1;
    return query(l, r, 1, n, 1);
}

int main() {
    int i, q;
    int rt = 1;
    scanf("%d%d", &n, &q);
    for (i = 1; i <= n; ++i) scanf("%d", &a[i]);
    for (i = 1; i < n; ++i) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        g[v1].push_back(v2);
        g[v2].push_back(v1);
    }

    dfs(1, 0);
    build(1, n, 1);
    while (q > 0) {
        int tp;
        scanf("%d", &tp);
        if (tp == 1) {
            scanf("%d", &rt);
        } else if (tp == 2) {
            int u, v, val;
            scanf("%d%d%d", &u, &v, &val);
            v = getnewLCA(u, v, rt);
            updateSub(v, val, rt);
        } else {
            int v;
            scanf("%d", &v);
            printf("%I64d\n", querySub(v, rt));
        }
        --q;
    }
    return 0;
}