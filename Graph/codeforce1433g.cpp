#include <bits/stdc++.h>
#define MAX_SIZE 1011
using namespace std;

const int inf = 100000000;
int dist[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE];
vector<pair<int, int>> g[MAX_SIZE];
int n;
struct road {
    int from, to;
};

road rd[MAX_SIZE], q[MAX_SIZE];

void dijkstra(int src) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push(make_pair(0, src));
    int i;
    for (i = 1; i <= n; ++i) {
        visited[i] = 0, dist[src][i] = inf;
    }

    dist[src][src] = 0;
    while (!q.empty()) {
        auto np = q.top();
        q.pop();
        if (visited[np.second]) continue;
        visited[np.second] = 1;
        dist[src][np.second] = np.first;
        for (auto nv : g[np.second]) {
            if (dist[src][nv.first] > nv.second + np.first) {
                dist[src][nv.first] = nv.second + np.first;
                q.push(make_pair(dist[src][nv.first], nv.first));
            } 
        }
    }
}

int main() {
    int m, k, i, j;
    scanf("%d%d%d", &n, &m, &k);
    for (i = 1; i <= m; ++i) {
        int w;
        scanf("%d%d%d", &rd[i].from, &rd[i].to, &w);
        g[rd[i].from].emplace_back(rd[i].to, w);
        g[rd[i].to].emplace_back(rd[i].from, w);
    }

    for (i = 1; i <= k; ++i) {
        scanf("%d%d", &q[i].from, &q[i].to);
    }

    for (i = 1; i <= n; ++i) dijkstra(i);
    
    long long ans = 1e13;
    for (i = 1; i <= m; ++i) {
        long long curr = 0;
        int u1 = rd[i].from, u2 = rd[i].to;
        for (j = 1; j <= k; ++j) {
            int v1 = q[j].from, v2 = q[j].to;
            curr = curr + min(min(dist[v1][u1] + dist[v2][u2], dist[v1][u2] + dist[v2][u1]), dist[v1][v2]);
            //cout << v1 << " " << v2 << " cost= " << min(dist[v1][u1] + dist[v2][u2], dist[v1][u2] + dist[v2][u1]) << endl;
        }
        ans = min(ans, curr);
        //cout << "choose " << u1 << " " << u2 << " res= " << curr << endl;
    }

    printf("%I64d\n", ans);
    return 0;
}