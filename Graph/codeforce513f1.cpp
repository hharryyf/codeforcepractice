#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 2011
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

ll dist[MAX_SIZE][MAX_SIZE];
char g[MAX_SIZE][MAX_SIZE];
int n, m, male, female;

int in(int x) {
    return x * 2;
}

int out(int x) {
    return x * 2 + 1;
}

int index(int x, int y) {
    return x * m + y;
}

void add(int x, int y, int z, int w) {
    if (x < 0 || y < 0 || x >= n || y >= m || z < 0 || z >= n || w < 0 || w >= m) return;
    if (g[x][y] == '#' || g[z][w] == '#') return;
    if (x == z && y == w) {
        dist[index(x, y)][index(z, w)] = 0;
    } else {
        dist[index(x, y)][index(z, w)] = 1;
    }
}

int dx[5] = {1, 0, -1, 0, 0}, dy[5] = {0, 1, 0, -1, 0};

struct people {
    int r, c, speed;
};

vector<people> man, woman;

bool check(ll T) {
    int i, j;
    mf.init();
    mf.s = MAX_SIZE - 2, mf.t = MAX_SIZE - 1;
    for (i = 0 ; i < n * m; ++i) {
        mf.addedge(in(i), out(i), 1);
    }

    int offset = 2 * n * m, sz = man.size();
    for (i = 0 ; i < sz; ++i) {
        mf.addedge(mf.s, i + offset, 1);
        for (j = 0 ; j < n * m; ++j) {
            if (dist[index(man[i].r, man[i].c)][j] >= INF) continue;
            if (dist[index(man[i].r, man[i].c)][j] * man[i].speed > T) continue;
            mf.addedge(i + offset, in(j), 1);
        }
    }

    for (i = 0 ; i < sz; ++i) {
        mf.addedge(i + sz + offset, mf.t, 1);
        for (j = 0 ; j < n * m; ++j) {
            if (dist[index(woman[i].r, woman[i].c)][j] >= INF) continue;
            if (dist[index(woman[i].r, woman[i].c)][j] * woman[i].speed > T) continue;
            mf.addedge(out(j), i + offset + sz, 1);
        }
    }
    // cout << mf.Dinic() << " " << sz << endl;
    return mf.Dinic() == (1ll * sz);
}

int main() {
    int i, j, k;
    int r, c, t;
    scanf("%d%d%d%d", &n, &m, &male, &female); 
    for (i = 0 ; i < n; ++i) {
        scanf("%s", g[i]);
    }

    scanf("%d%d%d", &r, &c, &t);
    r--, c--;
    if (abs(male - female) != 1) {
        printf("-1\n");
        return 0;
    }

    if (male - female == 1) {
        woman.push_back(people{r, c, t});
    } else {
        man.push_back(people{r, c, t});
    }

    for (i = 0 ; i < MAX_SIZE; ++i) {
        for (j = 0 ; j < MAX_SIZE; ++j) {
            dist[i][j] = INF;
        }
    }

    for (i = 0 ; i < n; ++i) {
        for (j = 0 ; j < m; ++j) {
            for (k = 0 ; k < 5; ++k) {
                add(i, j, i + dx[k], j + dy[k]);
            }
        }
    }

    for (i = 0 ; i < male; ++i) {
        scanf("%d%d%d", &r, &c, &t);
        r--, c--;
        man.push_back(people{r, c, t});
    }

    for (i = 0 ; i < female; ++i) {
        scanf("%d%d%d", &r, &c, &t);
        r--, c--;
        woman.push_back(people{r, c, t});
    }
    
    for (k = 0 ; k < n * m; ++k) {
        for (i = 0 ; i < n * m; ++i) {
            for (j = 0 ; j < n * m; ++j) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
/*
    for (i = 0 ; i < n * m; ++i) {
        for (j = 0 ; j < n * m; ++j) {
            cout << dist[i][j] << endl;
        }
    }
*/
    ll low = 0, high = 1e14;
    ll ans = high;
    while (low <= high) {
        ll mid = (low + high) / 2;
        if (check(mid)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    printf("%I64d\n", ans != 1e14 ? ans : -1);
    return 0;
}