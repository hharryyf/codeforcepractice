#include <bits/stdc++.h>
#define MAX_SIZE 1011
#define INF 10000000000ll
typedef long long ll;
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
		// cout << "addedge " << from << " " << to << " " << capacity << endl;
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
int a[MAX_SIZE], dp[MAX_SIZE];

void init() {
    mf.init();
    mf.s = 0, mf.t = MAX_SIZE - 1;
}

int in(int v) {
    return v * 2 - 1;
}

int out(int v) {
    return v * 2;
}

int main() {
    int i, j, n, ans = 1;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }

    dp[1] = 1;

    for (i = 2; i <= n; ++i) {
        dp[i] = 1;
        for (j = 1; j < i; ++j) {
            if (a[i] >= a[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }

        ans = max(ans, dp[i]);
    }

    printf("%d\n", ans);
    init();
    
    for (i = 1; i <= n; ++i) {
        mf.addedge(in(i), out(i), 1);
        for (j = i + 1; j <= n; ++j) {
            if (a[i] <= a[j] && dp[i] + 1 == dp[j]) {
                mf.addedge(out(i), in(j), 1);
            }
        }
    }

    for (i = 1; i <= n; ++i) {
        if (dp[i] == 1) {
            mf.addedge(mf.s, in(i), ans);
        }

        if (dp[i] == ans) {
            mf.addedge(out(i), mf.t, ans);
        }
    }

    cout << mf.Dinic() << endl;

    init();

    for (i = 1; i <= n; ++i) {
        if (i != 1 && i != n) {
            mf.addedge(in(i), out(i), 1);
        } else {
            mf.addedge(in(i), out(i), ans);
        }

        for (j = i + 1; j <= n; ++j) {
            if (a[i] <= a[j] && dp[i] + 1 == dp[j]) {
                mf.addedge(out(i), in(j), 1);
            }
        }
    }

    for (i = 1; i <= n; ++i) {
        if (dp[i] == 1) {
            mf.addedge(mf.s, in(i), ans);
        }

        if (dp[i] == ans) {
            mf.addedge(out(i), mf.t, ans);
        }
    }

    cout << mf.Dinic() << endl;
    return 0;
}