#include <bits/stdc++.h>
#define MAX_SIZE 1111
#define INF 1e9
#define NOFLOW 1e-8
typedef double TP;
using namespace std;

struct edge {
	int from, to;
	TP flow, capacity;
};

// start and end point
int s, t;

// n vertices and m edges
int n, m;

// list array
vector<edge> edg;

// g reference to the ith vertex's edges
vector<int> g[MAX_SIZE];

// distance array and visited array
int dist[MAX_SIZE], visited[MAX_SIZE];
int cur[MAX_SIZE];

/* first version without the optimization */

void init() {
	edg.clear();
	int i;
	for (i = 0 ; i < MAX_SIZE; i++) {
		g[i].clear();
	}
}

void addedge(int from, int to, TP capacity) {
	edge e1 = edge{from, to, 0, capacity};
	edge e2 = edge{to, from, 0, 0};
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
			if (!visited[nxt] && e.capacity > NOFLOW + e.flow) {
				dist[nxt] = dist[v] + 1;
				q.push(nxt);
				visited[nxt] = 1;
			}  
		}
	}
	
	return visited[t];
}

TP dfs(int x, TP cp) {
	if (x == t || cp == 0) {
		return cp;
	}
	
	TP flow = 0, newflow;
	for (int &y = cur[x]; y < (int) g[x].size(); y++) {
		edge &e = edg[g[x][y]];
		if (dist[x] + 1 == dist[e.to]) {
			TP minn = min(cp, e.capacity - e.flow);
			newflow = dfs(e.to, minn);
			if (newflow > NOFLOW) {
				e.flow += newflow;
				edg[g[x][y] ^1].flow -= newflow;
				flow += newflow;
				cp -= newflow;
				
				if (cp < NOFLOW) {
					break;
				}
			}
		}
	}
	
	return flow;
}


vector<pair<int, int> > inedge;

TP Dinic(){
    TP flow=0;
    while(bfs()){
        memset(cur,0,sizeof(cur));
        flow += dfs(s,INF);
    }
    return flow;
}


void build(TP curr) {
	// we connect all the edges src use a 1 edge
	// we connect all the vertex to t using a curr edge
	// we connect all the edges to its to vertices with an INF edge
	int i;
	init();
	s = 0, t = n + m + 1;
	for (i = 0; i < m; i++) {
		addedge(s, i + 1, 1.0);
		addedge(i + 1, inedge[i].first + m, INF);
		addedge(i + 1, inedge[i].second + m, INF);
	}
	
	for (i = 0; i < n; i++) {
		addedge(i + m + 1, t, curr);
	}
}

int visited2[MAX_SIZE];

void getans(int src) {
	visited2[src] = 1;
	int i;
	for (i = 0 ; i < (int) g[src].size(); i++) {
		edge e = edg[g[src][i]];
		if (e.flow + NOFLOW < e.capacity && !visited2[e.to]) {
		//	cout << src << " " << e.from << " " << e.to << " " << e.flow << " " << e.capacity << endl;
			getans(e.to);
		}
	}
}

int main() {
	double ept = 1e-7;
	while(scanf("%d%d", &n, &m) != EOF) {
		if (m == 0) {
			cout << 1 << endl;
			cout << 1 << endl;
			cout << endl;
			continue;
		}
		// we have m edges, and n vertices
		// start the binary search for the g value
		TP low = 0.0, high = m * 1.0;
		inedge = vector<pair<int, int> >();
		for (int i = 0; i < m; i++) {
			int v1, v2;
			scanf("%d%d", &v1, &v2);
			inedge.emplace_back(v1, v2);
		}
		ept = 1.0 / (n * 1.0) / (n * 1.0);
		while (low + ept < high) {
			TP mid = low + (high - low) / 2;
			build(mid);
			TP mp = m - Dinic();
			// we should increase mid, since the function is monetonically decreasing 
			if (mp > NOFLOW) {
				low = mid;
			} else {
				high = mid;
			}	
		}
		build(low);
		Dinic();
		memset(visited2, 0, sizeof(visited2));
		getans(s);
		
		vector<int> ret;
		for (int i = m + 1; i <= m + n; i++) {
			if (visited2[i]) {
				ret.push_back(i-m);
			}
		}
		
		cout << ret.size() << endl;
		for (auto r : ret) {
			cout << r << endl;
		}
		cout << endl;
	}
	return 0;
}
