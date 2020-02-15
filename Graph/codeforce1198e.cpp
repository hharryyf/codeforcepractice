#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 711
typedef long long ll;
#define INF 10000000000000
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
int m;
struct rec {
    int x1, y1, x2, y2;
};

vector<rec> rt;
vector<int> disc1;
vector<int> disc2;
int tmp1[MAX_SIZE], tmp2[MAX_SIZE];
int sz1, sz2;
// rc = 1 for rows, 2 for cols
int index(int i, int rc) {
	if (rc == 1) {
	   return 1 + i;
	} 
	
	return sz1 + 1 + i;
}
// x1 <= x2, y1 <= y2
bool fullcovered(int x1, int x2, int y1, int y2) {
	 for (rec r : rt) {
	 	 if ((r.x1 <= x1) && (x2 <= r.x2) && (r.y1 <= y1) && (y2 <= r.y2)) {
			 return true;
         }
	 }
	 
	 return false;
}

int main() {
	int n, i, j, cnt = 0;
	scanf("%d%d", &n, &m);
	for (i = 0 ; i < m; i++) {
		int v1, v2, v3, v4;
		scanf("%d%d%d%d", &v1, &v2, &v3, &v4);
		rt.push_back(rec{v1, v2, v3+1, v4+1});
		tmp1[cnt] = v1, tmp2[cnt++] = v2;
		tmp1[cnt] = v3+1, tmp2[cnt++] = v4+1;
	}
	
	sort(tmp1, tmp1 + cnt);
	sort(tmp2, tmp2 + cnt);
	
	for (i = 0 ; i < cnt; i++) {
		if (i == 0 || tmp1[i] != tmp1[i-1]) disc1.push_back(tmp1[i]);
		if (i == 0 || tmp2[i] != tmp2[i-1]) disc2.push_back(tmp2[i]);
	}
	
	sz1 = (int) disc1.size(), sz2 = (int) disc2.size();
	mf.s = 0, mf.t = sz1 + sz2 + 3;
	
	for (i = 0 ; i < sz1-1; i++) {
		mf.addedge(mf.s, index(i,1), disc1[i+1] - disc1[i]);
	}
	
	for (i = 0 ; i < sz2-1; i++) {
		mf.addedge(index(i, 2), mf.t, disc2[i+1] - disc2[i]);
	}
	
	for (i = 0 ; i < sz1-1; i++) {
		for (j = 0 ; j < sz2-1; j++) {
			if (fullcovered(disc1[i], disc1[i+1], disc2[j], disc2[j+1])) {
			    mf.addedge(index(i, 1), index(j, 2), INF);
			}
		}
	}
	
	printf("%lld\n", mf.Dinic());
	return 0;
}

