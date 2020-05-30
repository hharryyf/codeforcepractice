#include <bits/stdc++.h>
#define MAX_SIZE 100011
typedef long long ll;
using namespace std;

const ll INF = 1e15;

struct edge {
    int from, to;
    ll w;
    bool operator < (edge other) const {
        return w < other.w;
    }
};

edge edg[MAX_SIZE];
vector<pair<int, ll>> g[MAX_SIZE];
ll dist[MAX_SIZE];
int origion[MAX_SIZE];
int n, k, m;
int portal[MAX_SIZE];
int f[MAX_SIZE];
int visited[MAX_SIZE];

void init() {
    int i;
    for (i = 0 ; i < MAX_SIZE; ++i) {
        f[i] = i;
        dist[i] = INF;
        origion[i] = i;
    }
}

int find(int x) {
    if (x == f[x]) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    x = find(x), y = find(y);
    f[x] = y;
}

void dijkstra() {
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
    int i;
    for (i = 1; i <= k; ++i) {
        dist[portal[i]] = 0;
        q.push(make_pair(0, portal[i]));
    }

    while (!q.empty()) {
        auto p = q.top();
        q.pop();
        if (visited[p.second]) continue;
        dist[p.second] = p.first;
        visited[p.second] = 1;
        for (auto np : g[p.second]) {
            int nv = np.first;
            if (!visited[nv] && dist[nv] > dist[p.second] + np.second) {
                dist[nv] = dist[p.second] + np.second;
                q.push(make_pair(dist[nv], nv));
                // origion records the starting point of the optimal shortest path
                origion[nv] = origion[p.second];
            }
        }
    }
}

ll kruskal() {
    int i;
    ll ret = 0;
    for (i = 1; i <= m; ++i) {
        if (find(edg[i].from) != find(edg[i].to)) {
            ret += edg[i].w;
            unionset(edg[i].from, edg[i].to);
        }
    }
    return ret;
}

int main() {
    int i;
    init();
    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; ++i) {
        scanf("%d%d%I64d", &edg[i].from, &edg[i].to, &edg[i].w);
        g[edg[i].from].emplace_back(edg[i].to, edg[i].w);
        g[edg[i].to].emplace_back(edg[i].from, edg[i].w);
    }

    scanf("%d", &k);
    for (i = 1; i <= k; ++i) {
        scanf("%d", &portal[i]);
    }

    dijkstra();
    
    for (i = 1; i <= m; ++i) {
        edg[i].w = dist[edg[i].from] + edg[i].w + dist[edg[i].to];
        edg[i].from = origion[edg[i].from];
        edg[i].to = origion[edg[i].to];
    }

    sort(edg + 1, edg + 1 + m);

    printf("%I64d\n", kruskal() + dist[1]);
    return 0;
}