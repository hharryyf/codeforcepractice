#include <bits/stdc++.h>
#define MAX_SIZE 1711
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
char st[51][51];
int visited[51][51], dx[4] = {1, 0, 0, -1}, dy[4] = {0, -1, 1, 0};
int ans = 0, N, M;

int idx(int x, int y) {
	return (x - 1) * M + y;
}

bool valid(int x, int y) {
	return x >= 1 && x <= N && y >= 1 && y <= M;
}

bool ok(int x, int y) {
	int i;
	if (!valid(x, y)) return false;
	if (st[x][y] != 'C') return false;
	for (i = 0 ; i < 4; ++i) {
		int tx = x + dx[i], ty = y + dy[i];
		if (valid(tx, ty) && st[tx][ty] == 'L') return false;  
	}

	return true;
}

void dfs(int x, int y) {
	visited[x][y] = 1;
	int i;
	for (i = 0 ; i < 4; ++i) {
		int tx = dx[i] + x, ty = dy[i] + y;
		if (valid(tx, ty) && st[x][y] == 'L' && !visited[tx][ty]) {
			dfs(tx, ty);
		}
	}
}

int main() {
	int i, j, k, useful = 0;
	scanf("%d%d", &N, &M);
	for (i = 1; i <= N; ++i) {
		scanf("%s", st[i] + 1);
	}

	// printf("111");
	for (i = 1; i <= N; ++i) {
		for (j = 1; j <= M; ++j) {
			if (!visited[i][j] && st[i][j] == 'L') {
				dfs(i, j);
				ans++;
			}
		}
	}
	// printf("222");
	mf.s = 0, mf.t = MAX_SIZE - 1;
	for (i = 1; i <= N; ++i) {
		for (j = 1; j <= M; ++j) {
			if (ok(i, j)) useful++;
		}
	}
	// printf("here\n");
	for (i = 1; i <= N; ++i) {
		for (j = 1; j <= M; ++j) {
			if (!ok(i, j)) continue;
			if ((i + j) % 2 == 1) {
				for (k = 0 ; k < 4; ++k) {
					int tx = i + dx[k], ty = j + dy[k];
					if (ok(tx, ty)) {
						mf.addedge(idx(i, j), idx(tx, ty), INF);
					}
				}
				mf.addedge(mf.s, idx(i, j), 1);
			} else {
				mf.addedge(idx(i, j), mf.t, 1);
			}	
		}
	}
	printf("%d\n", ans + useful - (int) mf.Dinic());
	return 0;
}
