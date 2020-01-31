#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 10011
typedef long long ll;
#define INF 1000000000
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
pair<int, int> g[MAX_SIZE];

void build(int mid) {
    mf.init();
    mf.s = 0, mf.t = n + m + 1;
    int i;
    for (i = 1; i <= n; i++) {
        mf.addedge(mf.s, i, mid);
    }
    
    for (i = 1; i <= m; i++) {
        mf.addedge(g[i].first, i + n, 1);
        mf.addedge(g[i].second, i + n, 1);
        mf.addedge(i + n, mf.t, 1);
    }
}

bool valid(int mid) {
    build(mid);
    return mf.Dinic() == m;
}

int main() {
    scanf("%d%d", &n, &m);
    int low = 0, high = 5001;
    int ans = 5001, i;
    for (i = 1 ; i <= m; i++) {
        scanf("%d%d", &g[i].first, &g[i].second);
    }
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (valid(mid)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    
    build(ans);
    mf.Dinic();
    printf("%d\n", ans);
    for (auto e : mf.edg) {
        if (e.flow == 1 && e.capacity == 1 && e.from >= 1 && e.from <= n) {
            int v = g[e.to - n].first != e.from ? g[e.to - n].first : g[e.to - n].second;
            printf("%d %d\n", e.from, v);
        }
    }
    return 0;
}
