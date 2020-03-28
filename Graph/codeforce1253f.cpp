#include <bits/stdc++.h>
#define MAX_SIZE 300111
#define INF 1000000000000000ll
typedef long long ll;
using namespace std;


struct edge {
	int from, to;
	ll w;
	bool operator < (edge other) const {
		return w < other.w;
	}
};

vector<pair<int, ll>> g[MAX_SIZE];
int n, m, k, q;
int f[MAX_SIZE];
int parent[MAX_SIZE][19];
ll val[MAX_SIZE];
edge edg[MAX_SIZE];
ll dist[MAX_SIZE];
int visited[MAX_SIZE];

int find(int x) {
	if (x == f[x]) return x;
	return f[x] = find(f[x]);
}

void dijkstra() {
	int i;
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
	for (i = k+1; i <= n; ++i) dist[i] = INF;
	for (i = 1; i <= k; ++i) {
		q.push(make_pair(0, i));
	}
	
	while (!q.empty()) {
		auto p = q.top();
		q.pop();
		if (visited[p.second]) continue;
		visited[p.second] = 1;
		dist[p.second] = p.first;
		for (auto np : g[p.second]) {
			int nv = np.first;
			ll cost = np.second;
			if (!visited[nv]) {
				if (cost + dist[p.second] < dist[nv]) {
					dist[nv] = cost + dist[p.second];
					q.push(make_pair(dist[nv], nv));
				}
			}
		} 
	}
}

int height[MAX_SIZE];
vector<int> t[MAX_SIZE];
void dfs(int v) {
	int i;
	for (i = 1; i <= 18; ++i) {
		parent[v][i] = parent[parent[v][i-1]][i-1];
	}
	
	for (auto nv : t[v]) {
		height[nv] = height[v] + 1;
		dfs(nv);
	}
}

void kruskal_modification() {
	int i;
	int idx = n + 1;
	sort(edg + 1, edg + m +	1);
	for (i = 1; i <= m; ++i) {
		int x = find(edg[i].from), y = find(edg[i].to);
		if (x == y) continue;
		f[x] = idx, f[y] = idx;
		parent[x][0] = idx, parent[y][0] = idx;
		t[idx].push_back(x);
		t[idx].push_back(y);
		val[idx] = edg[i].w;
		idx++;
	}
	
	dfs(idx - 1);
}

int LCA(int u, int v) {
	if (height[u] < height[v]) swap(u, v);
	int i;
	for (i = 18; i >= 0; i--) {
		if (height[u] >= height[v] + (1 << i)) u = parent[u][i];
	}
	if (u == v) return u;
	
	for (i = 18; i >= 0; i--) {
		if (parent[u][i] != parent[v][i]) {
			u = parent[u][i];
			v = parent[v][i];
		}
	}
	return parent[u][0];
}

int main() {
	int i;
	scanf("%d%d%d%d", &n, &m, &k, &q);
	
	for (i = 1; i <= m; ++i) {
		scanf("%d%d%I64d", &edg[i].from, &edg[i].to, &edg[i].w);
		g[edg[i].from].emplace_back(edg[i].to, edg[i].w);
		g[edg[i].to].emplace_back(edg[i].from, edg[i].w);
	}
	
	dijkstra();
	
	for (i = 0 ; i < MAX_SIZE; ++i) f[i] = i;
	
	for (i = 1; i <= m; ++i) edg[i].w = edg[i].w + dist[edg[i].from] + dist[edg[i].to];
	
	kruskal_modification();
	
	while (q > 0) {
		int u, v;
		scanf("%d%d", &u, &v);
		printf("%I64d\n", val[LCA(u, v)]);
		q--;
	}
	return 0;
}