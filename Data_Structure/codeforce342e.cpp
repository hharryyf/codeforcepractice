#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 262192
using namespace std;

vector<int> g[MAX_SIZE];
vector<int> node;
int dist[MAX_SIZE];
int visited[MAX_SIZE];
int id[MAX_SIZE];
int rid[MAX_SIZE];
int depth[MAX_SIZE];
int cnt = 0;
int table[MAX_SIZE << 1][19];
int pos[MAX_SIZE];
int logs[MAX_SIZE << 1];
vector<int> tour;
int block_size = 1;
int n, m;

void create_table() {
    int i, j, sz = tour.size();
    for (i = 2; i < (MAX_SIZE << 1); ++i) logs[i] = logs[i/2] + 1;
    for (i = 0 ; i < sz; ++i) table[i][0] = tour[i];
    for (i = 1; i <= 18; ++i) {
        int prel = (1 << (i - 1));
        for (j = 0; j < sz; j++) {
            if (j + prel < sz) {
                table[j][i] = min(table[j][i-1], table[j+prel][i-1]);
            } else {
                table[j][i] = table[j][i-1];
            }
        }
    }
}

int RMQ(int l, int r) {
    int len = r - l + 1;
    return min(table[l][logs[len]], table[r - (1 << logs[len]) + 1][logs[len]]);
}

void dfs(int v, int pre) {
    depth[v] = 1 + depth[pre];
    id[v] = cnt++;
    rid[id[v]] = v;
    pos[v] = (int) tour.size();
	tour.push_back(id[v]);
    for (auto nv : g[v]) {
        if (nv != pre) {
            dfs(nv, v);
            tour.push_back(id[v]);
        }
    }
}

int LCA(int u, int v) {
    int t1 = pos[u], t2 = pos[v];
    if (t1 > t2) swap(t1, t2);
    return rid[RMQ(t1, t2)];
}

int getdist(int u, int v) {
    // cout << "lca " << u << " " << v << " is " << LCA(u, v) << endl;
    return depth[u] + depth[v] - 2 * depth[LCA(u, v)];
}

void update(int v) {
    node.push_back(v);
    if ((int) node.size() >= block_size) {
        queue<int> q;
        memset(visited, 0, sizeof(visited));
        while (!node.empty()) {
            q.push(node.back());
            dist[node.back()] = 0;
            node.pop_back();
        }

        while (!q.empty()) {
            int nv = q.front();
            q.pop();
            if (visited[nv]) continue;
            visited[nv] = 1;
            for (auto nd : g[nv]) {
                if (!visited[nd]) {
                    dist[nd] = min(dist[nd], dist[nv] + 1);
                    q.push(nd);
                }
            }
        }
    }
}

int query(int v) {
    int ret = dist[v];
    for (auto nd : node) {
        ret = min(ret, getdist(nd, v));    
    }

    return ret;
}

int main() {
    int i;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i) dist[i] = n;
    block_size = sqrt(m);
    node.push_back(1);
    for (i = 0; i < n - 1; ++i) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        g[v1].push_back(v2);
        g[v2].push_back(v1);
    }
    
    dfs(1, 0);
    create_table();
    while (m-- > 0) {
        int tp, v;
        scanf("%d%d", &tp, &v);
        if (tp == 1) {
            update(v);
        } else {
            printf("%d\n", query(v));
        }
    }
    return 0;
}