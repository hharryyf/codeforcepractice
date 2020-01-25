#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 100011
typedef long long ll;
using namespace std;

struct edge {
    int v;
    int tp;
};

vector<edge> g[MAX_SIZE];
int parent[MAX_SIZE][18];
int height[MAX_SIZE];
// record the number of times an edge has been visited
int cnt[MAX_SIZE][2];
int up[MAX_SIZE];

void dfs(int v, int pre, int d) {
    height[v] = d; 
    parent[v][0] = pre;
    int i;
    for (i = 1; i <= 17; i++) {
        parent[v][i] = parent[parent[v][i-1]][i-1];
    }
    
    for (auto ed : g[v]) {
        int nv = ed.v;
        if (nv != pre) {
            up[ed.v] = -ed.tp;
            dfs(nv, v, d + 1);
        }
    }
}

int LCA(int u, int v) {
    if (height[u] < height[v]) swap(u, v);
    int i;
    for (i = 17; i >= 0; i--) {
        if (height[v] + (1 << i) <= height[u]) {
            u = parent[u][i];
        }
    }
    
    if (u == v) return u;
    for (i = 17; i >= 0; i--) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i], v = parent[v][i];
        }
    }
    
    return parent[u][0];
}

// return the total number of step 1 count and bidirectional count
void update(int u, int v) {
    int pt = LCA(u, v);
    cnt[u][0]++, cnt[pt][0]--, cnt[v][1]++, cnt[pt][1]--;
}

ll fastpow(int p) {
    ll ret = 1;
    ll base = 2;
    while (p > 0) {
        if (p % 2 == 0) {
            base = base * base;
            base %= MOD;
            p /= 2;
        } else {
            ret = ret * base;
            ret %= MOD;
            p--;
        }
    }
    return ret;
}

void dfs_2(int v, int pre) {
    for (auto ed : g[v]) {
        int nv = ed.v;
        if (nv != pre) {
            dfs_2(nv, v);
            cnt[v][0] += cnt[nv][0], cnt[v][1] += cnt[nv][1];
        }
    }
}

int n;
int curr = 1;
ll ans = 0;

int main() {
    scanf("%d", &n);
    int i;
    for (i = 0 ; i < n - 1; i++) {
        int v1, v2, w;
        scanf("%d%d%d", &v1, &v2, &w);
        if (!w) {
            g[v1].push_back(edge{v2, 0});
            g[v2].push_back(edge{v1, 0});
        } else {
            g[v1].push_back(edge{v2, 1});
            g[v2].push_back(edge{v1, -1});
        }
    }
    dfs(1, 0, 1);
    int m;
    scanf("%d", &m);
    for (i = 0 ; i < m; i++) {
        int v;
        scanf("%d", &v);
        update(curr, v);
        curr = v;
    }
    
    dfs_2(1, 0);
    
    for (i = 1; i <= n; i++) {
        if (up[i] == 1) {
            ans = (ans + fastpow(cnt[i][1]) - 1 + MOD) % MOD;
        } else if (up[i] == -1) {
            ans = (ans + fastpow(cnt[i][0]) - 1 + MOD) % MOD;
        }
    }
    
    printf("%lld\n", ans % MOD);
    return 0;
}
