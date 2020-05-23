#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 2503
using namespace std;

struct edge {
    int from, to, weight;
    bool select;
    bool operator < (edge other) const {
        return weight < other.weight;
    }
};

int a[MAX_SIZE][MAX_SIZE];
int f[MAX_SIZE];
edge edg[3500011];
int parent[MAX_SIZE][13];
int depth[MAX_SIZE];
int pmax[MAX_SIZE][13];
int n;
// (to,weight)
vector<pair<int,int>> g[MAX_SIZE];

int find(int x) {
    if (x == f[x]) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int a = find(x), b = find(y);
    f[a] = b;
}

void dfs(int v, int pre) {
    int i;
    depth[v] = depth[pre] + 1;
    parent[v][0] = pre;
    for (i = 1; i <= 12; ++i) {
        parent[v][i] = parent[parent[v][i-1]][i-1];
        pmax[v][i] = max(pmax[v][i-1], pmax[parent[v][i-1]][i-1]);
    }

    for (auto np : g[v]) {
        int nv = np.first, wt = np.second;
        if (nv != pre) {
            pmax[nv][0] = wt;
            dfs(nv, v);
        }
    }
}
// return the maximum edge on the path (u, v)
int query(int u, int v) {
    int i, ret = 0;
    if (depth[u] < depth[v]) {
        swap(u, v);
    }

    for (i = 12; i >= 0; --i) {
        if (depth[u] >= depth[v] + (1 << i)) {
            ret = max(ret, pmax[u][i]);
            u = parent[u][i];
        }
    }

    if (u == v) return ret;

    for (i = 12; i >= 0; --i) {
        if (parent[u][i] != parent[v][i]) {
            ret = max(ret, max(pmax[u][i], pmax[v][i]));
            u = parent[u][i], v = parent[v][i];
        }
    }

    ret = max(ret, max(pmax[u][0], pmax[v][0]));
    return ret;
}

int main() {
    int i, tol = 0, j;
    scanf("%d", &n);
    for (i = 0 ; i < MAX_SIZE; ++i) f[i] = i;
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= n; ++j) {
            scanf("%d", &a[i][j]);
        }
    }   
    // check the matrix is symmetric
    for (i = 1; i <= n; ++i) {
        for (j = i ; j <= n; ++j) {
            if (a[i][j] != a[j][i] || (i == j && a[i][j] != 0)) {
                printf("NOT MAGIC\n");
                return 0;
            }

            if (i != j) {
                edg[tol++] = edge{i, j, a[i][j], false};
            }
        }
    }

    sort(edg, edg + tol);

    for (i = 0 ; i < tol; ++i) {
        if (find(edg[i].from) != find(edg[i].to)) {
            g[edg[i].from].emplace_back(edg[i].to, edg[i].weight);
            g[edg[i].to].emplace_back(edg[i].from, edg[i].weight);
            unionset(edg[i].from, edg[i].to);
        }
    }

    dfs(1, 0);
    // check all edges can be MST-edge
    for (i = 0 ; i < tol; ++i) {
        if (!edg[i].select) {
            int v = query(edg[i].from, edg[i].to);
            if (edg[i].weight != v) {
                printf("NOT MAGIC\n");
                return 0;
            }
        }
    }

    printf("MAGIC\n");
    return 0;
}