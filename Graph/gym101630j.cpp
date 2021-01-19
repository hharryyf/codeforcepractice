#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma comment(linker, "/stack:200000000")
#include <bits/stdc++.h>
#define MAX_SIZE 3011
using namespace std;
typedef long long ll;
const ll inf = 1e16;
vector<pair<int, ll>> g[MAX_SIZE];
ll dist[MAX_SIZE];
int visited[MAX_SIZE];
int N, M, K;

ll dijkstra(ll wt) {
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
    memset(visited, 0, sizeof(visited));
    int i;
    for (i = 1; i <= N; ++i) dist[i] = inf;
    q.push({0, 1});
    while (!q.empty()) {
        auto curr = q.top();
        q.pop();
        if (curr.second == N) break;
        if (visited[curr.second]) continue;
        dist[curr.second] = min(curr.first, dist[curr.second]);
        visited[curr.second] = 1;
        for (auto np : g[curr.second]) {
            int nv = np.first;
            ll w = max(0ll, np.second - wt);
            if (!visited[nv] && dist[nv] > dist[curr.second] + w) {
                dist[nv] = dist[curr.second] + w;
                q.push({dist[nv], nv});
            }
        }
    }
    return dist[N];
}

int main() {
    int i;
    scanf("%d%d%d", &N, &M, &K);
    set<int> wt;
    for (i = 1; i <= M; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
        wt.insert(w);
    }

    ll ans = dijkstra(0);
    for (auto w : wt) {
        ans = min(ans, dijkstra(w) + 1ll * K * w);
    }

    cout << ans << endl;
    return 0;
}