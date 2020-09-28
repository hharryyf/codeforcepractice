#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 200011
using namespace std;

vector<pair<int, ll>> g[MAX_SIZE];
int N;
int sz[MAX_SIZE];
ll mx, mn;

void init() {
    for (int i = 0 ; i <= N; ++i) {
        g[i].clear();
        sz[i] = 0;
    }
    mn = 0, mx = 0;
}

void dfs(int v, int p) {
    sz[v] = 1;
    for (auto ne : g[v]) {
        int nv = ne.first;
        ll w = ne.second;
        if (nv == p) continue;
        dfs(nv, v);
        sz[v] += sz[nv];
        if (sz[nv] % 2 == 1) {
            mn += w;
        }

        mx += 1ll * min(N - sz[nv], sz[nv]) * w;
    }
}

int main() {
    int T, i;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d", &N);
        N *= 2;
        init();
        for (i = 1; i < N; ++i) {
            int u, v;
            ll w;
            scanf("%d%d%I64d", &u, &v, &w);
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
        }

        dfs(1, 0);
        printf("%I64d %I64d\n", mn, mx);
    }
    return 0;
}