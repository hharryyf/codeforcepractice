#include <bits/stdc++.h>
#define MAX_SIZE 100111
#define INF 10000000000000ll
typedef long long ll;
using namespace std;

vector<pair<int, ll>> g[MAX_SIZE][2];
ll dist[MAX_SIZE][2];
int visited[MAX_SIZE][2];
void dijkstra(int src, int dim) {
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
	int i;
	for (i = 0; i < MAX_SIZE; ++i) dist[i][dim] = INF;
	q.push(make_pair(0, src));
	dist[src][dim] = 0;
	while (!q.empty()) {
		auto p = q.top();
		q.pop();
		if (visited[p.second][dim]) continue;
		visited[p.second][dim] = 1;
		dist[p.second][dim] = p.first;
		for (auto np : g[p.second][dim]) {
			int nv = np.first;
			ll cost = np.second;
			if (!visited[nv][dim]) {
				if (dist[nv][dim] > dist[p.second][dim] + cost) {
					dist[nv][dim] = dist[p.second][dim] + cost;
					q.push(make_pair(dist[nv][dim], nv));
				}
			}
		}
	}
}

pair<pair<int, int>, ll> edge[MAX_SIZE];
// the second graph that only consists the shortest path edges
// we need to make sure which one is a bridge
vector<pair<int, int>> g2[MAX_SIZE];
int ans[MAX_SIZE];
int vis[MAX_SIZE], low[MAX_SIZE];
int cnt = 1;
unordered_map<int, int> h[MAX_SIZE];

bool contains(int v1, int v2) {
	return h[v1].find(v2) != h[v1].end();
}

void dfs(int v, int pre) {
	low[v] = vis[v] = cnt;
	cnt++;
	for (auto np : g2[v]) {
		int id = np.second, nv = np.first;
		if (nv != pre) {
			if (!vis[nv]) {
				dfs(nv, v);
				low[v] = min(low[v], low[nv]);
				if (vis[v] < low[nv] && ans[id] != -1) {
					ans[id] = 1;
				}
			} else {
				low[v] = min(low[v], vis[nv]);
			}
		}
	}
}

int main() {
	int s, t, n, m, i;
	scanf("%d%d%d%d", &n, &m, &s, &t);
	for (i = 1; i <= m; ++i) {
		int v1, v2;
		ll w;
		scanf("%d%d%I64d", &v1, &v2, &w);
		edge[i] = make_pair(make_pair(v1, v2), w);
		g[v1][0].push_back(make_pair(v2, w));
		g[v2][1].push_back(make_pair(v1, w));
	}
	
	dijkstra(s, 0);
	dijkstra(t, 1);
	// the desired distance
	ll dst = dist[t][0];
	
	for (i = 1; i <= m; ++i) {
		if (dist[edge[i].first.first][0] + dist[edge[i].first.second][1] + edge[i].second == dst) {
			if (contains(edge[i].first.first, edge[i].first.second)) {
				ans[i] = -1;
				ans[h[edge[i].first.second][edge[i].first.first]] = -1;
			} else {
				g2[edge[i].first.first].emplace_back(edge[i].first.second, i);
				g2[edge[i].first.second].emplace_back(edge[i].first.first, i);
				h[edge[i].first.first][edge[i].first.second] = i;
				h[edge[i].first.second][edge[i].first.first] = i;
			}
		}
	}
	
	dfs(s, -1);
	
	for (i = 1; i <= m; ++i) {
		ll diff = dist[edge[i].first.first][0] + dist[edge[i].first.second][1] + edge[i].second - dst;
		if (diff == 0) {
			if (ans[i] == 1) {
				printf("YES\n");
			} else {
				if (edge[i].second > 1) {
					printf("CAN 1\n");
				} else {
					printf("NO\n");
				}
			}
		} else {
			if (edge[i].second > diff + 1) {
				printf("CAN %I64d\n", diff + 1);
			} else {
				printf("NO\n");
			}
		}
	}
	return 0;
}