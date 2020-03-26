#include <bits/stdc++.h>
#define MAX_SIZE 13111
#define INF 10000000000ll
typedef long long ll;
using namespace std;

// at most 10000 materials and 2000 roads
// hence 13111 is enough for size of the node
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

int low[MAX_SIZE], visited[MAX_SIZE];
int cnt = 1;
int bridge[MAX_SIZE];

int tmp[MAX_SIZE];
vector<int> disc;
vector<int> p[MAX_SIZE];
vector<pair<int, int>> g[MAX_SIZE];
unordered_map<int, unordered_set<int>> occ;
pair<int, int> road[MAX_SIZE];
int ans[MAX_SIZE];
int cm[MAX_SIZE];

void dfs(int v, int pre) {
	low[v] = visited[v] = cnt;
	cnt++;
	for (auto np : g[v]) {
		int nv = np.first, id = np.second;
		if (nv != pre) {
			if (!visited[nv]) {
				dfs(nv, v);
				low[v] = min(low[v], low[nv]);
				if (visited[v] < low[nv]) {
					bridge[id] = 1;
				}
			} else {
				low[v] = min(visited[nv], low[v]);
			}
		}
	}
}


int getindex(int mt) {
	if (!binary_search(disc.begin(), disc.end(), mt)) return MAX_SIZE;
	return lower_bound(disc.begin(), disc.end(), mt) - disc.begin() + 1;
}

int main() {
	int n, k, i, m, j = 0;
	scanf("%d%d", &n, &k);
	for (i = 1; i <= n; ++i) {
		int v;
		scanf("%d", &v);
		g[i].emplace_back(v, i);
		g[v].emplace_back(i, i);
		road[i] = {i, v};
		scanf("%d", &m);
		while (m > 0) {
			int mt;
			scanf("%d", &mt);
			tmp[j++] = mt;
			occ[mt].insert(i);
			m--;
		}
	}
	
	sort(tmp, tmp + j);
	
	for (i = 0 ; i < j; ++i) {
		if (i == 0 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
	}
	
	mf.s = 0, mf.t = MAX_SIZE - 1;
	
	int sz = disc.size();
	for (i = 1; i <= k; ++i) {
		int v;
		scanf("%d", &v);
		int idx = getindex(v); 
		if (idx <= sz) {
			p[getindex(v)].push_back(i);
		}
	}
	
	for (i = 1; i <= sz; ++i) {
		mf.addedge(mf.s, i, p[i].size());
		for (auto v : occ[disc[i-1]]) {
			mf.addedge(i, v + sz, 1);
		}
	}
	
	dfs(1, 0);
	
	j = 0;
	for (i = 1; i <= n; ++i) {
		// cout << i << " bridge " << bridge[i] << endl;
		if (!bridge[i]) {
			j++;
			mf.addedge(i + sz, MAX_SIZE - 2, 1);
		} else {
			mf.addedge(i + sz, mf.t, 1);
		}
	}
	
	mf.addedge(MAX_SIZE - 2, mf.t, j-1);
	
	if (mf.Dinic() != n - 1) {
		printf("-1\n");
		return 0;
	}
	
	for (auto e : mf.edg) {
		if (e.from <= sz && e.to > sz && e.capacity == e.flow) {
			cm[e.to - sz] = e.from;
		}
	}
	
	for (i = 1; i <= n; ++i) {
		if (cm[i]) {
			ans[p[cm[i]].back()] = i;
			p[cm[i]].pop_back();
		}
	}
	
	for (i = 1; i <= k; ++i) {
		if (ans[i]) {
			printf("%d %d\n", road[ans[i]].first, road[ans[i]].second);
		} else {
			printf("0 0\n");
		}
	}
	return 0;
}
/*
5 7
2 2 1 3
3 1 2
1 1 5
1 2 1 2
2 2 1 4
1 3 4 9 6 2 8
*/