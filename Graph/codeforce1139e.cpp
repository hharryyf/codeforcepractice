#include <bits/stdc++.h>
#define MAX_SIZE 10111
typedef long long ll;
#define INF 10000000000ll
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

const int maxp = 5000;
int p[MAX_SIZE];
bool visited[MAX_SIZE];
bool haspeople[MAX_SIZE];
int leave[MAX_SIZE];
int ans[MAX_SIZE];
int c[MAX_SIZE];
bool add[MAX_SIZE];

int main() {
	// students, clubs
	int n, m, i;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n; ++i) {
		visited[i] = 1;
		scanf("%d", &p[i]);
		haspeople[p[i]] = true;
	}
	
	for (i = 1; i <= n; ++i) {
		scanf("%d", &c[i]);
	}
	
	mf.s = MAX_SIZE - 2, mf.t = MAX_SIZE - 1;
	// addedge from club to sink with capacity 1
	for (i = 1 + maxp; i <= m + maxp; ++i) {
		mf.addedge(i, mf.t, 1);
	}
	
	int q;
	scanf("%d", &q);
	for (i = 1; i <= q; ++i) {
		scanf("%d", &leave[i]);
		visited[leave[i]] = 0;
	}
	
	for (i = 1; i <= n; ++i) {
		if (visited[i] == 1) {
			mf.addedge(p[i], c[i] + maxp, 1);
		}
	}
	
	int ret = 0;
	ll flow = 0;
	for (i = q; i >= 1; --i) {
		while (ret <= maxp) {
			if (!add[ret] && haspeople[ret]) {
				mf.addedge(mf.s, ret, 1);
				add[ret] = 1;
			}
			// cout << mf.Dinic() << " " << i << endl;
			flow += mf.Dinic();
			if (flow >= ret + 1) {
				ret++;
			} else {
				break;
			}
		}
		
		ans[i] = ret;
		mf.addedge(p[leave[i]], c[leave[i]] + maxp, 1);
	}
	
	for (i = 1; i <= q; ++i) {
		printf("%d\n", ans[i]);
	}
	return 0;
}