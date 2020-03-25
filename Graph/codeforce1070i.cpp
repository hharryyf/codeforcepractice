#include <bits/stdc++.h>
#define MAX_SIZE 1222
typedef long long ll;
#define INF 100000000000
using namespace std;


/*
	The key observation for this problem is for a given company
	only if it occupys 2 edges that shares a common vertex, it can
	have some benifits towards the final answer.
	Then, for each vertices, we should calculate how many times at least
	a company uses it as the middle point.
	Finally, the problem can be reduced to the following, select a direction
	for each edge, each vertices should have at least some out degree. Which
	can be solved by max flow.
	
	
*/
struct Maxflow {
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
};

Maxflow mf;
int ans[MAX_SIZE];
vector<int> mg[MAX_SIZE];
vector<int> g[MAX_SIZE];

int main() {
	int T, i, n, m, k, j;
	scanf("%d", &T);
	while (T > 0) {
		mf.init();
		ll target = 0;
		mf.s = 0, mf.t = MAX_SIZE - 1;
		scanf("%d%d%d", &n, &m, &k);
		// 1-m edges, m+1-m+n vertices
		for (i = 1; i < MAX_SIZE; ++i) {
			mg[i].clear();
			g[i].clear();
		}
		memset(ans, 0, sizeof(ans));
		for (i = 1; i <= m; ++i) {
			int v1, v2;
			scanf("%d%d", &v1, &v2);
			g[v1].push_back(v2);
			g[v2].push_back(v1);
			mf.addedge(mf.s, i, 1);
			mf.addedge(i, v1 + m, 1);
			mf.addedge(i, v2 + m, 1);
		}
		
		for (i = 1; i <= n; ++i) {
			int deg = g[i].size();
			mf.addedge(m + i, mf.t, max(0, 2 * deg - 2 * k));
			target += max(0, 2 * deg - 2 * k);
		}
		
		ll ret = mf.Dinic();
		
		if (ret != target) {
			for (i = 1; i <= m; ++i) {
				printf("0 ");
			}
			printf("\n");
		} else {
			for (auto e : mf.edg) {
				if (e.from <= m && e.to >= m + 1 && e.to <= m + n && e.flow == e.capacity) {
					mg[e.to-m].push_back(e.from);
				}
			}
			
			int id = 1;
			for (i = 1; i <= n; ++i) {
				for (j = 0; j < (int) mg[i].size(); j += 2) {
					ans[mg[i][j]] = id;
					ans[mg[i][j+1]] = id;
					id++;
				}
			}
			
			for (i = 1; i <= m; ++i) {
				if (!ans[i]) ans[i] = id++;
			}
			
			for (i = 1; i <= m; ++i) {
				printf("%d ", ans[i]);
			}
			printf("\n");
		}
		
		T--;
	}
	return 0;
}