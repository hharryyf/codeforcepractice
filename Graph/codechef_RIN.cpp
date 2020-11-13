#include <bits/stdc++.h>
#define MAX_SIZE 10151
typedef long long ll;
#define INF 100000000000
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

int idx(int term, int cid) {
    return n * (term - 1) + cid;  
}

int main() {
    int i, j, k;
    scanf("%d%d%d", &n, &m, &k);
    // be careful n -> number of courses, m -> number of terms, k -> k prereq
    mf.s = 0, mf.t = MAX_SIZE - 1;
    for (i = 1; i <= n; ++i) {
        mf.addedge(mf.s, idx(1, i), INF);
    }

    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= m; ++j) {
            int v;
            scanf("%d", &v);
            if (v == -1) {
                mf.addedge(idx(j, i), idx(j + 1, i), INF);
            } else {
                mf.addedge(idx(j, i), idx(j + 1, i), 100 - v);
            }
        }
    }

    for (i = 1; i <= n; ++i) {
        mf.addedge(idx(m + 1, i), mf.t, INF);
    }

    for (i = 1; i <= k; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        for (j = 1; j <= m; ++j) {
            mf.addedge(idx(j, u), idx(j + 1, v), INF);
            // cout << "addedge " << idx(j, u) << " " << idx(j, v) << endl;
        }
    }

    ll ret = mf.Dinic();
    ll ans = 1ll * 100 * n - ret;
    printf("%.2lf\n", 1.0 * ans / n);
    return 0;
}