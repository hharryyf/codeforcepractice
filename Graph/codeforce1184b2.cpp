#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 2521
typedef long long ll;
#define INF 10000000000000
using namespace std;

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
int n, m;
ll dist[111][111];
tuple<int, int, int> sp[MAX_SIZE];
pair<int, int> bs[MAX_SIZE];
int s, b;
ll kcost, hcost;

int main() {
	mf.s = 0, mf.t = MAX_SIZE - 2;
	scanf("%d%d", &n, &m);
	int i, j, k;
	for (i = 0 ; i <= n; i++) {
		for (j = 0 ; j <= n; j++) {
			if (i != j) dist[i][j] = INF;
		}
	}	
	
	for (i = 0; i < m; i++) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		dist[v1][v2] = dist[v2][v1] = min(dist[v1][v2], 1ll);
	}
	
	for (k = 1; k <= n; k++) {
		for (i = 1; i <= n; i++) {
			for (j = 1; j <= n; j++) {
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);	
			}
		}
	}
	
	scanf("%d%d%lld%lld", &s, &b, &kcost, &hcost);
	
	for (i = 1; i <= s; i++) {
		int v1, v2, v3;
		scanf("%d%d%d", &v1, &v2, &v3);
		sp[i] = make_tuple(v1, v2, v3);
		mf.addedge(mf.s, i, 1);
	}
	
	for (i = 1; i <= b; i++) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		bs[i] = make_pair(v1, v2);
		mf.addedge(i + s, mf.t, 1);
	}
	
	for (i = 1; i <= s; i++) {
		for (j = 1; j <= b; j++) {
			int v1 = get<0>(sp[i]), v2 = bs[j].first;
			if (dist[v1][v2] <= get<2>(sp[i]) && get<1>(sp[i]) >= bs[j].second) {
			   mf.addedge(i, j + s, 1);
			}
		}
	}
	
	ll flow = mf.Dinic();
	ll money = min(flow * kcost, hcost * s);
	printf("%lld\n", money);
	return 0;	
}
