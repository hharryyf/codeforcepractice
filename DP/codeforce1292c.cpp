#include <bits/stdc++.h>
#define MAX_SIZE 3011
typedef long long ll;
using namespace std;

vector<int> g[MAX_SIZE];
ll dp[MAX_SIZE][MAX_SIZE];
int sz[MAX_SIZE][MAX_SIZE];
int dist[MAX_SIZE][MAX_SIZE];
int psz[MAX_SIZE];
int n;

void dfs1(int v, int p) {
    psz[v] = 1;
    for (auto nv : g[v]) {
        if (nv != p) {
            dfs1(nv, v);
            psz[v] += psz[nv];
        }
    }
}

void dfs2(int v, int rt, int s, int p) {
    for (auto nv : g[v]) {
        if (nv != p) {
            dist[rt][nv] = dist[rt][v] + 1;
            if (v == rt) {
                sz[rt][nv] = (s - psz[nv]) * psz[nv];
                dfs2(nv, rt, s - psz[nv], v);
            } else {
                sz[rt][nv] = s * psz[nv];
                dfs2(nv, rt, s, v);
            }
        }
    }
}

ll dfs3(int u, int v, int p1, int p2) {
    if (dp[u][v] != -1) return dp[u][v];
    ll ret = 0;
    for (auto nu : g[u]) {
        if (nu != p1 && dist[nu][v] == dist[u][v] + 1) {
            ret = max(ret, 1ll * sz[nu][v] + dfs3(nu, v, u, p2));
        }
    }

    for (auto nv : g[v]) {
        if (nv != p2 && dist[u][nv] == dist[u][v] + 1) {
            ret = max(ret, 1ll * sz[u][nv] + dfs3(u, nv, p1, v));
        }
    }
    
    return dp[u][v] = ret;
}

int main() {
    int i, j;
    scanf("%d", &n);
    for (i = 1; i < n; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= n; ++j) {
            dp[i][j] = -1;
        }
    }

    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= n; ++j) {
            psz[j] = 0;
        }

        dfs1(i, 0);
        dfs2(i, i, psz[i],  0);
    }

    ll ans = 0;
    for (i = 1; i <= n; ++i) {
        dfs3(i, i, 0, 0);
        ans = max(ans, dp[i][i]);
    }

    cout << ans << endl;
    return 0;
}