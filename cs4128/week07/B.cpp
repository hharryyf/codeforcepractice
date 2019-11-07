#include <bits/stdc++.h>
#define MAX_SIZE 360111

#define INF 500000000
typedef int ll;
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
	edge e1 = edge{from, to, 0, capacity};
	edge e2 = edge{to, from, 0, 0};
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

char str[611][611];
int idx[611][611];

int dx[4] = {1,0,0,-1};
int dy[4] = {0,-1,1,0};

int main() {
	int T, n, l;
	scanf("%d", &T);
	for (l = 1; l <= T; l++) {
		scanf("%d", &n);
		init();
		int i, j;
		s = 0, t = n * n + 2;
		for (i = 0; i < n; i++) {
			scanf("%s", str[i]);
		}
		
		if (n == 1) {
			printf("Case %d: 0\n", l);
			continue;
		}
		
		int ct = 1;
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if (i % 2 == 0 && j % 2 == 0) {
					idx[i][j] = ct++;
				} else if (i % 2 == 1 && j % 2 == 1) {
					idx[i][j] = ct++;
				} else {
					idx[i][j] = 0;
				}
			}
		}
		
		int th = ct - 1;
		
		for (i = 0 ; i < n; i++) {
			for (j = 0; j < n; j++) {
				if (idx[i][j] == 0) {
					idx[i][j] = ct++;
				}
			}
		}
		
		for (i = 0 ; i < n; i++) {
			for (j = 0 ; j < n; j++) {
				if (idx[i][j] <= th && str[i][j] == '#') {
					addedge(s, idx[i][j], 1);
					int k;
					for (k = 0; k < 4; k++) {
						int tx = dx[k] + i, ty = dy[k] + j;
						if (tx >= 0 && tx < n && ty >= 0 && ty < n) {
							if (str[tx][ty] == '#') {
								addedge(idx[i][j], idx[tx][ty], 1);
							}
						}
					}
				} else if (idx[i][j] > th && str[i][j] == '#') {
					addedge(idx[i][j], t, 1);
				}
				
			}			
		}
		
		printf("Case %d: %d\n", l, Dinic());
	}
	return 0;
}
