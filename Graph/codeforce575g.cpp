#include <bits/stdc++.h>
#define MAX_SIZE 100111
using namespace std;

vector<pair<int, int>> g[MAX_SIZE];
// very important here!
vector<int> zero[MAX_SIZE];
// g2 is a shortest path dag from target -> src
vector<pair<int, int>> g2[MAX_SIZE];
struct edge {
    int from, to, wt;
};

edge edg[MAX_SIZE];
int dist[MAX_SIZE][2], dist2[MAX_SIZE];
int visited[MAX_SIZE], conn[MAX_SIZE], pre[MAX_SIZE], pcost[MAX_SIZE];
pair<int, int> cost[MAX_SIZE];
int n, m;
const int INF = 1e8;

void dijkstra(int src, int dim) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    int i;
    for (i = 0 ; i < MAX_SIZE; ++i) visited[i] = 0, dist[i][dim] = INF;
    dist[src][dim] = 0;
    q.push(make_pair(0, src));
    while (!q.empty()) {
        auto p = q.top();
        q.pop();
        if (visited[p.second]) continue;
        visited[p.second] = 1;
        for (auto np : g[p.second]) {
            if (!visited[np.first] && np.second + dist[p.second][dim] < dist[np.first][dim]) {
                dist[np.first][dim] = np.second + dist[p.second][dim];
                q.push(make_pair(dist[np.first][dim], np.first));
            }
        }
    }
}

void init() {
    pre[n - 1] = -1;
    // first BFS on the zero graph
    queue<int> q;
    for (int i = 0 ; i < MAX_SIZE; ++i) dist2[i] = INF;
    dist2[n - 1] = 0;
    q.push(n - 1);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (visited[v]) continue;
        visited[v] = 1;
        conn[v] = 1;
        for (auto nv : zero[v]) {
            if (!visited[nv]) {
                if (dist2[nv] > dist2[v] + 1) {
                    dist2[nv] = min(dist2[nv], dist2[v] + 1);
                    pre[nv] = v;
                    q.push(nv);
                }
            }
        }
    }
}

int main() {
    int i;
    scanf("%d%d", &n, &m);

    for (i = 1; i <= m; ++i) {
        scanf("%d%d%d", &edg[i].from, &edg[i].to, &edg[i].wt);
        if (edg[i].wt == 0) {
            zero[edg[i].from].push_back(edg[i].to);
            zero[edg[i].to].push_back(edg[i].from);
        }
    }

    init();
    for (i = 1; i <= m; ++i) {
        int u = edg[i].from, v = edg[i].to;
        if (conn[u] && conn[v]) {
            g[u].emplace_back(v, 0);
            g[v].emplace_back(u, 0);
        } else {
            g[u].emplace_back(v, 1);
            g[v].emplace_back(u, 1);
        }
    }

    dijkstra(0, 0);
    dijkstra(n - 1, 1);

    for (i = 1; i <= m; ++i) {
        if ((!conn[edg[i].from] || !conn[edg[i].to])) {
            int u = edg[i].from, v = edg[i].to;
            if (dist[u][0] + 1 + dist[v][1] == dist[0][1]) {
                g2[v].emplace_back(u, edg[i].wt);
                // cout << "addedge " << v << " " << u << " wt= " << edg[i].wt << endl;
            }   

            if (dist[u][1] + 1 + dist[v][0] == dist[0][1]) {
                g2[u].emplace_back(v, edg[i].wt);
                // cout << "addedge " << u << " " << v << " wt= " << edg[i].wt << endl;
            }
        }
    }

    vector<int> curr, nxt;
    for (i = 0 ; i < n; ++i) {
        cost[i].first = cost[i].second = INF;
        if (conn[i]) {
            curr.push_back(i);
            cost[i].first = 0, cost[i].second = dist2[i];
            // cout << "i= " << i << endl;
        }
        visited[i] = 0;
    }
    
    while (!curr.empty()) {
        for (auto v : curr) {
            visited[v] = 1;
            for (auto np : g2[v]) {
                int nv = np.first, w = np.second;
                if (!visited[nv]) {
                    if (cost[nv].first > w || (cost[nv].first == w && cost[nv].second > cost[v].second)) {
                        nxt.push_back(nv);
                        cost[nv].first = w;
                        cost[nv].second = cost[v].second;
                        pre[nv] = v;
                        pcost[nv] = w;
                    }
                }
            }
        }

        int mn = INF;
        for (auto v : nxt) {
            mn = min(mn, cost[v].first);
        }
        curr.clear();
        for (auto v : nxt) {
            if (cost[v].first == mn) curr.push_back(v);
        }
        nxt.clear();
    }
    
    vector<int> ret;
    vector<int> path;
    int v = 0;
    while (v != -1) {
        path.push_back(v);
        ret.push_back(pcost[v]);
        v = pre[v];
        // printf("%d\n", v);
    }

    while ((int) ret.size() > 1 && ret.back() == 0) {
        ret.pop_back();
    }

    reverse(ret.begin(), ret.end());
    for (auto nv : ret) {
        printf("%d", nv);
    }
    printf("\n%d\n", (int) path.size());
    for (auto nv : path) {
        printf("%d ", nv);
    }
    printf("\n");
    return 0;
}