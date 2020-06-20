#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 3011
using namespace std;

const int inf = 1e6;
int dist[MAX_SIZE][MAX_SIZE];
bool visited[MAX_SIZE];
vector<int> g[MAX_SIZE];

void BFS(int src) {
    queue<int> q;
    q.push(src);
    dist[src][src] = 0;
    memset(visited, 0, sizeof(visited));
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (visited[v]) continue;
        visited[v] = 1;
        for (auto nv : g[v]) {
            if (!visited[nv]) {
                q.push(nv);
                dist[src][nv] = min(dist[src][nv], dist[src][v] + 1);
            }
        }
    }
}

int main() {
    int n, m, i, j;
    int ans = 0;
    scanf("%d%d", &n, &m);
    memset(dist, inf, sizeof(dist));
    
    for (i = 1; i <= m; ++i) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        g[v1].push_back(v2);
        g[v2].push_back(v1);
    }

    for (i = 1; i <= n; ++i) {
        BFS(i);
    }

    int s1, t1, T1, s2, t2, T2;
    scanf("%d%d%d", &s1, &t1, &T1);
    scanf("%d%d%d", &s2, &t2, &T2);
    // cout << dist[s1][t1] << " " << dist[s2][t2]  << endl;
    if (dist[s1][t1] > T1 || dist[s2][t2] > T2) {
        printf("-1\n");
        return 0;
    }

    ans = max(0, m - (dist[s1][t1] + dist[s2][t2]));

    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= n;  ++j) {
            // s1->i->j->t1, s2->i->j->t2
            if (dist[i][j] + dist[s1][i] + dist[j][t1] > T1 || dist[i][j] + dist[s2][i] + dist[j][t2] > T2) continue;
            ans = max(ans, m - dist[i][j] - dist[s1][i] - dist[j][t1] - dist[s2][i] - dist[j][t2]);
        }
    }

    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= n;  ++j) {
            // s1->i->j->t1, t2->i->j->s2, cover all cases
            if (dist[i][j] + dist[s1][i] + dist[j][t1] > T1 || dist[i][j] + dist[t2][i] + dist[j][s2] > T2) continue;
            ans = max(ans, m - dist[i][j] - dist[s1][i] - dist[j][t1] - dist[t2][i] - dist[j][s2]);
        }
    }

    printf("%d\n", ans);
    return 0;
}