#include <bits/stdc++.h>
#define MAX_SIZE 81111
typedef int ll;
#define INF 1000000
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
char st[211][211];

int idx(int x, int y, int tp) {
    return  2 * ((x - 1) * m + y) + tp;
}

int main() {
    int i, j, ans = 0;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i) scanf("%s", st[i] + 1);
    mf.s = 0, mf.t = MAX_SIZE - 1;
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= m; ++j) {
            if (st[i][j] == '#') {
                ans++;
                if (st[i][j+1] == '#') {
                    ans--;
                    mf.addedge(mf.s, idx(i, j, 0), 1);
                }

                if (st[i+1][j] == '#') {
                    ans--;
                    mf.addedge(idx(i, j, 1), mf.t, 1);
                }
            }
        }
    }

    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= m; ++j) {
            if (st[i][j] == '#') {
                if (st[i][j+1] == '#' && st[i-1][j+1] == '#') {
                    mf.addedge(idx(i, j, 0), idx(i-1, j+1, 1), INF);
                }

                if (st[i][j+1] == '#' && st[i+1][j+1] == '#') {
                    mf.addedge(idx(i, j, 0), idx(i, j+1, 1), INF);
                }

                if (st[i][j-1] == '#' && st[i-1][j-1] == '#') {
                    mf.addedge(idx(i, j-1, 0), idx(i-1, j-1, 1), INF);
                }

                if (st[i][j-1] == '#' && st[i+1][j-1] == '#') {
                    mf.addedge(idx(i, j-1, 0), idx(i, j-1, 1), INF);
                }
            }
        }
    }

    ans = ans + (int) mf.Dinic();
    printf("%d\n", ans);
    return 0;
}