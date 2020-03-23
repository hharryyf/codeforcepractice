#include <bits/stdc++.h>
#define MAX_SIZE 10111
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


vector<int> prime;
int visited[MAX_SIZE << 2];
unordered_map<int, int> fac[MAX_SIZE];
unordered_map<int, int> id[MAX_SIZE];

int main() {
	int i, j, n, m, cnt;
	mf.s = 0, mf.t = MAX_SIZE - 1;
	for (i = 2; i <= 31621; ++i) {
		if (!visited[i]) {
			prime.push_back(i);
			for (j = 1; j * i <= 31621; ++j) {
				visited[i * j] = 1;
			}
		} 
	}
	
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n; ++i) {
		int v;
		cnt = 0;
		scanf("%d", &v);
		for (j = 0 ; j < (int) prime.size(); ++j) {
			if (v <= 1) break;
			while (v % prime[j] == 0) {
				fac[i][prime[j]]++;
				v = v / prime[j];
				cnt++;
			}
		}
		
		if (v > 1) {
			fac[i][v]++;
			cnt++;
		}
		
		if (i & 1) {
			mf.addedge(mf.s, i, cnt);
		} else {
			mf.addedge(i, mf.t, cnt);
		}
	}
	
	cnt = n + 1;
	for (i = 1; i <= n; ++i) {
		auto iter = fac[i].begin();
		// cout << "number id " << i << endl;
		while (iter != fac[i].end()) {
			id[i][iter->first] = cnt++;
			// cout << iter->first << " counts " << iter->second << endl;
			iter++;
		}
	}
	
	for (i = 1; i <= n; ++i) {
		auto iter = id[i].begin();
		while (iter != id[i].end()) {
			if (i & 1) {
				mf.addedge(i, iter->second, fac[i][iter->first]);
			} else {
				mf.addedge(iter->second, i, fac[i][iter->first]);
			}
			iter++;
		}
	}
	
	for (i = 1; i <= m; ++i) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		if (v2 & 1) swap(v1, v2);
		auto iter = fac[v1].begin();
		while (iter != fac[v1].end()) {
			if(fac[v2].find(iter->first) != fac[v2].end()) {
				mf.addedge(id[v1][iter->first], id[v2][iter->first],INF);
			}
			iter++;
		}
	}
	printf("%I64d\n", mf.Dinic());
	return 0;
}