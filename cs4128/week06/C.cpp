#include <bits/stdc++.h>
#define MAX_SIZE 54
#define INF 1e17
using namespace std;
typedef long long ll;
struct edge {
	int from, to;
	ll flow, capacity;
};

int s, t;

int n, m;
ll x;

vector<edge> edg;
vector<int> g[MAX_SIZE];

vector<pair<pair<int, int>, ll> > original;

// distance array and visited array
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


void init() {
	edg.clear();
	int i;
	for (i = 1; i <= n; i++) {
		g[i].clear();
	}
}

bool judge(double tol) {
	init();
	for (auto p : original) {
		addedge(p.first.first, p.first.second, (ll) min(1.0 * x, (p.second * x / tol)));
	}
	s = 1, t = n;
	ll ret = Dinic();	
	// cout << ret << " " << tol << " " << x << endl;
	return ret >= x;
}

int main() {
	scanf("%d%d%lld", &n, &m, &x);
	int i;
	for (i = 0 ; i < m; i++) {
		int v1, v2;
		ll w;
		scanf("%d%d%lld", &v1, &v2, &w);
		original.push_back(make_pair(make_pair(v1, v2), w));
	}
	
	double low = 0.0, high = 5.0 * 1e8;
	double ans = 0.0;
	// cout << judge(1) << endl;
	// cout << "------------" << endl;
	for (i = 0; i < 200; i++) {
		double mid = low + (high - low) / 2.0;
		if (judge(mid)) {
			ans = max(ans, mid);
			low = mid + (1e-9);
		} else {
			high = mid - (1e-9);
		}
	}
	printf("%.9lf\n", ans);
	return 0;
}
