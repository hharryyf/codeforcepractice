#include <bits/stdc++.h>
#define MAX_SIZE 3111
using namespace std;
typedef long long ll;
#define INF 10000000000ll

// we have at most 1000 horizontal points and 1000 vertical points
// hence 3111 is enough

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
// y -> {x}
unordered_map<int, vector<int>> hz;
// x -> {y}
unordered_map<int, vector<int>> vc;
int tx[MAX_SIZE], ty[MAX_SIZE];
// horizontal segments and vertical segments
vector<pair<pair<int, int>, int>> hs, vs;
int x[MAX_SIZE], y[MAX_SIZE];
set<pair<pair<int, int>, int>> elih, eliv;
set<pair<int, int>> valid;
vector<pair<pair<int, int>, int>> ansh, ansv;
int visited[MAX_SIZE];

void dfs(int v) {
	visited[v] = 1;
	for (auto idx : mf.g[v]) {
		auto e = mf.edg[idx];
		if (e.flow != e.capacity && !visited[e.to]) {
			dfs(e.to);
		}
	}
}

int main() {
	int n, i, j;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) {
		scanf("%d%d", &tx[i], &ty[i]);
		hz[ty[i]].push_back(tx[i]);
		vc[tx[i]].push_back(ty[i]);
		x[i] = tx[i], y[i] = ty[i];
		valid.insert(make_pair(x[i], y[i]));
	}
	
	mf.s = 0, mf.t = MAX_SIZE - 1;
	
	auto iter = hz.begin();
	while (iter != hz.end()) {
		sort(iter->second.begin(), iter->second.end());
		for (i = 1 ; i < (int) iter->second.size(); ++i) {
			hs.push_back(make_pair(make_pair(iter->second[i-1], iter->second[i]), iter->first));
		}
		++iter;
	}
	
	iter = vc.begin();
	while (iter != vc.end()) {
		sort(iter->second.begin(), iter->second.end());
		for (i = 1 ; i < (int) iter->second.size(); ++i) {
			vs.push_back(make_pair(make_pair(iter->second[i-1], iter->second[i]), iter->first));
		}
		++iter;
	}
	
	int sz1 = hs.size(), sz2 = vs.size();
	for (i = 1; i <= sz1; ++i) {
		mf.addedge(mf.s, i, 1);
	}
	
	for (i = 1; i <= sz2; ++i) {
		mf.addedge(i + sz1, mf.t, 1);
	}
	//cout << "h1 sz= " << sz1 << endl;
	//cout << "h2 sz= " << sz2 << endl;
	for (i = 1; i <= sz1; ++i) {
		for (j = 1 ; j <= sz2; ++j) {
			auto p1 = hs[i-1], p2 = vs[j-1];
			int x1 = p1.first.first, x2 = p1.first.second, y = p1.second;
			int y1 = p2.first.first, y2 = p2.first.second, x = p2.second;
			if (x1 <= x && x <= x2 && y1 <= y && y <= y2) {
				if (valid.find(make_pair(x, y)) == valid.end()) {
					mf.addedge(i, j + sz1, INF);
					// cout << x1 << " " << x2 << " " << y << " and " << x << " " << y1 << " " << y2 << " cross at invalid point" << endl;
				}
			}
		}
	}
	
	mf.Dinic();
	
	dfs(mf.s);
	
	for (auto e : mf.edg) {
		if (visited[e.from] && !visited[e.to]) {
			if (e.from == mf.s && e.to <= sz1 && e.flow == e.capacity) {
				elih.insert(hs[e.to-1]);
				// cout << "eliminate " << hs[e.to-1].second << endl;
			}
			
			if (e.to == mf.t && e.from > sz1 && e.flow == e.capacity) {
				eliv.insert(vs[e.from - sz1 - 1]);
				// cout << "elimi " << vs[e.from - sz1 - 1].second << endl;
			}
		}
	}
	
	iter = hz.begin();
	while (iter != hz.end()) {
		int low = iter->second[0], high = iter->second[0], y = iter->first;
		for (i = 0 ; i < (int) iter->second.size() - 1; ++i) {
			int x1 = iter->second[i], x2 = iter->second[i+1];
			if (elih.find(make_pair(make_pair(x1, x2), y)) == elih.end()) {
				high = x2;
			} else {
				ansh.push_back(make_pair(make_pair(low, high), y));
				low = x2, high = x2;
			}
		} 
		ansh.push_back(make_pair(make_pair(low, high), y));
		++iter;
	}
	
	iter = vc.begin();
	while (iter != vc.end()) {
		int low = iter->second[0], high = iter->second[0], y = iter->first;
		for (i = 0 ; i < (int) iter->second.size() - 1; ++i) {
			int x1 = iter->second[i], x2 = iter->second[i+1];
			if (eliv.find(make_pair(make_pair(x1, x2), y)) == eliv.end()) {
				high = x2;
			} else {
				ansv.push_back(make_pair(make_pair(low, high), y));
				low = x2, high = x2;
			}
		} 
		ansv.push_back(make_pair(make_pair(low, high), y));
		++iter;
	}
	
	printf("%d\n", (int) ansh.size());
	for (auto p : ansh) {
		printf("%d %d %d %d\n", p.first.first, p.second, p.first.second, p.second);
	}
	
	printf("%d\n", (int) ansv.size());
	for (auto p : ansv) {
		printf("%d %d %d %d\n", p.second, p.first.first, p.second, p.first.second);
	}
	return 0;
}