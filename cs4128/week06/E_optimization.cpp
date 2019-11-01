#include <bits/stdc++.h>

#define MAX_SIZE 121
#define INF 1e9
#define NOFLOW 1e-8
typedef double TP;

using namespace std;

/* The second version, optimized algorithm */

/* 
	a super source s to all the original vertices with capacity U, U is a large number 
	all the original vertices capacity 1, bidirectional edges
	all the vertices to a super sink t with capacity U + 2 * mid - d[v], which d[v] is the degree of v
	
	Proof of the algorithm.
	Consider the fraction programming problem, we tried to maximize mid = |E'| / |V'|, which 
	When the fraction programming problem is optimized max(|E'| - mid * |V'|).
	For a graph, we can split it into 2 parts, V1 and V2 which V2 is the complement of V1.
	Suppose that V1 is the optimal subset of vertices, then it is obviously true that selecting
	all the e(u, v), which u belongs to V1 and v belongs to V1 won't make things worse.
	Hence, we have E' = sum(d[v], v belongs to V1) - c[V1, V2]
	Then we want to find min(sum(ans, v belongs to V') - sum(1, e belongs to E'))
	= min(sum(ans, v belongs to V1) - (sum(d[v], v belongs to V1) / 2 - c[V1, V2]). (*)
	
	Let V = S - {s}, V' = T - {t}.
	Consider c[S, T] = sum(c(u, v), u belongs to S, v belongs to T)
	= sum(c(s, v), v belongs to V') + sum(c(u, t), u belongs to V) 
	+ sum(c(u, v), u belongs to V, v belongs to V')
	= sum(U, v belongs to V') + sum(U + 2 * mid - d[u], u belongs to V) + 
	sum(1, u belongs to V and v belongs to V')
	= U * |totalV| + sum(2 * mid - d[u] + sum(1, v belongs to V'), u belongs to V)
	+ U * |totalV| + sum(2 * mid - sum(1, v belongs to V, e(u,v)), u belongs to V)  // us the *
	= U*n + 2 * mid * |V| - 2 * |E'| = U * n - 2 * (|E'| - mid * |V'|)
	Hence the maximum value |E'| - mid * |V'| is reached when a we c[S, T] is minimum
	and in the end we would like U * n - c[S, T]/2 = 0 for the |E'| / |V'|.
*/

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
int indegree[MAX_SIZE];

TP Dinic(){
    TP flow=0;
    while(bfs()){
        memset(cur,0,sizeof(cur));
        flow += dfs(s,INF);
    }
    return flow;
}

double U = 102.0;

void build(TP curr) {
	memset(indegree, 0, sizeof(indegree));
	init();
	s = 0, t = n + 1;
	for (auto ee : inedge) {
		indegree[ee.first]++;
		indegree[ee.second]++;
		addedge(ee.first, ee.second, 1);
		addedge(ee.second, ee.first, 1);
	}
	
	for (int i = 1; i <= n; i++) {
		addedge(s, i, U);
		addedge(i, t, U + 2 * curr - indegree[i]);
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
	int i, v1, v2;
	double ept = 1e-7;
	while (scanf("%d%d", &n, &m) != EOF) {
		if (m == 0) {
			cout << 1 << endl;
			cout << 1 << endl;
			cout << endl;
			continue;
		}
		
		inedge = vector<pair<int, int> >();
		for (i = 0 ; i < m; i++) {
			scanf("%d%d", &v1, &v2);
			inedge.emplace_back(v1, v2);
		}
		
		double low = 0, high = 1.0 * m;
		ept = 1.0 / (1.0 * n) / (1.0 * n);
		while (low + ept < high) {
			double mid = low + (high - low) / 2.0;
			build(mid);
			TP res = Dinic();
			TP ret = (U * n -  res) / 2.0;
			
			if (ret > NOFLOW) {
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
		for (int i = 1; i <= n; i++) {
			if (visited2[i]) {
				ret.push_back(i);
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
