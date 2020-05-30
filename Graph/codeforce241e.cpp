#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 1011
using namespace std;

const int inf = 1e7;

struct edge {
    int from, to, w;
};

pair<int, int> oedg[MAX_SIZE << 3];
int ans[MAX_SIZE << 3];
edge edg[MAX_SIZE << 3];
// the graph and reverse graph
vector<int> g[MAX_SIZE];
vector<int> rg[MAX_SIZE];
// on the path from 1 to n, on the reverse path from n to 1
int onpath1[MAX_SIZE], onpathn[MAX_SIZE];
// useful iff onpath1[i] and onpathn[i]
int useful[MAX_SIZE];
int n, m;
int tol = 0;
int dist[MAX_SIZE];

void dfs1(int v) {
    onpath1[v] = 1;
    for (auto nv : g[v]) {
        if (!onpath1[nv]) {
            dfs1(nv);
        }
    }
}

void dfs2(int v) {
    onpathn[v] = 1;
    for (auto nv : rg[v]) {
        if (!onpathn[nv]) {
            dfs2(nv);
        }
    }
}

bool bellman_ford() {
    dist[0] = 0;
    int i, j;
    for (i = 1; i <= n; ++i) {
        dist[i] = inf;
    }

    for (i = 0; i < n; ++i) {
        for (j = 1; j <= tol; ++j) {
            edge &e = edg[j];
            dist[e.to] = min(dist[e.from] + e.w, dist[e.to]);
        }
    }

    for (j = 1; j <= tol; ++j) {
        edge &e = edg[j];
        if (dist[e.to] > dist[e.from] + e.w) {
            return false;
        }
    }

    return true;
}

int main() {
    int i;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; ++i) {
        scanf("%d%d", &oedg[i].first, &oedg[i].second);
        g[oedg[i].first].push_back(oedg[i].second);
        rg[oedg[i].second].push_back(oedg[i].first);
    }

    dfs1(1);
    dfs2(n);

    for (i = 1; i <= n; ++i) {
        useful[i] = onpath1[i] && onpathn[i];
    }

    for (i = 1; i <= m; ++i) {
        if (useful[oedg[i].first] && useful[oedg[i].second]) {
            // here add edge for system of different constraints
            int from = oedg[i].first, to = oedg[i].second;
            // we know that 1 <= dist[to] - dist[from] <= 2
            // it is  dist[to] - dist[from] <= 2 and dist[from] - dist[to] <= -1
            edg[++tol] = edge{from, to, 2};
            edg[++tol] = edge{to, from, -1};
        }   
    }

    for (i = 1; i <= n; ++i) {
        if (useful[i]) {
            edg[++tol] = edge{i, 0, 0};
        }
    }

    if (!bellman_ford()) {
        printf("No\n");
        return 0;
    }

    printf("Yes\n");
    for (i = 1; i <= m; ++i) {
        if (useful[oedg[i].first] && useful[oedg[i].second]) {
            printf("%d\n", dist[oedg[i].second] - dist[oedg[i].first]);
        } else {
            printf("1\n");
        }
    }
    return 0;
}