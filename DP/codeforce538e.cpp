#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

vector<int> g[MAX_SIZE];
int sz[MAX_SIZE];
int dp[MAX_SIZE][2];
void dfs1(int v, int pre, int d) {
    int child = 0, mn = MAX_SIZE;
    for (auto nv : g[v]) {
        if (nv != pre) {
            dfs1(nv, v, d + 1);
            child = 1;
            sz[v] += sz[nv];
            if (d % 2 == 0) {
                mn = min(sz[nv] - dp[nv][0], mn);
            } else {
                dp[v][0] += dp[nv][0] - 1;
            }
        }
    }

    if (child == 0) {
        dp[v][0] = 1;
        sz[v] = 1;
    } else {
        if (d % 2 == 1) {
            dp[v][0] += 1;
        } else {
            dp[v][0] = sz[v] - mn;
        }
    }
}

void dfs2(int v, int pre, int d) {
    int child = 0, mn = MAX_SIZE;
    for (auto nv : g[v]) {
        if (nv != pre) {
            dfs2(nv, v, d + 1);
            child = 1;
            if (d % 2 == 0) {
                dp[v][1] += dp[nv][1];
            } else {
                mn = min(mn, dp[nv][1]);
            }
        }
    }

    if (child == 0) {
        dp[v][1] = 1;
    } else {
        if (d % 2 == 1) {
            dp[v][1] = mn;
        }
    }
}

int main() {
    int i, n;
    scanf("%d", &n);
    for (i = 0 ; i < n - 1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs1(1, 0, 0);
    dfs2(1, 0, 0);
    printf("%d %d\n", dp[1][0], dp[1][1]);
    return 0;
}