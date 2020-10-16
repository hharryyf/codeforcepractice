#include <bits/stdc++.h>
#define MAX_SIZE 1000011
using namespace std;

vector<int> g[MAX_SIZE];
int dp[MAX_SIZE][2];
int mn[MAX_SIZE], dep[MAX_SIZE];
int n, k;

void dfs(int v) {
    mn[v] = MAX_SIZE;
    for (auto nv : g[v]) {
        dep[nv] = dep[v] + 1;
        dfs(nv);
        if (mn[nv] - dep[v] <= k) {
            mn[v] = min(mn[v], mn[nv]);
            dp[v][0] = dp[v][0] + dp[nv][0];
        }
    }

    if (g[v].empty()) {
        mn[v] = dep[v];
        dp[v][0] = 1;
    }
}

void dfs2(int v) {
    dp[v][1] = dp[v][0];
    for (auto nv : g[v]) {
        dfs2(nv);
        int curr = dp[v][0];
        if (mn[nv] - dep[v] <= k) curr -= dp[nv][0];
        dp[v][1] = max(dp[v][1], dp[nv][1] + curr);
    }
}

int main() {
    int i;
    scanf("%d%d", &n, &k);
    for (i = 2 ; i <= n ; ++i) {
        int p;
        scanf("%d", &p);
        g[p].push_back(i);
    }

    dfs(1);
    dfs2(1);
    printf("%d\n", dp[1][1]);
    return 0;
}