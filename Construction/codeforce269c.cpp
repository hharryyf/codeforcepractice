#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

struct edge {
    int from, to, w, id, dir, ok;
};

vector<edge> edg;
vector<int> g[MAX_SIZE];
int ans[MAX_SIZE];
int flow[MAX_SIZE];
int visited[MAX_SIZE];

void addedge(int from, int to, int w, int id) {
    int sz = edg.size();
    edg.push_back(edge{from, to, w, id, 0, 1});
    g[from].push_back(sz++);
    edg.push_back(edge{to, from, w, id, 1, 1});
    g[to].push_back(sz++);
}



int main() {
    int i, n, m;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; ++i) {
        int from, to, w;
        scanf("%d%d%d", &from, &to, &w);
        flow[from] += w, flow[to] += w;
        addedge(from, to, w, i);
    }

    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (visited[v]) continue;
        visited[v] = 1;
        for (auto eid : g[v]) {
            edge &e = edg[eid];
            if (e.ok == 0) continue;
            ans[e.id] = e.dir;
            flow[e.to] -= 2 * e.w;
            edg[eid ^ 1].ok = 0;
            if (flow[e.to] == 0 && e.to != n) {
                q.push(e.to);
            }
        }
    }

    for (i = 1; i <= m; ++i) {
        printf("%d\n", ans[i]);
    }
    return 0;
}