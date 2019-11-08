#include <bits/stdc++.h>
#define MAX_SIZE 4511
#define INF 10000000000000
typedef long long ll;
using namespace std;

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

char st[14011];
unordered_set<string> sts[211];

void init() {
	
	edg.clear();
	int i;
	for (i = 0 ; i < MAX_SIZE; i++) {
		g[i].clear();
	}
	
	for (i = 0 ; i < 211; i++) {
		sts[i].clear();
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

int main() {
	int k, n, m, T, i, j;
	ll U = 100000;
	scanf("%d", &T);
	for (k = 1; k <= T; k++) {
		scanf("%d", &n);
		fgets(st, 14011, stdin);
		init();
		unordered_map<string, int> wd;
		for (j = 1; j <= n; j++) {
			fgets(st, 14011, stdin);
			string str = st;
			istringstream ss(str);
			while (ss >> str) {
				sts[j].insert(str);
			}			
		}
		
		for (j = 1; j <= n; j++) {
			for (auto str : sts[j]) {
				wd[str] = 0;
			}
		}
		
		int cnt = 1;
		unordered_map<string, int> :: iterator iter = wd.begin(); 
		while (iter != wd.end()) {
			iter->second = cnt++;
			iter++;
		}
		
		m = (int) wd.size();
		s = 0, t = 2 * m + 2 * n + 1;
		for (i = 1; i <= n; i++) {
			if (i == 2) {
				addedge(s, i, U * U);
			} else {
				addedge(s, i, U);
			}
			addedge(i, i + n, U * U);
		}
		
		for (i = n + 1; i <= 2 * n; i++) {
			if (i == n + 1) {
				addedge(i, t, U * U);
			} else {
				addedge(i, t, U);
			}
		}
		
		for (i = 1; i <= m; i++) {
			addedge(2 * n + i, 2 * n + i + m, 1);
		}
		
		for (i = 1; i <= n; i++) {
			for (auto str : sts[i]) {
				addedge(i, 2 * n + wd[str], U * U);
				addedge(2 * n + m + wd[str], i + n, U * U);
			}
		}
		
		printf("Case #%d: %lld\n", k, Dinic() - n * U);
	}
		
	return 0;
}
