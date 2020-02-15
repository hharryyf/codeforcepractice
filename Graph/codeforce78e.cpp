#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 7100
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
char g1[14][14];
char g2[14][14];
bool visited[14][14];
int dist[14][14];
int n;
int tgt[103];

void BFS(int x, int y) {
	queue<pair<pair<int, int>, int> > q;
	int i, j;
	for (i = 0 ; i < 14; i++) {
		for (j = 0 ; j < 14; j++) {
			dist[i][j] = 111;
		}
	} 
	
	dist[x][y] = 0;
	q.push(make_pair(make_pair(x, y), 0));
	int dx[4] = {1, 0, 0, -1}, dy[4] = {0, 1, -1, 0};
	while (!q.empty()) {
        auto p = q.front();
        q.pop();
        if (visited[p.first.first][p.first.second]) continue;
        visited[p.first.first][p.first.second] = true;
        dist[p.first.first][p.first.second] = p.second;
        for (i = 0; i < 4; i++) {
			int tx = dx[i] + p.first.first, ty = dy[i] + p.first.second;
			if (tx <= 0 || tx > n || ty <= 0 || ty > n 
			    || visited[tx][ty] || g1[tx][ty] == 'Y') continue;
			q.push(make_pair(make_pair(tx, ty), p.second + 1));
		}
	}
}

int index(int level, int x, int y) {
	return level * n * n + (x - 1) * n + y;
}

int main() {
	int i, t, j, k;
	scanf("%d%d", &n, &t);
	for (i = 1; i <= n; i++) scanf("%s", g1[i] + 1);
	for (i = 1; i <= n; i++) scanf("%s", g2[i] + 1);
	
	mf.s = 0, mf.t = MAX_SIZE - 2;
	int x = 0, y = 0;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			if (g1[i][j] == 'Z') {
			   x = i, y = j;
			   break;
			}
		}
	}
	
	for (i = 1; i <= n * n; i++) tgt[i] = MAX_SIZE - 3 - (n * n - i);
	
	BFS(x, y);
	
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			if (g1[i][j] >= '0' && g1[i][j] <= '9') 
		        mf.addedge(mf.s, index(0, i, j), g1[i][j] - '0');
			
			if (g2[i][j] >= '0' && g2[i][j] <= '9') 
			    mf.addedge(tgt[index(0, i, j)], mf.t, g2[i][j] - '0');   
			mf.addedge(index(0, i, j), tgt[index(0, i, j)], INF);
		}
	}
	
	int dx[4] = {1, 0, 0, -1}, dy[4] = {0, 1, -1, 0};
	for (i = 1; i <= t; i++) {
		for (j = 1; j <= n; j++) {
			for (k = 1; k <= n; k++) {
				if (g1[j][k] == 'Y' || g1[j][k] == 'Z') continue;
				for (int l = 0 ; l < 4; l++) {
					int tx = dx[l] + j, ty = dy[l] + k;
					if (tx >= 1 && tx <= n && ty >= 1 && ty <= n && g1[tx][ty] != 'Y' && g1[tx][ty] != 'Z') {
					   if (dist[j][k] >= i && dist[tx][ty] >= i && g1[j][k] != 'Y' && g1[j][k] != 'Z') {
					   	  mf.addedge(index(i-1, tx, ty), index(i, j, k), INF);
					   }
					}
				}
				
				mf.addedge(index(i, j, k), tgt[index(0, j, k)], INF);
			}
		}
	}
	printf("%lld\n", mf.Dinic());
	return 0;
}
