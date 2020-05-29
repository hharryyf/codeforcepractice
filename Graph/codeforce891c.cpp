#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 505011
using namespace std;

struct qrs {
    int from, to, id;
};

struct edge {
    int from, to, w;
};

edge edg[MAX_SIZE];
// the collection of edges per weight
vector<pair<int, int>> g[MAX_SIZE];
vector<int> sz[MAX_SIZE];
vector<int> f[MAX_SIZE];
int ans[MAX_SIZE];
// q[i] records all queries with edge weight i
vector<qrs> q[MAX_SIZE];
// first join to second
vector<pair<int, int>> history;

void init() {
    int i;
    for (i = 0; i < MAX_SIZE; ++i) {
        f[i].push_back(i);
        sz[i].push_back(1);
        ans[i] = 1;
    }
}

int find(int x) {
    if (x == f[x].back()) return x;
    return find(f[x].back());
}

void unionset(int x, int y) {
    int a = find(x), b = find(y);
    if (a == b) {
        history.emplace_back(-1, -1);
    } else {
        if (sz[a].back() > sz[b].back()) {
            sz[a].push_back(sz[a].back() + sz[b].back());
            f[b].push_back(a);
            history.emplace_back(b, a);
        } else {
            sz[b].push_back(sz[a].back() + sz[b].back());
            f[a].push_back(b);
            history.emplace_back(a, b);
        }
    }
}

void cancel_last() {
    if (!history.empty()) {
        auto p = history.back();
        history.pop_back();
        if (p.first == -1) return;
        f[p.first].pop_back();
        sz[p.second].pop_back();
    }
}

int main() {
    int i, n, m, p, j;
    init();
    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; ++i) {
        scanf("%d%d%d", &edg[i].from, &edg[i].to, &edg[i].w);
        g[edg[i].w].emplace_back(edg[i].from, edg[i].to);
    }

    
    scanf("%d", &p);
    for (i = 1; i <= p; ++i) {
        int k;
        scanf("%d", &k);
        while (k > 0) {
            int v;
            scanf("%d", &v);
            q[edg[v].w].push_back(qrs{edg[v].from, edg[v].to, i});
            --k;
        }
    }

    for (i = 1; i < MAX_SIZE; ++i) {
        for (j = 0 ; j < (int) q[i].size(); ++j) {
            if (j > 0 && q[i][j].id != q[i][j-1].id) {
                int v = j - 1;
                while (v >= 0 && q[i][v].id == q[i][j-1].id) {
                    cancel_last();
                    --v;
                }
            }

            if (find(q[i][j].from) == find(q[i][j].to)) {
                ans[q[i][j].id] = 0;
            }
            
            unionset(q[i][j].from, q[i][j].to);
        }

        for (auto pp : g[i]) {
            unionset(pp.first, pp.second);
        }
    }

    for (i = 1; i <= p; ++i) {
        printf("%s\n", ans[i] ? "YES" : "NO");
    }
    return 0;
}