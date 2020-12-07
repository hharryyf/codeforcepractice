#include <bits/stdc++.h>
#define MAX_SIZE 300011
using namespace std;
typedef long long ll;
vector<int> g[MAX_SIZE];
ll a[MAX_SIZE];
ll dp[MAX_SIZE], dp2[MAX_SIZE];
int N, cnt = 0;
ll mx = -1000000002;

void dfs1(int v, int p) {
    if (a[v] == mx) {
        cnt++;
    } else if (mx < a[v]) {
        mx = a[v];
        cnt = 1;
    }

    for (auto nv : g[v]) {
        if (nv != p) {
            dfs1(nv, v);
        }
    }
}

void dfs2(int v, int p) {
    dp[v] += a[v];

    for (auto nv : g[v]) {
        if (nv != p) {
            dfs2(nv, v);
        }
    }
    
    for (auto nv : g[v]) {
        if (nv != p) {
            dp[v] += max(dp[nv], 0ll);
        }
    }

    mx = max(dp[v], mx);
}

void dfs3(int v, int p) {
    dp2[v] = a[v];
    for (auto nv : g[v]) {
        if (nv != p) {
            dfs3(nv, v);
            dp2[v] += max(dp2[nv], 0ll);
        }
    }

    if (dp2[v] == mx) {
        cnt++;
        dp2[v] = 0;
    }
}

int main() {
    int i;
    scanf("%d", &N);
    for (i = 1 ; i <= N; ++i) {
        scanf("%I64d", &a[i]);
    }    

    for (i = 0 ; i < N - 1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs1(1, 0);
    if (mx <= 0) {
        printf("%I64d %d\n", 1ll * cnt * mx, cnt);
        return 0;
    }

    cnt = 0, mx = 0;

    dfs2(1, 0);
    dfs3(1, 0);
    printf("%I64d %d\n", 1ll * cnt * mx, cnt);
    return 0;
}