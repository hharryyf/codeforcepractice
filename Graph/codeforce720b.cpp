#include <bits/stdc++.h>
#define MAX_SIZE 81111
using namespace std;
typedef long long ll;
#define INF 1000000000

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

// construct the graph and we find all biconnected components
vector<pair<int, int>> g[MAX_SIZE];
int low[MAX_SIZE], visited[MAX_SIZE];
int cid[MAX_SIZE], instack[MAX_SIZE];
stack<int> st;
int cnt = 1;
int id = 1;
int n, m;

struct edge {
	int from, to, color;
};

edge edg[MAX_SIZE];
vector<int> bcp[MAX_SIZE];

void dfs(int v, int pre) {
	low[v] = visited[v] = cnt;
	++cnt;
	for (auto np : g[v]) {
		int nv = np.first;
		if (nv != pre) {
			if (!visited[nv]) {
				st.push(np.second);
				dfs(nv, v);
				low[v] = min(low[v], low[nv]);
				if (low[nv] >= visited[v]) {
					while (st.top() != np.second) bcp[id].push_back(st.top()), st.pop();
					bcp[id++].push_back(st.top()), st.pop();
				}
			} else if (visited[nv] < visited[v]) {
				st.push(np.second);
				low[v] = min(low[v], visited[nv]);
			}
		}
	}
}

int add[MAX_SIZE];

void construct() {
	int i;
	mf.s = 0, mf.t = MAX_SIZE - 1;
	dfs(1, 0);
	
	for (i = 1; i < id; ++i) {
		int sz = bcp[i].size();
		if (sz == 1) {
			mf.addedge(mf.s, i, 1);
		} else if (sz > 1) {
			mf.addedge(mf.s, i, sz - 1);
		}
		
		for (auto v : bcp[i]) {
			int cl = edg[v].color + id + 2;
			mf.addedge(i, cl, 1);
			if (!add[cl]) {
				mf.addedge(cl, mf.t, 1);
				add[cl] = 1;
			}
		}
	}
	
}

int main() {
	scanf("%d%d", &n, &m);
	int i;
	for (i = 1; i <= m; ++i) {
		scanf("%d%d%d", &edg[i].from, &edg[i].to, &edg[i].color);
		g[edg[i].from].emplace_back(edg[i].to, i);
		g[edg[i].to].emplace_back(edg[i].from, i);
	}
	
	construct();
	
	printf("%I64d\n", mf.Dinic());
	return 0;
}