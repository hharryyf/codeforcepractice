#include <bits/stdc++.h>
#define MAX_SIZE 811
#define INF 1e13
typedef long long ll;
using namespace std;

struct edge {
	int from, to;
	ll flow, capacity;
};

int n, m, s, t;

vector<edge> edg;
vector<int> g[MAX_SIZE];
int dist[MAX_SIZE], visited[MAX_SIZE];
int cur[MAX_SIZE];

void addedge(int from, int to, int capacity) {
	edge e1 = edge{from, to, 0ll, capacity};
	edge e2 = edge{to, from, 0ll, 0ll};
	edg.push_back(e1), edg.push_back(e2);
	g[from].push_back((int) edg.size() - 2);
	g[to].push_back((int) edg.size() - 1);
}

// construct the level graph
bool bfs() {
	memset(visited,0,sizeof(visited));
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

unordered_set<int> nd;

void reachs(int src) {
	visited[src] = 1;
	nd.insert(src);
	for (int i = 0; i < (int) g[src].size(); i++) {
		edge e = edg[g[src][i]];
		if (!visited[e.to] && e.flow < e.capacity) {
			reachs(e.to);
		}
	}
}

void couldt(int src) {
	visited[src] = 1;
	nd.insert(src);
	
	for (int i = 0; i < (int) g[src].size(); i++) {
		edge e = edg[g[src][i]];
		if (!visited[e.to] && edg[g[src][i]^1].flow < edg[g[src][i]^1].capacity) {
			couldt(e.to);		
		}
	}
}



int main() {
	freopen("attack.in", "r", stdin);
	freopen("attack.out", "w", stdout);
	scanf("%d%d", &n, &m);
	scanf("%d%d", &s, &t);
	int i;
	for (i = 0 ; i < m; i++) {
		int v1, v2;
		ll w;
		scanf("%d%d%lld", &v1, &v2, &w);
		addedge(v1, v2, w);
		addedge(v2, v1, w);
	}
	
	Dinic();
	
	
	memset(visited,0,sizeof(visited));
	reachs(s);
	
	couldt(t);
	
	
	if ((int) nd.size() == n) {
		cout << "UNIQUE" << endl;
	} else {
		cout << "AMBIGUOUS" << endl;
	}
	return 0;
}
