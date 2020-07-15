#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 50111
using namespace std;
typedef long long ll;

// the origional tree
vector<int> g[MAX_SIZE];
// cnt[i] refers to the number of nodes with 
int cnt[MAX_SIZE];
// the compressed centroid tree
vector<int> ct[MAX_SIZE];
int parent[MAX_SIZE], sz[MAX_SIZE];
int tocheck[MAX_SIZE];
ll curr = 0;
ll ans = 0;
int n, k;

void init() {
    curr = 0, ans = 0;
    memset(tocheck, 1, sizeof(tocheck));
}

void dfs1(int v) {
    sz[v] = 1;
    for (auto nv : g[v]) {
        if (nv != parent[v]) {
            parent[nv] = v;
            dfs1(nv);
            sz[v] += sz[nv];
        }
    }
}

// dfs2 get the solution for the tree "rooted" at v
void dfs2(int v, int pre, int val, int tp) {
    cnt[val] += tp;
    for (auto nv : g[v]) {
        if (nv == pre) continue;
        if (!tocheck[nv]) continue;
        dfs2(nv, v, val + 1, tp);
    }
}
// update the answer based on the current decomposed centroid
void update(int v, int pre, int val) {
    if (val > k) return;
    curr += cnt[k - val];
    for (auto nv : g[v]) {
        if (tocheck[nv] && nv != pre) {
            update(nv, v, val + 1);
        }
    }
}   
// 
int getroot(int v, int psz, int pre) {
    int u = v;
    while (true) {
        int nu = 0;
        for (auto nv : g[u]) {
            if (!tocheck[nv] || nv == parent[u]) continue;
            if (sz[nv] >= psz / 2) nu = nv;
        }

        if (psz -sz[u] - 1 > psz / 2 && parent[u] != 0 && tocheck[parent[u]]) {
            nu = parent[u];
        }

        if (nu != 0) {
            u = nu;
        } else {
            break;
        }
    }

    // here u is the new centroid of the subtree
    auto nv = parent[u];
    // update the size array after deleting the centroid
    while (nv != 0 && tocheck[nv]) {
        sz[nv] -= 1 + sz[u];
        nv = parent[nv];
    }

    curr = 0;
    // here is the solve fundtion
    dfs2(u, pre, 0, 1);
    curr += cnt[k];
    for (auto nv : g[u]) {
        if (tocheck[nv]) {
            dfs2(nv, u, 1, -1);
            update(nv, u, 1);
            dfs2(nv, u, 1, 1);
        }
    }
    dfs2(u, pre, 0, -1);
    ans += curr / 2;
    tocheck[u] = 0;
    for (auto nv : g[u]) {
        if (!tocheck[nv]) continue;
        int V2 = 1 + sz[nv];
        if (nv == parent[u]) V2 = psz - 1 - sz[u];
        ct[u].push_back(getroot(nv, V2, u));
    }
    return u;
}

int main() {
    int i;
    init();
    scanf("%d%d", &n, &k);
    for (i = 0 ; i < n - 1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[v].push_back(u);
        g[u].push_back(v);
    }

    dfs1(1);
    getroot(1, sz[1], 0);

    cout << ans << endl;
    return 0;
}