#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 20011
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
// n dogs, m plans, penalty of friend
int n, m, G;
// index of dog i in the flow graph
// is from 1 to n, dog[i] is the sex of the ith dog
int dog[MAX_SIZE];
int cost[MAX_SIZE];
// plan[i] is the wanted sex of the ith plane
int plan[MAX_SIZE];
int award[MAX_SIZE];
// g[i] stores the dogs associated with the ith plan
vector<int> g[MAX_SIZE];
// good[i] 0/1 represents whether the ith plan is a friend plan
int good[MAX_SIZE];
// the plan that the ith dog involves in
vector<int> cover[MAX_SIZE];

int main() {
    int i, j, k;
    scanf("%d%d%d", &n, &m, &G);
    for (i = 1; i <= n; ++i) scanf("%d", &dog[i]);
    for (i = 1; i <= n; ++i) scanf("%d", &cost[i]);
    for (i = 1; i <= m; ++i) {
        int ki;
        scanf("%d%d", &plan[i], &award[i]);
        scanf("%d", &ki);
        while (ki-- > 0) {
            int v;
            scanf("%d", &v);
            g[i].push_back(v);
            cover[v].push_back(i);
        }
        scanf("%d", &good[i]);
    }
    // here's the rule of the index
    // 1 to n, the dogs
    // n+1 to n+m, the plans
    // cutting an edge means we select this penalty
    mf.s = 0, mf.t = MAX_SIZE - 1;
    for (i = 1; i <= n; ++i) {
        // if the dog has state 1, by cutting this edge
        // we change its state to 0
        if (dog[i] == 1) {
            mf.addedge(i, mf.t, cost[i]);
        } else {
            mf.addedge(mf.s, i, cost[i]);
        }
    }

    ll tol = 0;
    for (i = 1; i <= m; ++i) {
        for (auto v : g[i]) {
            // the plan of i and its dogs are different in color
            // whether we 
            if (plan[i] != dog[v]) {
                // either accept the penalty of the plan or accept 
                // the penalty of changing color of all dogs
                if (plan[i] == 1) {
                    mf.addedge(v, i + n, INF);
                } else {
                    mf.addedge(i + n, v, INF);
                }
            }
        }

        tol += award[i];
        if (good[i]) {
            award[i] += G;
        }
        // cutting this edge means we do not select this plan
        // and accept the penalty!
        if (plan[i] == 1) {
            mf.addedge(i + n, mf.t, award[i]);
        } else {
            mf.addedge(mf.s, i+n, award[i]);
        }
    }
    // something that might be missed, 2 plan with different type
    // that involves a common dog cannot exist at the same time
    for (i = 1; i <= n; ++i) {
        for (j = 0 ; j < (int) cover[i].size(); ++j) {
            for (k = 1; k < (int) cover[i].size(); ++k) {
                if (plan[cover[i][j]] != plan[cover[i][k]]) {
                    if (plan[cover[i][j]] == 1) {
                        mf.addedge(cover[i][k] + n, cover[i][j] + n, INF);
                    } else {
                        mf.addedge(cover[i][j] + n, cover[i][k] + n, INF);
                    }
                }
            }
        }
    }

    cout << tol - mf.Dinic() << endl;
    return 0;
}