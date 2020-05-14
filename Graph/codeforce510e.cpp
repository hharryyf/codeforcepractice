#include <bits/stdc++.h>
#define MAX_SIZE 311
typedef long long ll;
#define INF 10000000011
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

int a[311];
vector<int> prime;
int visited[20111];

void preprocess() {
    int i, j;
    for (i = 2; i < 20001; ++i) {
        if (!visited[i]) {
            prime.push_back(i);
            for (j = 1; j * i < 20001; ++j) {
                visited[i * j] = 1;
            }
        }
    }
}

bool isprime(int v) {
    return binary_search(prime.begin(), prime.end(), v);
}

vector<int> g[311];
int vis[311];
vector<vector<int>> ans;

void dfs(int v) {
    ans.back().push_back(v);
    vis[v] = 1;
    for (auto nv : g[v]) {
        if (!vis[nv]) {
            dfs(nv);
        }
    }
}

int main() {
    int i, n, j, odd = 0, even = 0;
    scanf("%d", &n);
    preprocess();
    mf.s = 0, mf.t = MAX_SIZE - 1;
    for (i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        if (a[i] % 2 == 0) {
            even++;
            mf.addedge(i, mf.t, 2);
        } else {
            odd++;
            mf.addedge(mf.s, i, 2);
        }
    }

    if (even != odd) {
        printf("Impossible\n");
        return 0;
    }

    for (i = 1; i <= n; ++i) {
        if (a[i] % 2 == 1) {
            for (j = 1; j <= n; ++j) {
                if (isprime(a[i] + a[j])) {
                    mf.addedge(i, j, 1);
                }
            }
        }
    }

    if (mf.Dinic() != n) {
        printf("Impossible\n");
        return 0;
    }

    for (auto e : mf.edg) {
        if (e.from >= 1 && e.from <= n && e.to >= 1 && e.to <= n && e.flow == e.capacity && e.flow == 1) {
            g[e.from].push_back(e.to);
            g[e.to].push_back(e.from);
        }
    }

    for (i = 1; i <= n; ++i) {
        if (!vis[i]) {
            ans.push_back(vector<int>());
            dfs(i);
        }
    }

    printf("%d\n", (int) ans.size());
    for (auto &vc : ans) {
        printf("%d ", (int) vc.size());
        for (auto v : vc) {
            printf("%d ", v);
        }
        printf("\n");
        for (i = 0 ; i < (int) vc.size() - 1; ++i) {
            if (!isprime(a[vc[i]] + a[vc[i+1]])) {
                cout << "wrong answer!" << endl;
            }
        }
        if (!isprime(a[vc.front()] + a[vc.back()])) {
            cout << "wrong answer!" << endl;
        }
    }
    return 0;
}