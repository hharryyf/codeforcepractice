#include <bits/stdc++.h>
#define MAX_SIZE 524292
#define MID ((l+r)>>1)
#define LEFT (index << 1)
#define RIGHT (index << 1 | 1)
using namespace std;

struct rangetree {

    struct segt {
        // range full cover segment, length covered in the range
        int cover, len;
    };

    segt tree[MAX_SIZE];

    void pullup(int l, int r, int index) {
        if (l > r) return;
        if (tree[index].cover == 0) {
            if (l == r) {
                tree[index].len = 0;
            } else {
                tree[index].len = tree[LEFT].len + tree[RIGHT].len;
            }
        } else {
            tree[index].len = r - l + 1;
        }
    }

    // val=1 means cover, val=0 means cancel
    void update(int start, int end, int l, int r, int index, int val) {
        if (start > end || l > r || start > r || l > end) return;
        if (start <= l && r <= end) {
            tree[index].cover += val;
            pullup(l, r, index);
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

        pullup(l, r, index);
    }

    int query() {
        return tree[1].len;
    }
};

int n, q;
rangetree tree;
int parent[MAX_SIZE >> 1][19];
int depth[MAX_SIZE];
int sz[MAX_SIZE >> 1], id[MAX_SIZE >> 1];
vector<int> g[MAX_SIZE];
int cnt = 0;
set<pair<int, int>> edg;

void dfs(int v, int pre) {
    int i;
    id[v] = ++cnt;
    depth[v] = 1 + depth[pre];
    sz[v] = 1;
    parent[v][0] = pre;
    for (i = 1; i < 19; ++i) {
        parent[v][i] = parent[parent[v][i-1]][i-1];
    }

    for (auto nv : g[v]) {
        if (nv != pre) {
            dfs(nv, v);
            sz[v] += sz[nv];
        }
    }
}

int kthparent(int v, int k) {
    if (k <= 0) return v;
    int i;
    for (i = 18; i >= 0; --i) {
        if (k >= (1 << i)) {
            v = parent[v][i];
            k -= (1 << i);
        }
    }

    return v;
}

void update_edge(int u, int v, int tp) {
    // so now u is higher than v in the tree structure
    if (depth[u] > depth[v]) swap(u, v);
    // check whether u is a parent of v
    int l = id[u], r = id[u] + sz[u] - 1;
    if (l <= id[v] && id[v] <= r) {
        // cout << "case 1" << endl;
        if (parent[v][0] == u) return;
        int c = kthparent(v, depth[v] - depth[u] - 1);
        pair<int, int> L = {id[c], id[c] + sz[c] - 1};
        pair<int, int> R = {id[v], id[v] + sz[v] - 1};
        tree.update(L.first, R.first - 1, 1, n, 1, tp);
        tree.update(R.second + 1, L.second, 1, n, 1, tp);
    } else {
        // cout << "case 2" << endl;
        pair<int, int> L = {id[u], id[u] + sz[u] - 1};
        pair<int, int> R = {id[v], id[v] + sz[v] - 1};
        if (L > R) swap(L, R);
        tree.update(1, L.first - 1, 1, n, 1, tp);
        tree.update(L.second + 1, R.first - 1, 1, n, 1, tp);
        tree.update(R.second + 1, n, 1, n, 1, tp);
    }
}

int main() {
    scanf("%d%d", &n, &q);
    int i;
    for (i = 0 ; i < n - 1; ++i) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        g[v1].push_back(v2);
        g[v2].push_back(v1);
    }

    dfs(1, 0);

    while (q > 0) {
        int u, v;
        scanf("%d%d", &u, &v);
        if (edg.find(make_pair(u, v)) != edg.end()) {
            edg.erase(make_pair(u, v));
            edg.erase(make_pair(v, u));
            update_edge(u, v, -1);
        } else {
            edg.insert(make_pair(u, v));
            edg.insert(make_pair(v, u));
            update_edge(u, v, 1);
        }
        printf("%d\n", n - tree.query());
        --q;
    }
    return 0;
}