#include <bits/stdc++.h>
#define MAX_SIZE 11111
typedef int ll;
#define INF 10000000
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

int N;
int x[MAX_SIZE], y[MAX_SIZE];
int op[MAX_SIZE];
long long tmp[MAX_SIZE];
Maxflow mf;
vector<long long> disc;

int main() {
    int i;
    mf.s = MAX_SIZE - 2, mf.t = MAX_SIZE - 1;
    scanf("%d", &N);
    for (i = 0 ; i < N; ++i) {
        scanf("%d%d", &x[i], &y[i]);
        tmp[i * 3] = x[i] + y[i];
        tmp[i * 3 + 1] = x[i] - y[i];
        tmp[i * 3 + 2] = 1ll * x[i] * y[i];
    }

    sort(tmp, tmp + 3 * N);
    for (i = 0 ; i < 3 * N; ++i) {
        if (i == 0 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
    }

    for (i = 0 ; i < N; ++i) {
        mf.addedge(mf.s, i, 1);
    }

    int sz = disc.size();
    for (i = 0 ; i < sz; ++i) {
        mf.addedge(N + i, mf.t, 1);
    }

    for (i = 0 ; i < N; ++i) {
        int idx = lower_bound(disc.begin(), disc.end(), x[i] + y[i]) - disc.begin();
        mf.addedge(i, N + idx, 1);
        idx = lower_bound(disc.begin(), disc.end(), x[i] - y[i]) - disc.begin();
        mf.addedge(i, N + idx, 1);
        idx = lower_bound(disc.begin(), disc.end(), 1ll * x[i] * y[i]) - disc.begin();
        mf.addedge(i, N + idx, 1);
    }

    auto ret = mf.Dinic();
    if (ret != N) {
        printf("impossible\n");
        return 0;
    }

    for (auto &e : mf.edg) {
        if (e.from < N && e.to >= N && e.to < N + sz && e.flow == e.capacity && e.flow == 1) {
            if (disc[e.to - N] == x[e.from] + y[e.from]) {
                op[e.from] = 0;
            } else if (disc[e.to - N] == x[e.from] - y[e.from]) {
                op[e.from] = 1;
            } else {
                op[e.from] = 2;
            }
        }
    }

    for (i = 0 ; i < N; ++i) {
        if (op[i] == 0) {
            printf("%d + %d = %d\n", x[i], y[i], x[i] + y[i]);
        } else if (op[i] == 1) {
            printf("%d - %d = %d\n", x[i], y[i], x[i] - y[i]);
        } else {
            printf("%d * %d = %I64d\n", x[i], y[i], 1ll * x[i] * y[i]);
        }
    }
    return 0;
}