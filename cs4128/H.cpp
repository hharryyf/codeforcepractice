#include <bits/stdc++.h>
#define MAX_SIZE 711
#define INF 100000000000ll

using namespace std;
typedef long long ll;

struct edge {
	int from, to;
	ll flow, capacity;
};

int s, t;

vector<edge> edg;

vector<int> g[MAX_SIZE];

int dist[MAX_SIZE], visited[MAX_SIZE], cur[MAX_SIZE];

void init() {
	edg.clear();
	int i;
	for (i = 0 ; i < MAX_SIZE; i++) {
		g[i].clear();
	}
}

void addedge(int from, int to, ll cp) {
	edge e1 = edge{from, to, 0, cp};
	edge e2 = edge{to, from, 0, 0};
	edg.push_back(e1), edg.push_back(e2);
	g[from].push_back((int) edg.size() - 2);
	g[to].push_back((int) edg.size() - 1);
}

bool bfs() {
	memset(visited, 0, sizeof(visited));
	memset(dist, 0, sizeof(dist));
	queue<int> q;
	q.push(s);
	visited[s] = 1;
	dist[s] = 0;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int i = 0 ; i < (int) g[v].size(); i++) {
			edge &e = edg[g[v][i]];
			int nxt = e.to;
			if (!visited[nxt] && e.capacity > e.flow) {
				dist[nxt] = dist[v] + 1;
				q.push(nxt);
				visited[nxt] = 1;
			}
		}
	}
	
	return visited[t];
}

ll dfs(ll x, ll cp) {
	if (x == t || cp == 0) {
		return cp;
	}
	
	ll flow = 0, newflow;
	for (int &y = cur[x]; y < (int) g[x].size(); y++) {
		edge &e = edg[g[x][y]];
		if (dist[x] + 1 == dist[e.to]) {
			ll minn = min(cp, e.capacity - e.flow);
			newflow = dfs(e.to, minn);
			if (newflow > 0) {
				e.flow += newflow;
				edg[g[x][y] ^ 1].flow -= newflow;
				flow += newflow;
				cp -= newflow;
				if (cp == 0) break; 
			}
		}
	}
	
	return flow;
}

ll Dinic() {
	ll flow = 0;
	while (bfs()) {
		memset(cur, 0, sizeof(cur));
		flow += dfs(s, INF);
	}
	return flow;
}

int n;

vector<int> keys[MAX_SIZE];

int main() {
	scanf("%d", &n);
	
	int low = 1, high = n, i;
	for (i = 1; i <= n; i++) {
		int tt;
		scanf("%d", &tt);
		while (tt > 0) {
			int v;
			scanf("%d", &v);
			if (v > i) {
				keys[i].push_back(v);
			}
			tt--;
		}
	}
	cout << n << endl;
	int ans = 1;
	while (low <= high) {
		int mid = low + (high - low) / 2;
		init();
		s = 0;
		t = 2 * n + 2;
		for (int i = 1 ; i <= mid; i++) {
			if (keys[i].size()) {
				addedge(s, i, 1);
				addedge(s, i + n, 1);
			}
			
			
			for (auto kk : keys[i]) {
				if (kk <= mid) {		
					addedge(i + n, kk, 1);
					cout << "(" << i+n << " ," << kk << ")" << endl;
				}
			}
			
			addedge(i, t, 1);
			cout << "(" << i << " ," << t << ")" << endl;
		}
		
		cout << endl;
		
		if (mid == Dinic()) {
			ans = mid;
			low = mid + 1;
		} else {
			high = mid - 1;
		}
		
	}
	
	cout << ans << endl;
	return 0;
}
