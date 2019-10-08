#include <bits/stdc++.h>
#define MAX_SIZE 100011
#define INF 200000000000000ll
typedef long long ll;
using namespace std;

unordered_set<int> hs;
vector<int> special;
ll dist[42][MAX_SIZE];
bool visited[42][MAX_SIZE];
ll depth[MAX_SIZE];
int parent[MAX_SIZE][21];
int height[MAX_SIZE];
// union find array
int f[MAX_SIZE];
// special edges
vector<pair<pair<int, int>, ll> > edg;

vector<pair<int, ll> > g[MAX_SIZE];

int logs[MAX_SIZE];

int n;

void precompute() {
	int i;
	logs[0] = logs[1] = 0;
	f[1] = 1;
	for (i = 2 ; i <= n; i++) {
		logs[i] = logs[i/2] + 1;
		f[i] = i;
	}
}


int find(int x) {
	if (f[x] == x) return x;
	return f[x] = find(f[x]);
}

void unionset(int a, int b) {
	int x = find(a), y = find(b);
	if ((x + y) % 2 == 0) {
		f[x] = y;
	} else {
		f[y] = x;
	}
}

void dijkstra(int src, int dim) {
	int i;
	for (i = 0 ; i < MAX_SIZE; i++) {
		dist[dim][i] = INF;
	}
	dist[dim][src] = 0ll;
	priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > q;
	q.push(make_pair(0ll, src));
	while (!q.empty()) {
		pair<ll, int> p = q.top();
		q.pop();
		if (visited[dim][p.second]) continue;
		visited[dim][p.second] = 1;
		dist[dim][p.second] = p.first;
		for (auto nextp : g[p.second]) {
			if (!visited[dim][nextp.first] && dist[dim][nextp.first] > dist[dim][p.second] + nextp.second) {
				q.push(make_pair(dist[dim][p.second] + nextp.second, nextp.first));
				dist[dim][nextp.first] = dist[dim][p.second] + nextp.second;
			}
		}
	}
}

void dfs(int v, ll wt, int ht, int pre) {
	int i;
	parent[v][0] = pre;
	for (i = 1; i <= logs[n]; i++) {
		parent[v][i] = parent[parent[v][i-1]][i-1];
	}
	depth[v] = wt;
	height[v] = ht;
	for (auto nextp : g[v]) {
		int nv = nextp.first;
		ll nw = nextp.second;
		if (nv != pre) {
			dfs(nv, wt + nw, ht + 1, v);
		}
	}
}

int LCA(int u, int v) {
	if (height[u] < height[v]) swap(u, v);
	
	int i;
	for (i = logs[n]; i >= 0; i--) {
		if (height[u] >= height[v] + (1 << i)) {
			u = parent[u][i];
		}
	}
	
	if (u == v) return u;
	
	for (i = logs[n]; i >= 0; i--) {
		if (parent[u][i] != parent[v][i]) {
			u = parent[u][i];
			v = parent[v][i];
		}
	}
	
	return parent[u][0];
}

ll mindist(int u, int v) {
	ll ret = depth[u] + depth[v] - 2ll * depth[LCA(u, v)];
	int k = (int) special.size();
	
	for (int i = 0; i < k; i++) {
		ret = min(ret, dist[i][u] + dist[i][v]);
	}
	return ret;
}

int main(int argc, char *argv[]) {
	int m, i;
	scanf("%d%d", &n, &m);
	precompute();
	for (i = 0 ; i < m; i++) {
		int v1, v2;
		ll w;
		scanf("%d%d%lld", &v1, &v2, &w);
		if (find(v1) != find(v2)) {
			g[v1].push_back(make_pair(v2, w));
			g[v2].push_back(make_pair(v1, w));
			unionset(v1, v2);
		} else {
			edg.push_back(make_pair(make_pair(v1, v2), w));
			if (hs.find(v1) == hs.end()) {
				special.push_back(v1);
				hs.insert(v1);
			}
			
			if (hs.find(v2) == hs.end()) { 
				special.push_back(v2);
				hs.insert(v2);
			}
		}
	}
	
	dfs(1, 0ll, 0, 0);
	
	for (auto e : edg) {
		g[e.first.first].push_back(make_pair(e.first.second, e.second));
		g[e.first.second].push_back(make_pair(e.first.first, e.second));
	}
	
	for (i = 0 ; i < (int) special.size(); i++) {
		dijkstra(special[i], i);
	}
	/*
	for (i = 0 ; i < (int) special.size(); i++) {
		cout << special[i] << ": ";
		for (int j = 1; j <= n; j++) {
			cout << dist[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;*/
	int q;
	scanf("%d", &q);
	while (q > 0) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		printf("%lld\n", mindist(v1, v2));
		q--;
	}
	return 0;
}
