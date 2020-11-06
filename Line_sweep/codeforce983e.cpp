#include <bits/stdc++.h>
#define MAX_SIZE 200111
using namespace std;

vector<int> g[MAX_SIZE];
vector<int> up[MAX_SIZE];
int dep[MAX_SIZE], sz[MAX_SIZE], id[MAX_SIZE], rid[MAX_SIZE];
int parent[MAX_SIZE][19];
int pmin[MAX_SIZE][19];
int tree[MAX_SIZE];
int N, M, Q, cnt = 0;
struct route {
    int from, to;
};

struct event {
    int x, y, id, sgn;
    bool operator < (event other) const {
        if (x != other.x) return x < other.x;
        return id < other.id;
    }
};
// buses and queries
route bus[MAX_SIZE];
route qs[MAX_SIZE];
// add events and query events
vector<event> q;
int ans[MAX_SIZE], ans2[MAX_SIZE];

int shift(int x) {
    return x & (-x);
}

void update(int pos, int v) {
    if (pos <= 0) return;
    while (pos <= N) {
        tree[pos] += v;
        pos += shift(pos);
    }
}

int query(int pos) {
    int ret = 0;
    while (pos > 0) {
        ret += tree[pos];
        pos -= shift(pos);
    }
    return ret;
}

void dfs(int v, int d) {
    int i;
    sz[v] = 1, id[v] = ++cnt, rid[id[v]] = v, dep[v] = d;
    for (i = 1; i <= 18; ++i) parent[v][i] = parent[parent[v][i-1]][i-1];
    for (auto nv : g[v]) {
        dfs(nv, d + 1);
        sz[v] += sz[nv];
    }
}

void dfs2(int v) {
    for (auto nv : g[v]) {
        dfs2(nv);
        if (pmin[nv][0] != 0) {
            if (pmin[v][0] == 0) pmin[v][0] = pmin[nv][0];
            if (dep[pmin[v][0]] > dep[pmin[nv][0]]) pmin[v][0] = pmin[nv][0];
        }
    }

    for (auto nv : up[v]) {
        if (pmin[v][0] == 0 || dep[pmin[v][0]] > dep[nv]) pmin[v][0] = nv;
    }
}

int LCA(int u, int v) {
    int i;
    if (dep[u] < dep[v]) swap(u, v);
    for (i = 18; i >= 0; --i) {
        if (dep[u] >= (1 << i) + dep[v]) u = parent[u][i];
    }

    if (u == v) return u;
    for (i = 18; i >= 0; --i) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i], v = parent[v][i];
        }
    }
    // cout << "LCA= " << parent[u][0] << endl;
    return parent[u][0];
}
// the number of steps and upmost vertex
pair<int, int> getp(int v, int anc) {
    int i, ret = 0;
    // cout << "getp " << v << " " << anc << endl;
    for (i = 18; i >= 0; --i) {
        if (pmin[v][i] != 0 && dep[pmin[v][i]] > dep[anc]) {
            v = pmin[v][i];
            ret += (1 << i);
        }
    }
    // cout << ret << " : " << v << endl;
    return make_pair(ret, v);
}

int main() {
    int i, j;
    scanf("%d", &N);
    for (i = 2 ; i <= N; ++i) {
        scanf("%d", &parent[i][0]);
        g[parent[i][0]].push_back(i);
    }   
    scanf("%d", &M);
    for (i = 1; i <= M; ++i) scanf("%d%d", &bus[i].from, &bus[i].to);
    dfs(1, 1);

    for (i = 1; i <= M; ++i) {
        if (dep[bus[i].from] < dep[bus[i].to]) swap(bus[i].from, bus[i].to);
        int lca = LCA(bus[i].from, bus[i].to);
        up[bus[i].from].push_back(lca);
        if (bus[i].to != lca) {
            up[bus[i].to].push_back(lca);
            if (id[bus[i].from] > id[bus[i].to]) swap(bus[i].from, bus[i].to);
            q.push_back(event{id[bus[i].from], id[bus[i].to], 0, 0});
        }
    }

    dfs2(1);
    for (j = 1; j <= 18; ++j) {
        for (i = 1; i <= N; ++i) {
            if (pmin[i][j-1] != 0) pmin[i][j] = pmin[pmin[i][j-1]][j-1];
        }
    }

    scanf("%d", &Q);
    for (i = 1; i <= Q; ++i) {
        scanf("%d%d", &qs[i].from, &qs[i].to);
        if (dep[qs[i].from] < dep[qs[i].to]) swap(qs[i].from, qs[i].to);
        int lca = LCA(qs[i].from, qs[i].to);
        auto p1 = getp(qs[i].from, lca), p2 = getp(qs[i].to, lca);
        if (lca == qs[i].to) {
            if (pmin[p1.second][0] != 0 && dep[pmin[p1.second][0]] <= dep[lca]) {
                ans[i] = 1 + p1.first;
                
            } else {
                ans[i] = -1;
            }
        } else {
            // cout << p1.first << " " << p1.second << " " << p2.first << " " << p2.second << endl;
            if (pmin[p1.second][0] != 0 && dep[pmin[p1.second][0]] <= dep[lca] 
             && pmin[p2.second][0] != 0 && dep[pmin[p2.second][0]] <= dep[lca]) {
                
                ans[i] = 2 + p1.first + p2.first;
                int x = p1.second, y = p2.second;
                if (id[x] > id[y]) swap(x, y);
                // query the rectangle [id[x], id[x] + sz[x] - 1] [id[y], id[y] + sz[y] - 1]
                // (x, y, id, sgn)
                q.push_back(event{id[x] + sz[x] - 1, id[y] + sz[y] - 1, i, 1});
                q.push_back(event{id[x] - 1, id[y] - 1, i, 1});
                q.push_back(event{id[x] - 1, id[y] + sz[y] - 1, i, -1});
                q.push_back(event{id[x] + sz[x] - 1, id[y] - 1, i, -1});
            } else {
                ans[i] = -1;
            }
        }
    }

    sort(q.begin(), q.end());
    for (i = 0, j = 0; i <= N; ++i) {
        while (j < (int) q.size() && i == q[j].x) {
            if (q[j].id == 0) {
                update(q[j].y, 1);
            } else {
                ans2[q[j].id] += q[j].sgn * query(q[j].y);
            }
            ++j;
        }
    }

    for (i = 1; i <= Q; ++i) {
        if (ans2[i] > 0) {
            ans[i]--;
            // cout << i << " -1" << endl;
        }
        printf("%d\n", ans[i]);
    }
    return 0;
}