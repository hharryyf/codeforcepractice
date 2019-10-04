#include <bits/stdc++.h>
#define MAX_SIZE 300011
#define INF 400000000000000ll
typedef long long ll;

using namespace std;

vector<pair<int, ll> > g[MAX_SIZE];
vector<pair<int, int> > edges;

vector<ll> dist = vector<ll>(MAX_SIZE, INF);
vector<ll> lst = vector<ll>(MAX_SIZE, INF);

// prev = 0 means the node hasn't been explored yet
int pre[MAX_SIZE];
int visited[MAX_SIZE];
int n;

void dijkstra(int src) {
	priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > q;
	q.push(make_pair(0ll, src));
	while (!q.empty()) {
		pair<ll, int> curr = q.top();
		q.pop();
		if (visited[curr.second]) continue;
		visited[curr.second] = 1;
		dist[curr.second] = curr.first;
		for (auto nextp : g[curr.second]) {
			if (!visited[nextp.first]) {
				if (dist[nextp.first] > nextp.second + curr.first) {
					dist[nextp.first] = nextp.second + curr.first;
					pre[nextp.first] = curr.second;
					lst[nextp.first] = nextp.second;
					q.push(make_pair(dist[nextp.first], nextp.first));
				} else if (dist[nextp.first] == nextp.second + curr.first) {
					if (lst[nextp.first] > nextp.second) {
						pre[nextp.first] = curr.second;
						lst[nextp.first] = nextp.second;
					}
				}
			}
		}
	}
}

int main(int argc, char *argv[]) {
	int m, u;
	scanf("%d%d", &n, &m);
	while (m > 0) {
		int v1, v2;
		ll w;
		scanf("%d%d%lld", &v1, &v2, &w);
		g[v1].push_back(make_pair(v2, w));
		g[v2].push_back(make_pair(v1, w));
		edges.push_back(make_pair(v1, v2));
		m--;
	}
	
	scanf("%d", &u);
	dijkstra(u);
	
	ll ret = 0ll;
	for (int i = 1; i <= n; i++) {
		if (pre[i]) {
			ret += lst[i];
		}
	}
	
	cout << ret << endl;
	
	for (int i = 0 ; i < (int) edges.size(); i++) {
		if (pre[edges[i].first] == edges[i].second || pre[edges[i].second] == edges[i].first) {
			printf("%d ", i + 1);
		}
	}
	cout << endl;
	return 0;
}
