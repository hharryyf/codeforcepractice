#include <bits/stdc++.h>
#define INF 20000000000
#define MAX_SIZE 1711

typedef long long ll;
using namespace std;

// spfa algorithm start from src, return false if there's a negative cycle
// the graph is directed.
ll dist[MAX_SIZE];
int visited[MAX_SIZE];
int rt[MAX_SIZE];
vector<pair<int, ll> > g[MAX_SIZE];
int n;

bool spfa(int src) {
	int i;
	for (i = 0; i <= n; i++) {
		dist[i] = INF;
		visited[i] = 0;
		rt[i] = 0;
	}
	
	dist[src] = 0ll;
	rt[src] = 1;
	queue<int> q;
	q.push(src);
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		visited[v] = 0;
		if (rt[v] >= n) return false;
		for (auto nextv : g[v]) {
			int nv = nextv.first;
			ll w = nextv.second;
			if (dist[nv] > dist[v] + w) {
				dist[nv] = dist[v] + w;
				if (!visited[nv]) {
					visited[nv] = 1;
					q.push(nv);
					rt[nv]++;
				}
			}
		}
	}
	return true;
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
	
	if (!spfa(s)) {
		printf("there's a negative cycle! the calculation is meaningless\n");
	} else {
		for (int i = 1; i <= n; i++) {
			printf("dist[%d] = %lld\n", i, dist[i]);
		}
	}
	return 0;
}
