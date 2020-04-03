#include <bits/stdc++.h>
#define MAX_SIZE 10111
#define INF 1000000000000ll
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
int n, b, q;
pair<int, int> v[MAX_SIZE];

int cnt(int x, int mod) {
	if (x < mod) return 0;
	return (x - mod) / 5 + 1;
}
/*
int judge(int l, int r, int mod) {
	int ret = 0;
	while (l <= r) {
		ret += (l % 5 == mod % 5);
		l++;
	}
	return ret;
}
*/
int count(int l, int r, int mod) {
	int ret = cnt(r, mod) - cnt(l-1, mod);
	//cout << l <<" to " << r << " has " << ret << " %% " << mod << endl;
	// if (ret != judge(l, r, mod)) cout << "wrong answer" << endl;
	return ret;
}

int main() {
	int i, j;
	scanf("%d%d%d", &n, &b, &q);
	
	if (n % 5) {
		printf("unfair\n");
		return 0;
	}
	
	for (i = 1; i <= q; ++i) {
		scanf("%d%d", &v[i].first, &v[i].second);
	}
	
	sort(v + 1, v + 1 + q);
	
	mf.s = 0, mf.t = MAX_SIZE - 1;
	
	int d[6];
	
	for (i = 1; i <= 5; ++i) {
		d[i] = mf.t - i - 1;
		mf.addedge(mf.s, d[i], n / 5);
	}
	
	for (i = 1; i <= q; ++i) {
		if (i == 1) {
			for (j = 1 ; j <= 5; ++j) {
				mf.addedge(d[j], i, count(1, v[i].first, j));
			}
			mf.addedge(i, mf.t, v[i].second);
			continue;
		}
		
		if (i > 1 && v[i].first == v[i-1].first) {
			if (v[i].second != v[i-1].second) {
				printf("unfair\n");
				return 0;
			}
			continue;
		}
		
		if (v[i].second < v[i-1].second) {
			printf("unfair\n");
			return 0;
		}
		
		for (j = 1 ; j <= 5; ++j) {
			mf.addedge(d[j], i, count(v[i-1].first + 1, v[i].first, j));
		}
		mf.addedge(i, mf.t, v[i].second - v[i-1].second);
	}
	
	if (v[q].first < b) {
		for (j = 1 ; j <= 5; ++j) {
			mf.addedge(d[j], q + 1, count(v[q].first + 1, b, j));
		}
		mf.addedge(q + 1, mf.t, n - v[q].second);
		if (v[q].second > n) {
			printf("unfair\n");
			return 0;
		}
	}
	
	auto p = mf.Dinic();
	
	for (auto e : mf.edg) {
		if (e.from <= q && e.to == mf.t && e.flow != e.capacity) {
			printf("unfair\n");
			return 0;
		}
	}
	
	printf("%s\n", p == n ? "fair" : "unfair");
	return 0;
}