#include <bits/stdc++.h>
#define MAX_SIZE 4111
typedef long long ll;
#define INF 10000000000ll
using namespace std;

struct Maxflow {
    struct edge {
    	int from, to;
    	ll flow, capacity;
        int id;
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
    
    void addedge(int from, int to, ll capacity, int id) {
    	edge e1 = edge{from, to, 0ll, capacity, id};
		// cout << "addedge " << from << " " << to << " " << capacity << endl;
    	edge e2 = edge{to, from, 0ll, 0ll, -1};
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
int n1, n2, m;
int deg[MAX_SIZE];
vector<int> ans[MAX_SIZE];

int main() {
    int i, j;
    scanf("%d%d%d", &n1, &n2, &m);
    mf.s = 0, mf.t = MAX_SIZE - 1;
    for (i = 0 ; i < m; ++i) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        mf.addedge(v1, v2 + n1, 1, i + 1);
        ++deg[v1], ++deg[v2 + n1];
    }

    int k = deg[1];
    for (i = 2; i <= n1 + n2; ++i) {
        k = min(deg[i], k);
    }
    // cout << "deg= " << k << endl;
    // we solve the queries in reverse order of k
    // instead of thinking the minimum number of edges that must be added
    // we think the maximum edges that can be eliminated, which let all edges
    // to have a degree loss no more than deg[i] - k
    for (i = 1; i <= n1; ++i) {
        mf.addedge(mf.s, i, deg[i] - k, -1);
    }

    for (i = 1; i <= n2; ++i) {
        mf.addedge(n1 + i, mf.t, deg[i+n1] - k, -1);
    }

    int flow = 0;
    for (i = k; i >= 0; --i) {
        flow += mf.Dinic();
        for (auto &e : mf.edg) {
            if (e.from <= n1 && e.from >= 1 && e.to <= n1 + n2 && e.to >= n1 + 1) {
                // cout << e.flow << " ... " << e.capacity << endl;
                if (e.flow == 0 && e.capacity == 1) {
                    ans[i].push_back(e.id);
                }
            }
        }

        for (j = 1; j <= n1; ++j) {
            mf.addedge(mf.s, j, 1, -1);
        }

        for (j = 1; j <= n2; ++j) {
            mf.addedge(n1 + j, mf.t, 1, -1);
        }    
    }

    for (i = 0; i <= k; ++i) {
        printf("%d", (int) ans[i].size());
        for (auto v : ans[i]) {
            printf(" %d", v);
        }
        printf("\n");
    }
    return 0;
}