#include <bits/stdc++.h>
#define MAX_SIZE 200005
using namespace std;
typedef long long ll;

struct Edge {
	int x, y;
	ll dist;
};

vector<pair<int, ll>  > graph[MAX_SIZE];

vector<Edge> edges, edges2;

// weight of largest edge of v and up for at most (1 << i)
ll pmax[MAX_SIZE][21];

// parent[v][i] = the (1 << i) the parent of node v
int parent[MAX_SIZE][21];

int height[MAX_SIZE];
int logs[MAX_SIZE];

int n, m;

int f[MAX_SIZE];
vector<int> tour;

void precompute() {
	logs[0] = logs[1] = 0;
	for (int i = 2; i <= n; i++) {
		logs[i] = logs[i / 2] + 1;
	}
}

static bool cmp(const Edge &a, const Edge &b) {
	return a.dist < b.dist;
}

int find(int x) {
	if (f[x] == x) return f[x];
	return f[x] = find(f[x]);
}

void unionset(int a, int b) {
	int x = find(a), y = find(b);
	f[x] = y;
}

ll Kruskal() {
	sort(edges.begin(), edges.end(), cmp);
	for (int i = 0; i <= n; i++) {
		f[i] = i;
	}
	ll curr = 0ll;
	for (auto e : edges) {
		int x = e.x, y = e.y;
		ll w = e.dist;
		if (find(x) != find(y)) {
			graph[x].push_back(make_pair(y, w));
			graph[y].push_back(make_pair(x, w));
			unionset(x, y);
			curr += w;
		}
	}
	return curr;
}

void dfs(int v, int pd, int dps) {
	height[v] = dps;
	parent[v][0] = pd;
	int i;
	for (i = 1; i <= logs[n]; i++) {
		parent[v][i] = parent[parent[v][i-1]][i-1]; 
		pmax[v][i] = max(pmax[parent[v][i-1]][i-1], pmax[v][i-1]); 
	}
	
	for (auto nextp : graph[v]) {
		int nextv = nextp.first;
		ll wt = nextp.second;
		if (pd != nextv) {
			pmax[nextv][0] = wt;	
			dfs(nextv, v, dps + 1);
		}
	}
}

ll LCA(int u, int v) {
	if (height[u] < height[v]) {
		swap(u, v);
	}
	
	int i;
	ll ans = 0ll;
	for (i = logs[n]; i >= 0; i--) {
		if (height[u] >= height[v] + (1 << i)) {
			ans = max(ans, pmax[u][i]);
			u = parent[u][i];
		}
	}
	
	if (u == v) {
		return ans;
	}
	
	for (i = logs[n]; i >= 0; i--) {
		if (parent[u][i] != parent[v][i]) {
			ans = max(ans, max(pmax[u][i], pmax[v][i]));
			u = parent[u][i];
			v = parent[v][i];
		}
	}
	
	ans = max(ans, max(pmax[u][0], pmax[v][0]));
	return ans;
}

int main() {
	scanf("%d%d", &n, &m);
	precompute();
	
	for (int i = 0 ; i < m; i++) {
		int v1, v2;
		ll w;
		scanf("%d%d%lld", &v1, &v2, &w);
		edges.push_back(Edge{v1, v2, w});
		edges2.push_back(Edge{v1, v2, w});
	}
	
	ll mst = Kruskal();
	
	
	dfs(1, 0, 0);
	/*
	for (int i = 1; i <= n; i++) {
		cout << i << ": ";
		for (int j = 0; j <= logs[n]; j++) {
			cout << parent[i][j] << ", " << pmax[i][j] << "->";
		}
		cout << endl;
	}*/
	
	for (auto e : edges2) {
		printf("%lld\n", mst - LCA(e.x, e.y) + e.dist);
	}
	return 0;
}
