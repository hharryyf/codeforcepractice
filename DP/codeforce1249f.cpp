#include <bits/stdc++.h>
#define MAX_SIZE 211
using namespace std;

int a[MAX_SIZE], dp[MAX_SIZE][MAX_SIZE];
vector<int> g[MAX_SIZE];
int N, K;

void dfs(int v, int pre) {
    int i;
    dp[v][0] = a[v];
    for (auto nv : g[v]) {
        if (nv != pre) {
            dfs(nv, v);
            dp[v][0] += dp[nv][K-1];
        }
    }

    
    for (i = 1 ; i <= N; ++i) {
        int curr = 0;
        for (auto nv : g[v]) {
            if (nv == pre) continue;
            curr = curr + dp[nv][max(i, K - i) -1];
        }

        dp[v][i] = curr;
        for (auto nv : g[v]) {
            if (nv == pre) continue;
            dp[v][i] = max(dp[v][i], curr - dp[nv][max(i, K - i) - 1] + (i < K - i ? dp[nv][i-1] : dp[nv][max(i, K - i) - 1]));
        }
    }

    for (i = N; i >= 0; --i) dp[v][i] = max(dp[v][i+1], dp[v][i]);
}

int main() {
    int i;
    scanf("%d%d", &N, &K);
    K++;
    for (i = 1; i <= N; ++i) scanf("%d", &a[i]);
    for (i = 1; i < N; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0);
    printf("%d\n", dp[1][0]);/*
    for (i = 1; i <= N; ++i) {
        for (int j = 0; j <= N; ++j) {
            cout << dp[i][j] << ", ";
        }
        cout << endl;
    }*/
    return 0;
}