#include <bits/stdc++.h>
#define MAX_SIZE 100011
typedef long long ll;
using namespace std;

vector<int> g[MAX_SIZE];
int parent[MAX_SIZE][17], h[MAX_SIZE], sz[MAX_SIZE];
ll depsm[MAX_SIZE], f[MAX_SIZE];
int N, M;

void dfs(int v, int pre) {
    int i;
    sz[v] = 1;
    parent[v][0] = pre;
    h[v] = h[pre] + 1;
    for (i = 1; i < 17; ++i) {
        parent[v][i] = parent[parent[v][i-1]][i-1];
    }

    for (auto nv : g[v]) {
        if (nv != pre) {
            dfs(nv, v);
            sz[v] += sz[nv];
            depsm[v] += depsm[nv] + 1ll * sz[nv];
        }
    }
}

void dfs2(int v, int pre) {
    for (auto nv : g[v]) {
        if (nv != pre) {
            f[nv] = f[v] + 1ll * (N - sz[nv]) + depsm[v] - (depsm[nv] + sz[nv]); 
            dfs2(nv, v);
        }
    }
}

int LCA(int u, int v) {
    if (h[u] < h[v]) swap(u, v);
    int i;
    for (i = 16; i >= 0; --i) {
        if (h[u] >= (1 << i) + h[v]) {
            u = parent[u][i];
        }
    }

    if (u == v) return u;
    for (i = 16; i >= 0; --i) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i], v = parent[v][i];
        }
    }

    return parent[u][0];
}

int getanc(int v, int p) {
    int i;
    if (p == 0) return v;
    for (i = 16; i >= 0; --i) {
        if (p >= (1 << i)) {
            v = parent[v][i];
            p = p - (1 << i);
        }
    }

    return v;
}

int main() {
    int i;
    scanf("%d%d", &N, &M);
    for (i = 0; i < N - 1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0);
    dfs2(1, 0);

    while (M-- > 0) {
        int u, v;
        scanf("%d%d", &u, &v);
        if (h[u] < h[v]) swap(u, v);
        int lca = LCA(u, v);
        if (lca != u && lca != v) {
            ll h1 = 1ll + h[u] + h[v] - 2 * h[lca];
            double ans = 1.0 * h1 +  (1.0 * depsm[u]) / (1.0 * sz[u]) + (1.0 * depsm[v]) / (1.0 * sz[v]);
            printf("%.8lf\n", ans);
        } else {
            ll h1 = h[u] - h[v] + 1;
            int p = getanc(u, h[u] - h[v] - 1);
            int s1 = sz[u], s2 = N - sz[p];
            // cout << p << " " << s1 << " " << s2 << endl;
            ll d1 = depsm[u], d2 = f[v] + depsm[v] - depsm[p] - sz[p];
            double ans = 1.0 * h1 + 1.0 * d1 / (1.0 * s1) + 1.0 * d2 / s2;
            // cout << h1 << " " << d1 << " " << d2 << " " << s1 << " " << s2 << endl;
            printf("%.8lf\n", ans);
        }
    }
    return 0;
}