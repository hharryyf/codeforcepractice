#include <bits/stdc++.h>
#define INF 20000000000ll
#define MAX_SIZE 100111

typedef long long ll;
using namespace std;


ll dist[MAX_SIZE];
int visited[MAX_SIZE];
vector<pair<int, ll> > g[MAX_SIZE];
int n;

void dijkstra(int src) {
	priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > q;
	q.push(make_pair(0, src));
	for (int i = 1; i <= n; i++) {
		dist[i] = INF;
	}
	
	dist[src] = 0;
	
	while (!q.empty()) {
		pair<ll, int> p = q.top();
		q.pop();
		if (visited[p.second]) continue;
		visited[p.second] = 1;
		dist[p.second] = p.first;
		for (auto nextv : g[p.second]) {
			int v = nextv.first;
			ll w = nextv.second;
			if ((dist[v] > dist[p.second] + w) && (!visited[v])) {
				dist[v] = dist[p.second] + w;
				q.push(make_pair(dist[p.second] + w, v));
			}
		}
	}
}

int main() {
	int m, s;
	scanf("%d%d%d", &n, &m, &s);
	while (m > 0) {
		int v1, v2;
		ll w;
		scanf("%d%d%lld", &v1, &v2, &w);
		g[v1].push_back(make_pair(v2, w));
		m--;
	}
	
	dijkstra(s);
	for (int i = 1; i <= n; i++) {
		printf("dist[%d] = %lld\n", i, dist[i]);
	}
	return 0;
}
