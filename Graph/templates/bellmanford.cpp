#include <bits/stdc++.h>
#define INF 20000000000ll
#define MAX_SIZE 1711

typedef long long ll;
using namespace std;

ll dist[MAX_SIZE];
vector<pair<int, ll> > g[MAX_SIZE];
int n;

void bellmanford(int src) {
	int i, j;
	for (i = 1; i <= n; i++) {
		dist[i] = INF;
	}
	dist[src] = 0ll;
	for (i = 0 ; i < n - 1; i++) {
		for (j = 1; j <= n; j++) {
			for (auto nextv : g[j]) {
				int v = nextv.first;
				ll w = nextv.second;
				dist[v] = min(dist[v], dist[j] + w);
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
	
	bellmanford(s);
	
	for (int i = 1; i <= n; i++) {
		printf("dist[%d] = %lld\n", i, dist[i]);
	}
	return 0;
}
