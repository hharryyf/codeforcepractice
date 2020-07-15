#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 262192
using namespace std;

vector<int> g[MAX_SIZE];
int cnt[MAX_SIZE << 2];
int parent[MAX_SIZE];
int tocheck[MAX_SIZE];
int sz[MAX_SIZE];
long long ans[MAX_SIZE];
char val[MAX_SIZE];

void init() {
    memset(tocheck, 1, sizeof(tocheck));
}

int decode(char ch) {
    return 1 << (ch - 'a');
}

void dfs1(int v) {
    sz[v] = 1;
    for (auto nv : g[v]) {
        if (nv == parent[v]) continue;
        parent[nv] = v;
        dfs1(nv);
        sz[v] += sz[nv];
    }
}

void dfs2(int v, int pre, int wt, int tp) {
    cnt[wt] += tp;
    for (auto nv : g[v]) {
        if (tocheck[nv] && nv != pre) {
            dfs2(nv, v, wt ^ decode(val[nv]), tp);
        }
    }
}

long long update(int v, int pre, int wt) {
    int i;
    long long curr = 0;
    curr += cnt[wt];
    for (i = 0; i < 20; ++i) {
        curr += cnt[wt ^ (1 << i)];
    }
    for (auto nv : g[v]) {
        if (tocheck[nv] && nv != pre) {
            curr += update(nv, v, wt ^ decode(val[nv]));
        }
    }

    ans[v] += curr;
    return curr;
}

int getroot(int _u, int psz) {
    int root = _u;
    while (true) {
        int nu = 0;
        for (auto nv : g[root]) {
            if (!tocheck[nv] || nv == parent[root]) continue;
            if (sz[nv] >= psz / 2) nu = nv;
        }

        if (psz - sz[root] - 1 > psz / 2 && parent[root] != 0 && tocheck[parent[root]]) {
            nu = parent[root];
        }

        if (nu != 0) {
            root = nu;
        } else {
            break;
        }
    }

    return root;
}

void fixsize(int root) {
    int v = parent[root];
    while (v != 0 && tocheck[v]) {
        sz[v] -= 1 + sz[root];
        v = parent[v];
    }
}

int CD(int _u, int psz, int pre) {
    int root = getroot(_u, psz), i;
    long long curr = 0;
    fixsize(root);
    dfs2(root, pre, decode(val[root]), 1);
    curr += cnt[0];
    for (i = 0; i < 20; ++i) {
        curr += cnt[1 << i];
    }

    for (auto nv : g[root]) {
        if (tocheck[nv]) {
            dfs2(nv, root, decode(val[nv]) ^ decode(val[root]), -1);
            curr += update(nv, root, decode(val[nv]));
            dfs2(nv, root, decode(val[nv]) ^ decode(val[root]), 1);
        }
    }

    dfs2(root, pre, decode(val[root]), -1);
    ans[root] += curr / 2;
    tocheck[root] = 0;
    for (auto nv : g[root]) {
        if (!tocheck[nv]) continue;
        int V2 = 1 + sz[nv];
        if (nv == parent[root]) V2 = psz - 1 - sz[root];
        CD(nv, V2, root);
    }
    return root;
}


int main() {
    int i, n;
    init();
    scanf("%d", &n);
    for (i = 0 ; i < n - 1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    scanf("%s", val+1);

    dfs1(1);
    CD(1, sz[1], 0);

    for (i = 1; i <= n; ++i) {
        printf("%I64d ", ans[i] + 1);
    }
    return 0;
}