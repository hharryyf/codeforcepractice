#include <bits/stdc++.h>
#define MAX_SIZE 1422
#define MAXV 100011
typedef long long ll;
const ll INF = 10000000000000;
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
int N, M1, M2;
vector<int> g[MAXV];
struct pat {
    int from, to, cost;
};
pat p1[MAX_SIZE], p2[MAX_SIZE];
int parent[MAXV][18];
int height[MAXV];

void dfs(int v, int pre) {
    height[v] = height[pre] + 1;
    parent[v][0] = pre;
    int i;
    for (i = 1; i < 18; ++i) parent[v][i] = parent[parent[v][i-1]][i-1];
    for (auto nv : g[v]) {
        if (nv != pre) {
            dfs(nv, v);
        }
    }
}

int LCA(int u, int v) {
    if (height[u] < height[v]) swap(u, v);
    int i;
    for (i = 17; i >= 0; --i) {
        if (height[u] >= (1 << i) + height[v]) {
            u = parent[u][i];
        }
    }

    if (u == v) return u;
    for (i = 17; i >= 0; --i) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i], v = parent[v][i];
        }
    }

    return parent[u][0];
}

int dist(int u, int v) {
    return height[u] + height[v] - 2 * height[LCA(u, v)];
}

int main() {
    int i, j;
    ll ans = 0;
    scanf("%d%d%d", &N, &M1, &M2);
    mf.s = 0, mf.t = M1 + M2 + 2;
    for (i = 0 ; i < N - 1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0);
    for (i = 1; i <= M1; ++i) scanf("%d%d%d", &p1[i].from, &p1[i].to, &p1[i].cost);
    for (i = 1; i <= M2; ++i) scanf("%d%d%d", &p2[i].from, &p2[i].to, &p2[i].cost);
    for (i = 1; i <= M1; ++i) {
        mf.addedge(mf.s, i, p1[i].cost);
        ans += p1[i].cost;
    }

    for (i = 1; i <= M2; ++i) {
        mf.addedge(M1 + i, mf.t, p2[i].cost);
        ans += p2[i].cost;
    }

    for (i = 1; i <= M1; ++i) {
        int v1 = LCA(p1[i].from, p1[i].to);
        for (j = 1; j <= M2; ++j) {
            int v2 = LCA(p2[j].from, p2[j].to);
            int u = LCA(v1, v2);
            if (u == v1) {
                if (dist(v2, p1[i].from) + dist(v1, v2) == height[p1[i].from] - height[v1]) {
                    mf.addedge(i, M1 + j, INF);
                    continue;
                } else if (dist(v2, p1[i].to) + dist(v1, v2) == height[p1[i].to] - height[v1]) {
                    mf.addedge(i, M1 + j, INF);
                    continue;
                }
            }
            
            if (u == v2) {
                if (dist(v1, p2[j].from) + dist(v2, v1) == height[p2[j].from] - height[v2]) {
                    mf.addedge(i, M1 + j, INF);
                    continue;
                } else if (dist(v1, p2[j].to) + dist(v2, v1) == height[p2[j].to] - height[v2]) {
                    mf.addedge(i, M1 + j, INF);
                    continue;
                }
            }   
        }
    }

    ans -= mf.Dinic();
    cout << ans << endl;
    return 0;
}