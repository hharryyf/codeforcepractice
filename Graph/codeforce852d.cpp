#include <bits/stdc++.h>
#define MAX_SIZE 1211
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

ll Dinic() {
    ll flow=0;
    while(bfs()){
        memset(cur,0,sizeof(cur));
        flow += dfs(s,INF);
    }
    return flow;
}
// dp array stores the all pair shortest path 
ll dp[MAX_SIZE >> 1][MAX_SIZE >> 1];
int city[MAX_SIZE];
int V, E, N, K;

bool judge(int mid) {
	 init();
	 int i, j;
	 s = 0, t = 2 * V + 1;
	 for (i = 1; i <= V; i++) {
	 	 if (city[i]) {
		 	addedge(s, i, city[i]); 
         }
	 }
	 
	 for (i = 1; i <= V; i++) {
	 	 for (j = 1; j <= V; j++) {
		 	 if (dp[i][j] <= mid) {
			 	addedge(i, j + V, INF); 
		     } 
         }
	 }
	 
	 
	 for (i = 1; i <= V; i++) {
	 	 addedge(i + V, t, 1);
	 }
	 
	 return Dinic() >= K;
}

int main() {
	int i, j, k;
	scanf("%d%d%d%d", &V, &E, &N, &K);
	for (i = 0 ; i < N; i++) {
		int v;
		scanf("%d", &v);
		city[v]++;
	}		
	
	for (i = 0 ; i <= V; i++) {
		for (j = 0; j <= V; j++) {
			if (i != j) {
			   dp[i][j] = INF;
			}
		}
	}
	
	for (i = 0 ; i < E; i++) {
		int a, b;
		ll w;
		scanf("%d%d%lld", &a, &b, &w);
		dp[a][b] = min(dp[a][b], w);
	    dp[b][a] = min(dp[b][a], w);
	}
	
	for (k = 1; k <= V; k++) {
		for (i = 1; i <= V; i++) {
			for (j = 1; j <= V; j++) {
				dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
			}
		}
	}
	
	ll low = 0, high = 1731311;
	ll ans = 1731312;
	
	while (low <= high) {
		  ll mid = low + (high - low) / 2;
		  if (judge(mid)) {
		  	 ans = mid;
             high = mid - 1;
		  } else {
		  	 low = mid + 1;
		  }
	}
	
	if (ans == 1731312) {
	   cout << "-1" << endl;
	} else {
	  cout << ans << endl;
	}
	return 0;
}

