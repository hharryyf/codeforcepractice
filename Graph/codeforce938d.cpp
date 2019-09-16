#include <bits/stdc++.h>
#define MAX_SIZE (200000 + 11)
typedef long long ll;

using namespace std;

vector<pair<int, ll> > graph[MAX_SIZE];

int visited[MAX_SIZE];

vector<ll> dist;
// in this problem, we can add a virtual vertex called vertex 0 and connect
// all the other vertices with it and the corresponding weight is arr[i]
// we double the edge weight of the other edges
// and run dijkstra on vertex 0
void dijkstra(int n) {
	dist = vector<ll>(n + 1, 2400000000000000000ll);		
	priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > q;
	q.push(make_pair(0ll,0));
	visited[0] = 1;
	dist[0] = 0ll;
	int index = -1;
	ll currdist;
	for (auto nextv : graph[0]) {
		q.push(make_pair(nextv.second, nextv.first));
	}
	
	for (int i = 1; i <= n; i++) {
		index = -1;
		currdist = -1;
		while (!q.empty()) {
			pair<ll, int> p = q.top();
			q.pop();
			if (!visited[p.second]) {
				currdist = p.first;
				index = p.second;
				break;
			} 
		}
		// cout << index << " " << currdist << endl;
		if (index == -1) break;
		dist[index] = currdist;
		visited[index] = 1;
		
		for (auto nextv : graph[index]) {
			if (!visited[nextv.first] && (dist[index] + nextv.second < dist[nextv.first])) {
				dist[nextv.first] = dist[index] + nextv.second;
				q.push(make_pair(dist[nextv.first], nextv.first));
			}
		}
	}
}

int main(int argc, char *argv[]) {
	int n, m, i;
	scanf("%d%d", &n, &m);
	for (i = 0 ; i < m; i++) {
		int v1, v2;
		ll w;
		scanf("%d%d%lld", &v1, &v2, &w);
		graph[v1].push_back(make_pair(v2, 2ll * w));
		graph[v2].push_back(make_pair(v1, 2ll * w));
	}
	
	for (i = 1; i <= n; i++) {
		ll w;
		scanf("%lld", &w);
		graph[0].push_back(make_pair(i, w));
		graph[i].push_back(make_pair(0, w));
	}
	
	dijkstra(n);
	
	for (i = 1; i <= n; i++) {
		printf("%lld ", dist[i]);
	}
	cout << endl;
	return 0;
}
