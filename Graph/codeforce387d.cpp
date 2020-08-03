#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 1101
typedef long long ll;
#define INF 100000000000
using namespace std;

int in(int x) {
    return x << 1;
}

int out(int x) {
    return x << 1 | 1;
}

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
vector<int> g[MAX_SIZE];
int conn[MAX_SIZE][MAX_SIZE];
int N, M;

int solve(int vc) {
    int i, ret = 0, cnt = 0;
    mf.init();
    mf.s = 0, mf.t = MAX_SIZE - 1;
    for (i = 1; i <= N; ++i) {
        ret += (conn[vc][i] ^ 1);
        ret += (conn[i][vc] ^ 1);
    }

    ret -= (conn[vc][vc] ^ 1);

    for (i = 1; i <= N; ++i) {
        if (i == vc) continue;
        for (auto e : g[i]) {
            if (e != vc) {
                mf.addedge(in(i), out(e), 1);
                ++cnt;
            }
        }
        mf.addedge(mf.s, in(i), 1);
        mf.addedge(out(i), mf.t, 1);
    }

    int match = mf.Dinic();

    ret += (N - 1 + cnt) - 2 * match;
    return ret;
}

int main() {
    int i, u, v;
    int ans = 1e9;
    scanf("%d%d", &N, &M);
    for (i = 1; i <= M; ++i) {
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        conn[u][v] = 1;
    }

    for (i = 1; i <= N;  ++i) {
        // let i be the center
        ans = min(ans, solve(i));
    }

    printf("%d\n", ans);
    return 0;
}