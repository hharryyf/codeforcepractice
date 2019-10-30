#include <bits/stdc++.h>
#define MAX_SIZE 257
#define INF 10000000000000ll
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

void init() {
	edg.clear();
	int i;
	for (i = 0 ; i < MAX_SIZE; i++) {
		g[i].clear();
	}
}

void addedge(int from, int to, ll capacity) {
	edge e1 = edge{from, to, 0ll, capacity};
	edge e2 = edge{to, from, 0ll, 0ll};
	edg.push_back(e1), edg.push_back(e2);
	g[from].push_back((int) edg.size() - 2);
	g[to].push_back((int) edg.size() - 1);
}

// construct the level graph
bool bfs() {
	memset(visited,0,sizeof(visited));
	memset(dist,0,sizeof(dist));
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

int getin(int v) {
	return 2 * v;
}

int getout(int v) {
	return 1 + 2 * v;
}


int main() {
	int i, n, m, B, D;
	while (scanf("%d", &n) != EOF) {
		init();
		s = 1;
		t = 2 * n + 2;
		
		for (i = 1; i <= n; i++) {
			ll vcp;
			scanf("%lld", &vcp);
			addedge(getin(i), getout(i), vcp);
		}
		
		scanf("%d", &m);
		for (i = 0 ; i < m; i++) {
			int v1, v2;
			ll cap;
			scanf("%d%d%lld", &v1, &v2, &cap);
			addedge(getout(v1), getin(v2), cap);
		}
		
		scanf("%d%d", &B, &D);
		for (i = 1; i <= B; i++) {
			int v;
			scanf("%d", &v);
			addedge(s, getin(v), INF);
		}		
		
		for (i = 1; i <= D; i++) {
			int v;
			scanf("%d", &v);
			addedge(getout(v), t, INF);
		}
		
		cout << Dinic() << endl;
	}
	return 0;
}
