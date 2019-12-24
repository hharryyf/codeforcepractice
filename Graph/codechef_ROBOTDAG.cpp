#include <bits/stdc++.h>
#define MAX_SIZE 10011 
#define INF 100000000000ll
typedef long long ll;
using namespace std;


struct MaxFlow { 
	struct edge {
		int from, to;
		ll flow, capacity;
	};
	
	// start and end point
	int s, t;
	ll ans = 0;
	// list array
	vector<edge> edg;
	
	// g reference to the ith vertex's edges
	vector<int> g[MAX_SIZE];
	
	// distance array and visited array
	int dist[MAX_SIZE], visited[MAX_SIZE];
	int cur[MAX_SIZE];
	
	void init() {
		ans = 0;
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
	    ans += flow;
	    return ans;
	}
};

MaxFlow mf;

vector<int> h[111];

int main() {
	int n, m, i, j, k;
	int T;
	scanf("%d", &T);
	while (T > 0) {
		  scanf("%d%d%d", &n, &m, &k);
		  mf.init();
		  for (i = 0; i < 111; i++) h[i].clear(); 
		  mf.s = 0;
	      mf.t = n + 1;
		  mf.addedge(0, 1, INF);
		  for (i = 1; i <= m; i++) {
		  	  int v1, v2;
		  	  scanf("%d%d", &v1, &v2);
		  	  h[v1].push_back(v2);
		  }
		  
		  for (i = 1; i < n; i++) {
		  	  mf.t += n;
		  	  mf.addedge(mf.t - 1, mf.t, INF);
		  	  // cout << "addedge " << mf.t - 1 << " " << mf.t << endl;
		  	  for (j = 1; j <= n; j++) {
			  	  for (auto nv : h[j]) {
				  	  mf.addedge((i - 1) * n + j, i * n + nv, 1);	
				  	  // cout << "addedge " << (i - 1) * n + j << " " << i * n + nv << endl;
				  }	
              }
              // cout << "s= " << mf.s << " t =  " << mf.t << endl;
              ll fl = mf.Dinic();
              // cout << "flow= " << fl << endl;
              if (fl >= k) {
			  	 printf("%d\n", i);
			  	 break;
			  }
		  }
		  
		  if (i == n) {
		  	 printf("-1\n");
		  }
		  
		  T--;
	}
	return 0;
}

