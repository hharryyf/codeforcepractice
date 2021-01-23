#include <bits/stdc++.h>
#define MAX_SIZE 611
using namespace std;
typedef long long ll;
const ll INF = 1e13;

struct Maxflow {
    struct edge {
        int from, to;
        ll flow, capacity;
    };

    int s, t;

    vector<edge> edg;

    vector<int> g[MAX_SIZE];

    int dist[MAX_SIZE], visited[MAX_SIZE], cur[MAX_SIZE];

    void init() {
        edg.clear();
        int i;
        for (i = 0 ; i < MAX_SIZE; ++i) {
            g[i].clear();
        }
    }

    void addedge(int from, int to, ll capacity) {
        edge e1 = edge{from, to, 0ll, capacity};
        edge e2 = edge{to, from, 0ll, 0ll};
        edg.push_back(e1);
        edg.push_back(e2);
        g[from].push_back((int) edg.size() - 2);
        g[to].push_back((int) edg.size() - 1);
    }

    bool bfs() {
        memset(visited, 0, sizeof(visited));
        memset(dist, 0, sizeof(dist));
        queue<int> q;
        q.push(s);
        visited[s] = 1;
        dist[s] = 0;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int i = 0 ; i < (int) g[v].size(); ++i) {
                edge &e = edg[g[v][i]];
                int nxt = e.to;
                if (!visited[nxt] && e.capacity > e.flow) {
                    dist[nxt] = dist[v] + 1;
                    q.push(nxt);
                    visited[nxt] = 1;
                }
            }
        }

        return visited[t];
    }

    ll dfs(int x, ll cp) {
        if (x == t || cp == 0) return cp;
        ll flow = 0, newflow;
        for (int &y = cur[x]; y < (int) g[x].size(); ++y) {
            edge &e = edg[g[x][y]];
            if (dist[x] + 1 == dist[e.to]) {
                ll minn = min(cp, e.capacity - e.flow);
                newflow = dfs(e.to, minn);
                if (newflow > 0) {
                    e.flow += newflow;
                    edg[g[x][y] ^ 1].flow -= newflow;
                    flow += newflow;
                    cp -= newflow;
                    if (cp == 0) break;
                }
            }
        }

        return flow;
    }

    ll Dinic() {
        ll flow = 0;
        while (bfs()) {
            memset(cur, 0, sizeof(cur));
            flow += dfs(s, INF);
        }
        return flow;
    }
};


vector<int> g[MAX_SIZE];
Maxflow mf;
int N;
char st[MAX_SIZE][32];
int visited[MAX_SIZE];


void dfs(int v) {
    for (auto nv : g[v]) {
        if (visited[nv] == -1) {
            visited[nv] = visited[v] ^ 1;
            dfs(nv);
        }
    }
}

int main() {
    mf.s = 0, mf.t = MAX_SIZE - 1;
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) {
        scanf("%s", st[i]);
        visited[i] = -1;
    }

    for (int i = 1; i <= N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            int cnt = 0;
            for (int k = 0; k < (int) strlen(st[i]); ++k) {
                if (st[i][k] != st[j][k]) cnt++;
            }

            if (cnt == 2) {
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
    }

    for (int i = 1; i <= N; ++i) {
        if (visited[i] == -1) {
            visited[i] = 0;
            dfs(i);
        }
    }

    for (int i = 1; i <= N; ++i) {
        if (visited[i] == 0) {
            mf.addedge(mf.s, i, 1);
            for (auto nv : g[i]) {
                mf.addedge(i, nv, INF);
            }
        } else {
            mf.addedge(i, mf.t, 1);
        }
    }

    cout << (1ll * N - mf.Dinic()) << endl;
    return 0;
}