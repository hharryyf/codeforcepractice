#include <bits/stdc++.h>
#define MAX_SIZE 1211
#define INF 1e9
typedef long long ll;
using namespace std;

struct edge {
	int from, to;
	ll flow, capacity;
};

// start and end point
int s, t;

// list array
vector<edge> edg;

// g reference to the ith vertex's edges
vector<int> g[MAX_SIZE];

// distance array and visited array
int dist[MAX_SIZE], visited[MAX_SIZE];
int cur[MAX_SIZE];
void addedge(int from, int to, int capacity) {
	edge e1 = edge{from, to, 0ll, capacity};
	edge e2 = edge{to, from, 0ll, 0ll};
	edg.push_back(e1), edg.push_back(e2);
	g[from].push_back((int) edg.size() - 2);
	g[to].push_back((int) edg.size() - 1);
}

// construct the level graph
bool bfs() {
	memset(visited,0,sizeof(visited));
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

ll dfs(int x, ll cp) {
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
				edg[g[x][y] ^1].flow -= newflow;
				flow += newflow;
				cp -= newflow;
				
				if (cp == 0) {
					break;
				}
			}
		}
	}
	
	return flow;
}

ll Dinic(){
    ll flow=0;
    while(bfs()){
        memset(cur,0,sizeof(cur));
        flow += dfs(s,INF);
    }
    return flow;
}


int main() {
	int n, m, k, i;
	scanf("%d%d%d", &n, &m, &k);
	// edge s and s'
	addedge(1, 2, n);
	// edge s and s''
	addedge(1, 3, k);
	// edges between 2 and the n heros
	for (i = 4; i < n + 4; i++) {
		addedge(2, i, 1);	
	}
	
	for (i = 4; i < n + 4; i++) {
		addedge(3, i, 1);
	}
	
	// i refers to 3 + i, we need to add edges between 3 + i and n + 3 + k
	for (i = 1; i <= n; i++) {
		int t;
		scanf("%d", &t);
		for (int j = 1; j <= t; j++) {
			int v;
			scanf("%d", &v);
			addedge(3 + i, n + 3 + v, 1);
		}
	}
	
	for (i = 1; i <= m; i++) {
		addedge(3 + n + i, 4 + n + m, 1);
	}
	
	s = 1, t = 4 + n + m;
	printf("%lld\n", Dinic());
	return 0;
}
