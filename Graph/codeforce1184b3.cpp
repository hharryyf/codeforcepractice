#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 3011
typedef long long ll;
#define INF 1000000000000000
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
ll dist[111][111];
int n, m;

struct spa {
    int id, x, a, f, p;  
    bool operator < (spa other) const {
        return a < other.a;
    }
};

struct base {
    int d, g;
    bool operator < (base other) const {
        return d < other.d;
    }
};

// G[i] stores all the base at node i
vector<base> G[111];
spa sp[100011];
ll profit[100011];
pair<int, int> relation[MAX_SIZE];
int special[100011];
vector<int> disc;

int main() {
    int i, j, k, S, B;
    mf.s = MAX_SIZE - 2, mf.t = MAX_SIZE - 1;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= n; ++j) {
            if (i != j) {
                dist[i][j] = INF;
            }
        }
    }

    for (i = 0 ; i < 100011; ++i) profit[i] = -INF;

    for (i = 1; i <= m; ++i) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        dist[v1][v2] = dist[v2][v1] = min(dist[v1][v2], 1ll);
    }

    for (k = 1; k <= n; ++k) {
        for (i = 1; i <= n; ++i) {
            for (j = 1; j <= n; ++j) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    scanf("%d%d%d", &S, &B, &m);
    for (i = 1; i <= S; ++i) {
        scanf("%d%d%d%d", &sp[i].x, &sp[i].a, &sp[i].f, &sp[i].p);
        sp[i].id = i;
    }

    for (i = 1; i <= B; ++i) {
        int v, d, g;
        scanf("%d%d%d", &v, &d, &g);
        G[v].push_back(base{d, g});
    }

    sort(sp + 1, sp + 1 + S);
    for (i = 1; i <= n; ++i) {
        sort(G[i].begin(), G[i].end());
        ll gold = -INF;
        int sz = G[i].size();
        for (k = 1, j = 0; k <= S; ++k) {
            while (j < sz && sp[k].a >= G[i][j].d) {
                gold = max(gold, (ll) G[i][j].g);
                ++j;
            }
            
            if (sp[k].f >= dist[i][sp[k].x]) { 
                profit[sp[k].id] = max(profit[sp[k].id],  gold - sp[k].p);
            }
        }
    }

    ll ans = 0, tol = 0;
    for (i = 1; i <= m; ++i) {
        scanf("%d%d", &relation[i].first, &relation[i].second);
        special[relation[i].first] = special[relation[i].second] = 1;
    }
    
    for (i = 1; i <= S; ++i) {
        if (!special[i] && profit[i] > 0) {
            ans += profit[i];
        } 
        
        if (special[i]) {
            disc.push_back(i);
        }
    }

    for (i = 0 ; i < (int) disc.size(); ++i) {
        if (profit[disc[i]] < 0) {
            mf.addedge(i, mf.t, -profit[disc[i]]);
        } else {
            mf.addedge(mf.s, i, profit[disc[i]]);
            tol += profit[disc[i]];
        }
    }
/*
    for (i = 1; i <= S; ++i) {
        cout << profit[i] << " ";
    }

    cout << endl;
*/
    for (i = 1; i <= m; ++i) {
        if (binary_search(disc.begin(), disc.end(), relation[i].first) 
         && binary_search(disc.begin(), disc.end(), relation[i].second)) {
            int id1 = lower_bound(disc.begin(), disc.end(), relation[i].first) - disc.begin();
            int id2 = lower_bound(disc.begin(), disc.end(), relation[i].second) - disc.begin();
            mf.addedge(id1, id2, INF);
        }
    }

    ans = ans + tol - mf.Dinic();
    
    cout << ans << endl;
    return 0;
}