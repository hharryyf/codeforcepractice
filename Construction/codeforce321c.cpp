#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

vector<int> g[MAX_SIZE];
vector<int> ct[MAX_SIZE];
int parent[MAX_SIZE];
int visited[MAX_SIZE];
int sz[MAX_SIZE];
char ans[MAX_SIZE];

void dfs1(int v) {
    sz[v] = 1;
    for (auto nv : g[v]) {
        if (parent[v] == nv) continue;
        parent[nv] = v;
        dfs1(nv);
        sz[v] += sz[nv];
    }
}

void fixsize(int root) {
    int v = parent[root];
    while (v != 0 && !visited[v]) {
        sz[v] -= 1 + sz[root];
        v = parent[v];
    }
}

int getroot(int _u, int psz) {
    int root = _u;
    while (true) {
        int nu = 0;
        for (auto nv : g[root]) {
            if (visited[nv] || nv == parent[root]) continue;
            if (sz[nv] >= psz / 2) nu = nv;
        }

        if (psz - 1 - sz[root] > psz / 2 && parent[root] != 0 && !visited[parent[root]]) {
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

int CD(int _u, int psz, int pre) {
    int root = getroot(_u, psz);
    fixsize(root);
    visited[root] = 1;
    for (auto nv : g[root]) {
        if (visited[nv]) continue;
        int V2 = 1 + sz[nv];
        if (nv == parent[root]) V2 = psz - 1 - sz[root];
        ct[root].push_back(CD(nv, V2, root));
    }

    return root;
}

void dfs(int v, int d) {
    if (d > 25) {
        printf("Impossible!\n");
        exit(0);
    }

    ans[v] = 'A' + d;
    for (auto nv : ct[v]) {
        dfs(nv, d + 1);
    }
}

int main() {
    int n, i;
    scanf("%d", &n);
    for (i = 0 ; i < n - 1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs1(1);
    int root = CD(1, sz[1], 0);
    dfs(root, 0);
    for (i = 1; i <= n; ++i) {
        printf("%c ", ans[i]);
    }
    printf("\n");
    return 0;
}