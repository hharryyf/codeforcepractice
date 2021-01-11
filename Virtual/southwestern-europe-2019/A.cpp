#include <bits/stdc++.h>
#define MAX_SIZE 1011
using namespace std;

const int inf = 1000000000;

struct vertex {
    int id, b, cost;
    bool operator < (vertex other) const {
        return cost > other.cost;
    }
};

int N, B, T;
int x[MAX_SIZE], y[MAX_SIZE];
vector<vertex> g[MAX_SIZE];
int dist[MAX_SIZE][102];
int c[MAX_SIZE], visited[MAX_SIZE][102];

int getdist(int v, int u) {
    return ceil(sqrt((x[u] - x[v]) * (x[u] - x[v]) + (y[u] - y[v]) * (y[u] - y[v])));
}

int main() {
    scanf("%d%d", &x[0], &y[0]);
    int xt, yt, i, j;
    scanf("%d%d", &xt, &yt);
    scanf("%d", &B);
    scanf("%d", &c[0]);
    scanf("%d", &T);
    for (i = 1; i <= T; ++i) scanf("%d", &c[i]);
    scanf("%d", &N);
    x[N + 1] = xt, y[N + 1] = yt;
    for (i = 1; i <= N; ++i) {
        int v;
        scanf("%d%d%d", &x[i], &y[i], &v);
        while (v-- > 0) {
            int id, m;
            scanf("%d%d", &id, &m);
            id++;
            g[i].push_back(vertex{id, 0, c[m]});
            g[id].push_back(vertex{i, 0, c[m]});
        }
    }

    for (i = 1; i <= N; ++i) {
        for (j = 0; j < (int) g[i].size(); ++j) {
            int budget = getdist(i, g[i][j].id);
            g[i][j].b = budget;
            g[i][j].cost *= budget;
        }
    }

    for (i = 0; i <= N+1; ++i) {
        int budget = getdist(0, i);
        g[0].push_back(vertex{i, budget, c[0] * budget});
        budget = getdist(N+1, i);
        g[i].push_back(vertex{N+1, budget, c[0] * budget});
    }

    N++;
    for (i = 0; i <= N; ++i) {
        for (j = 0; j <= B; ++j) {
            dist[i][j] = inf;
        }
    }

    dist[0][0] = 0;
    priority_queue<vertex> q;
    q.push(vertex{0, 0, 0});
    while (!q.empty()) {
        auto curr = q.top();
        q.pop();
        if (visited[curr.id][curr.b]) continue;
        visited[curr.id][curr.b] = 1;
        dist[curr.id][curr.b] = min(dist[curr.id][curr.b], curr.cost);
        // cout << "relax " << curr.id << " " << curr.b << " dist= " << curr.cost << endl;
        for (auto nv : g[curr.id]) {
            int nb = nv.b + curr.b;
            int w = nv.cost;
            if (nb > B) continue;
            if (visited[nv.id][nb]) continue;
            if (dist[nv.id][nb] > curr.cost + w) {
                dist[nv.id][nb] = curr.cost + w;
                q.push(vertex{nv.id, nb, curr.cost + w});
            }
        }
    }

    int ans = inf;
    for (i = 0 ; i <= B; ++i) {
        ans = min(ans, dist[N][i]);
    }

    if (ans < inf) {
        printf("%d\n", ans);
    } else {
        printf("-1\n");
    }
    return 0;
}