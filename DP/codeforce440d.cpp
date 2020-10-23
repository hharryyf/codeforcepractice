#include <bits/stdc++.h>
#define MAX_SIZE 403
using namespace std;
int dp[MAX_SIZE][MAX_SIZE];
int sz[MAX_SIZE];
const int inf = 1000000;
vector<int> g[MAX_SIZE];
vector<pair<int, int>> opt[MAX_SIZE][MAX_SIZE];
int f[MAX_SIZE];
pair<int, int> edg[MAX_SIZE];
int visited[MAX_SIZE];
int n, k;

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void unionset(int v, int u) {
    v = find(v), u = find(u);
    f[v] = u;
}

void dfs(int v, int pre) {
    int i, j;
    dp[v][1] = 0;
    sz[v] = 1;
    for (auto nv : g[v]) {
        if (nv != pre) {
            dfs(nv, v);
            sz[v] += sz[nv];
            dp[v][1]++;
        }
    }

    for (auto nv : g[v]) {
        if (nv == pre) continue;
        for (i = min(k, sz[v]); i >= 2; --i) {
            for (j = 1; j <= min(i, sz[nv]); ++j) {
                if (dp[v][i] > dp[v][i-j] + dp[nv][j] - 1) {
                    dp[v][i] = dp[v][i-j] + dp[nv][j] - 1;
                    opt[v][i] = opt[v][i-j];
                    opt[v][i].push_back(make_pair(nv, j));
                }
            }
        }
    }
}

void back_track(int v, int p) {
    visited[v] = 1;
    for (auto np : opt[v][p]) {
        if (!visited[np.first]) {
            back_track(np.first, np.second);
            unionset(np.first, v);
        }
    }
}

int main() {
    int i, j;
    for (i = 0 ; i < MAX_SIZE; ++i) {
        f[i] = i;
        for (j = 0 ; j < MAX_SIZE; ++j) {
            dp[i][j] = inf;
        }
    }

    scanf("%d%d", &n, &k);
    for (i = 0 ; i < n - 1; ++i) {
        int v, u;
        scanf("%d%d", &v, &u);
        g[u].emplace_back(v);
        g[v].emplace_back(u);
        edg[i+1].first = u, edg[i+1].second = v;
    }

    dfs(1, 0);

    int ans = inf, v = 0;
    for (i = 1; i <= n; ++i) {
        if (ans > dp[i][k] + (i != 1)) {
            ans = dp[i][k] + (i != 1);
            v = i;
        }
    }

    printf("%d\n", ans);
    back_track(v, k);
    for (i = 1; i <= n-1; ++i) {
        if (find(edg[i].first) == find(v) && find(edg[i].second) != find(v)) {
            printf("%d ", i);
            continue;
        }

        if (find(edg[i].second) == find(v) && find(edg[i].first) != find(v)) {
            printf("%d ", i);
        }
    }
    return 0;
}