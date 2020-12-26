#include <bits/stdc++.h>
#define MAX_SIZE 300011
using namespace std;

int f[MAX_SIZE], sz[MAX_SIZE];
int dep[MAX_SIZE];
int visited[MAX_SIZE];
vector<int> g[MAX_SIZE];
vector<int> ret;
int N, Q;

void dfs1(int v, int d = 0) {
    visited[v] = 1;
    dep[v] = d;
    ret.push_back(v);
    for (auto nv : g[v]) {
        if (!visited[nv]) {
            dfs1(nv, d+1);
        }
    }
}

void dfs2(int v, int d = 0) {
    visited[v] = 1;
    dep[v] = d;
    for (auto nv : g[v]) {
        if (!visited[nv]) {
            dfs2(nv, d + 1);
        }
    }
}

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void unionset(int u, int v) {
    int a = find(u), b = find(v);
    if (a == b) return;
    f[a] = b;
    sz[b] = max(max(sz[a], sz[b]), 1 + (sz[a] / 2) + (sz[a] % 2) + (sz[b] / 2) + (sz[b] % 2));
}

int main() {
    int m, i;
    scanf("%d%d%d", &N, &m, &Q);
    for (i = 0 ; i < m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[v].push_back(u);
        g[u].push_back(v);
    }

    for (i = 1; i <= N; ++i) {
        if (!visited[i]) {
            ret.clear();
            dfs1(i);
            int vc = ret[0];
            for (auto v : ret) {
                if (dep[v] > dep[vc]) {
                    vc = v;
                }
            }

            for (auto v : ret) {
                f[v] = vc;
                dep[v] = 0;
                visited[v] = 0;
            }

            dfs2(vc);
            int curr = 0;
            for (auto v : ret) {
                curr = max(curr, dep[v]);
            }

            for (auto v : ret) {
                sz[v] = curr;
            }
        }
    }

    while (Q-- > 0) {
        int tp;
        scanf("%d", &tp);
        if (tp == 2) {
            int u, v;
            scanf("%d%d", &u, &v);
            unionset(u, v);
        } else {
            int x;
            scanf("%d", &x);
            printf("%d\n", sz[find(x)]);
        }
    }
    return 0;
}