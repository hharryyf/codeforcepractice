#include <bits/stdc++.h>
#define MOD 1000000007
#define INF 1000000000000ll
#define MAX_SIZE 1211
typedef long long ll;
using namespace std;

struct MaxFlow {
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
	
	bool fullcap() {
		 for (auto e : edg) {
		 	 if (e.from == s && e.flow != e.capacity) return false;
		 }
		 return true;
	}
};

MaxFlow mf;

// teams
int n;
// how many games each team wins
int win[27];
// the remaining game grid
int game[27][27];
// initalize
void init() {
	 int i, j;
	 for (i = 0 ; i < 27; i++) {
	 	  win[i] = 0;
		  for (j = 0 ; j < 27; j++) {
		  	  game[i][j] = 0;
          }
          
	 }
}

// check whether v can be the a winner
bool judge(int v) {
	 mf.init();
	 mf.s = 0, mf.t = MAX_SIZE - 4;
	 int target = win[v];
	 int i, j;
	 for (i = 1; i <= n; i++) {
	 	 target += game[v][i];
	 }
	 
	 for (i = 1; i <= n; i++) {
	 	 for (j = i + 1; j <= n; j++) {
		 	 if (i == v || j == v || game[i][j] == 0) continue;
			 mf.addedge(mf.s, i * n + j, game[i][j]);
			 mf.addedge(i * n + j, 800 + i, INF);
			 mf.addedge(i * n + j, 800 + j, INF);		  
         }
	 }
	 
	 for (i = 1; i <= n; i++) {
	 	  if (target - win[i] < 0) return false;
		  mf.addedge(800 + i, mf.t, target - win[i]);
	 }
	 
	 mf.Dinic();
	 
	 return mf.fullcap();
}

int main() {
	int T, i, j;
	scanf("%d", &T);
	while (T > 0) {
		  init();
		  scanf("%d", &n);
		  for (i = 1; i <= n; i++) {
		  	  int d;
		  	  scanf("%d%d", &win[i], &d);
		  }
		  
		  for (i = 1; i <= n; i++) {
		  	  for (j = 1; j <= n; j++) {
			  	  scanf("%d", &game[i][j]);	
              }
		  } 
		  int cnt = 1;
		  for (i = 1 ; i <= n; i++) {
		  	  if (judge(i)) {
                   if (cnt == 1) {
				   	  printf("%d", i);
				   } else {
				   	  printf(" %d", i);
				   }	
				   cnt++;
	          }
		  }
		  printf("\n");
		  T--;
	}
	return 0;
}

