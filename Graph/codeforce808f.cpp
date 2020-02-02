#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 211
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
unordered_set<int> h;
bool visited[200111];

struct card {
    int p, c, l;
    bool operator < (card other) const {
        return p > other.p;
    }
};

card a[MAX_SIZE];
int n;
// tol is the sum of a[i].p
ll k, tol;

void preprocess() {
    int i, j;
    for (i = 2; i <= 200000; i++) {
        if (!visited[i]) {
            h.insert(i);
            for (j = 1; j * i <= 200000; j++) {
                visited[j * i] = true;
            }
        }
    }
}

void build(int st) {
    int i, j;
    bool hasone = false;
    mf.init();
    tol = 0;
    for (i = 1; i <= n; i++) {
        if (a[i].l <= st) {
            if (a[i].c == 1 && hasone) continue;
            if (a[i].c == 1) hasone = true;
            tol += a[i].p;
            if (a[i].c % 2 == 0) {
                mf.addedge(i, mf.t, a[i].p);
            } else {
                mf.addedge(mf.s, i, a[i].p);
            }
            
            for (j = 1; j <= n; j++) {
                if (a[j].l <= st && h.find(a[i].c + a[j].c) != h.end()) {
                    if (a[i].c % 2 == 1) {
                        mf.addedge(i, j, INF);
                    } else {
                        mf.addedge(j, i, INF);
                    }
                }
            }
        }
    }
}

int main () {
    preprocess();
    scanf("%d%lld", &n, &k);
    int i;
    for (i = 1; i <= n; i++) {
        scanf("%d%d%d", &a[i].p, &a[i].c, &a[i].l);
        tol += 1ll * a[i].p;
    }
    
    sort(a + 1, a + n + 1);
    mf.s = 0, mf.t = 2 * n + 1;
    int low = 1, high = n;
    int ans = n + 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        build(mid);
        ll flow = mf.Dinic();
        if (flow <= tol - k) {
            ans = mid, high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    
    if (ans <= n) {
        printf("%d\n", ans);
    } else {
        printf("-1\n");
    }
    return 0;
}
