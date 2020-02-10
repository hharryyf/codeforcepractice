#include <bits/stdc++.h>
#define MAX_SIZE 100111
#define INF 100000000
using namespace std;

// the problem is equivalent to finding the
// length of the shortest path from s to t
// and among those paths, find the path with
// most amount of 1 edge
vector<int> g[MAX_SIZE];
vector<pair<int, int>> dag[MAX_SIZE];
struct edge {
    int from, to, tp;
};
int n, m;
vector<edge> edg;
bool visited[MAX_SIZE][2];
int dist[MAX_SIZE][2];

void BFS(int src, int dim) {
    int i;
    queue<pair<int, int>> q;
    for (i = 1; i <= n; i++) {
        dist[i][dim] = INF;
    }
    
    dist[src][dim] = 0;
    q.push(make_pair(src, 0));
    while (!q.empty()) {
        int v = q.front().first;
        int ds = q.front().second;
        q.pop();
        if (visited[v][dim]) continue;
        visited[v][dim] = true, dist[v][dim] = ds;
        for (auto nv : g[v]) {
            if (!visited[nv][dim]) {
                q.push(make_pair(nv, ds + 1));
            }
        }
    }
}

int dis[MAX_SIZE], pre[MAX_SIZE];
bool vis[MAX_SIZE];
set<pair<int, int>> rd;

void dijkstra() {
    int i;
    for (i = 1; i <= n; i++) dis[i] = INF;
    dis[1] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push(make_pair(0, 1));
    while (!q.empty()) {
        int v = q.top().second;
        int ds = q.top().first;
        q.pop();
        if (vis[v]) continue;
        vis[v] = true;
        dis[v] = ds;
        for (auto np : dag[v]) {
            if (!vis[np.first] && np.second + ds <= dis[np.first]) {
                q.push(make_pair(ds + np.second, np.first));
                dis[np.first] = ds + np.second;
                pre[np.first] = v;
            }
        }
    }
    
    int curr = n;
    while (curr > 1) {
        rd.insert(make_pair(curr, pre[curr]));
        curr = pre[curr];        
    }
}

int main() {
    scanf("%d%d", &n, &m);
    int i;
    for (i = 1; i <= m; i++) {
        int v1, v2, tp;
        scanf("%d%d%d", &v1, &v2, &tp);
        g[v1].push_back(v2);
        g[v2].push_back(v1);
        edg.push_back(edge{v1, v2, tp});
    }
    
    BFS(1, 0);
    BFS(n, 1);
    
    for (auto e : edg) {
        if (dist[e.from][0] + 1 + dist[e.to][1] == dist[n][0]) {
            dag[e.from].emplace_back(e.to, 1 - e.tp);
        } else if (dist[e.to][0] + 1 + dist[e.from][1] == dist[n][0]) {
            dag[e.to].emplace_back(e.from, 1 - e.tp);
        }
    }
    dijkstra();
    vector<edge> ret;
    for (auto e : edg) {
        set<pair<int, int>> :: iterator iter = rd.find(make_pair(e.from, e.to));
        if (iter != rd.end()) {
            if (e.tp == 0) {
                ret.push_back(edge{e.from, e.to, 1});
            }
            continue;
        } 
        iter = rd.find(make_pair(e.to, e.from));
        if (iter != rd.end()) {
            if (e.tp == 0) {
                ret.push_back(edge{e.from, e.to, 1});
            }
            continue;
        }
        
        if (e.tp == 1) {
            ret.push_back(edge{e.from, e.to, 0});
        }
    }
    
    printf("%d\n", (int) ret.size());
    for (auto e : ret) {
        printf("%d %d %d\n", e.from, e.to, e.tp);
    }
    return 0;
}
