#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 524292
#define MID ((l+r)>>1)
#define RIGHT (index<<1|1)
#define LEFT (index<<1)
typedef long long ll;
using namespace std;

const ll INF = 1e15;

struct edge {
    int to;
    ll w;
    int id;
    bool operator < (edge other) const {
        return w > other.w;
    }
};

int L[MAX_SIZE], R[MAX_SIZE];
int eid[MAX_SIZE];
ll dist[MAX_SIZE][2];
int pre[MAX_SIZE];
int pid[MAX_SIZE];
int critical[MAX_SIZE];
int visited[MAX_SIZE];
vector<edge> g[MAX_SIZE];
int n, len = 0;

void dijkstra(int src, int tp) {
    int i;
    int dim = src == 1 ? 0 : 1;
    priority_queue<edge> q;
    for (i = 1; i <= n; ++i) dist[i][dim] = INF;
    memset(visited, 0, sizeof(visited));
    dist[src][dim] = 0;
    q.push(edge{src, 0, 0});
    while (!q.empty()) {
        auto e = q.top();
        q.pop();
        if (visited[e.to]) continue;
        visited[e.to] = 1;
        dist[e.to][dim] = e.w;
        for (auto ne : g[e.to]) {
            if (!visited[ne.to]) {
                if (dist[ne.to][dim] > dist[e.to][dim] + ne.w) {
                    dist[ne.to][dim] = dist[e.to][dim] + ne.w;
                    q.push(edge{ne.to, dist[e.to][dim] + ne.w, ne.id});
                    pre[ne.to] = e.to;
                    pid[ne.to] = ne.id;
                    if (tp == 0 && !critical[ne.to]) {
                        L[ne.to] = L[e.to];
                    }

                    if (tp == 1 && !critical[ne.to]) {
                        R[ne.to] = R[e.to];
                    }
                }
            }
        }
    }

    if (tp == 2) {
        i = 1;
        int v = 1;
        L[1] = R[1] = 0;
        critical[1] = 1;
        while (v != n) {
            eid[pid[v]] = i;
            v = pre[v];
            L[v] = R[v] = i;
            len = i;
            critical[v] = 1;
            ++i;
        }
    }
}

ll tree[MAX_SIZE];
pair<pair<int, int>, ll> E[MAX_SIZE];

void update(int start, int end, int l, int r, int index, ll val) {
    if (start > end || l > r || start > r || l > end) return;
    if (start <= l && r <= end) {
        tree[index] = min(tree[index], val);
        return;
    }

    if (end <= MID) {
        update(start, end, l, MID, LEFT, val);
    } else if (start >= MID + 1) {
        update(start, end, MID + 1, r, RIGHT, val);
    } else {
        update(start, end, l, MID, LEFT, val);
        update(start, end, MID + 1, r, RIGHT, val);
    }
}

ll query(int pt, int l, int r, int index) {
    if (pt < l || pt > r || l > r) return INF;
    if (l == r) {
        return tree[index];
    }

    if (pt <= MID) return min(tree[index], query(pt, l, MID, LEFT));
    return min(tree[index], query(pt, MID + 1, r, RIGHT));
}

int main() {
    int i, m, q;
    for (i = 0 ; i < MAX_SIZE; ++i) {
        tree[i] = INF;
        eid[i] = -1;
    }

    scanf("%d%d%d", &n, &m, &q);

    for (i = 1; i <= m; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v ,&w);
        g[u].push_back(edge{v, w, i});
        g[v].push_back(edge{u, w, i});
        E[i].first.first = u, E[i].first.second = v, E[i].second = w;
    }

    dijkstra(n, 2);
    dijkstra(1, 0);
    dijkstra(n, 1);

    for (i = 1; i <= m; ++i) {
        if (eid[i] == -1) {
            // cout << "ith edge is false " << i << endl;
            update(L[E[i].first.first] + 1, R[E[i].first.second], 1, len, 1, dist[E[i].first.first][0] + dist[E[i].first.second][1] + E[i].second);
            // cout << "update " << dist[E[i].first.first][0] + dist[E[i].first.second][1] + E[i].second << endl;
            swap(E[i].first.first, E[i].first.second);
            update(L[E[i].first.first] + 1, R[E[i].first.second], 1, len, 1, dist[E[i].first.first][0] + dist[E[i].first.second][1] + E[i].second);
            // cout << "update " << dist[E[i].first.first][0] + dist[E[i].first.second][1] + E[i].second << endl;
        }
    }

    while (q-- > 0) {
        int id, w;
        scanf("%d%d", &id, &w);
        ll ans = INF;
        if (eid[id] == -1) {
            ans = dist[n][0];
            ans = min(ans, dist[E[id].first.first][1] + dist[E[id].first.second][0] + w);
            ans = min(ans, dist[E[id].first.second][1] + dist[E[id].first.first][0] + w);
        } else {
            // cout << "edge id= " << eid[id] << endl;
            ans = dist[n][0] + w - E[id].second;
            ans = min(ans, query(eid[id], 1, len, 1));
        }

        printf("%I64d\n", ans);
    }
    return 0;
}