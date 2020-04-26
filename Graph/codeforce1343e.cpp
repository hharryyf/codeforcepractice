#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;
typedef long long ll;
const int inf = 10000000;

ll weight[MAX_SIZE];
ll prefix[MAX_SIZE];
vector<int> g[MAX_SIZE];
int dist[MAX_SIZE][3];
bool visited[MAX_SIZE][3];
int n, m, a, b, c;

void BFS(int src, int dim) {
	queue<pair<int, int>> q;
	q.push(make_pair(src, 0));
	while (!q.empty()) {
		auto p = q.front();
		q.pop();
		if (visited[p.first][dim]) continue;
		visited[p.first][dim] = true;
		dist[p.first][dim] = p.second;
		for (auto e : g[p.first]) {
			if (!visited[e][dim]) {
				q.push(make_pair(e, p.second + 1));
				dist[e][dim] = min(dist[e][dim], p.second + 1);
			}
		}
	}
}


int main() {
	int T, i;
	scanf("%d", &T);
	while (T > 0) {
		scanf("%d%d%d%d%d", &n, &m, &a, &b, &c);
		for (i = 1; i <= n; ++i) {
			g[i].clear();
			dist[i][0] = dist[i][1] = dist[i][2] = inf;
			visited[i][0] = visited[i][1] = visited[i][2] = false;
		}
		for (i = 1; i <= m; ++i) {
			scanf("%I64d", &weight[i]);
			prefix[i] = 0;
		}
		
		for (i = 1; i <= m; ++i) {
			int v1, v2;
			scanf("%d%d", &v1, &v2);
			g[v1].push_back(v2);
			g[v2].push_back(v1);
		}
		
		BFS(a, 0);
		BFS(b, 1);
		BFS(c, 2);
		sort(weight + 1, weight + 1 + m);
		for (i = 1; i <= m; ++i) {
			prefix[i] = prefix[i-1] + weight[i];
		}
		// there are only 2 possible cases, a->b->c
		// and a->v->b->v->c
		// here v is any point
		ll ans = 1e17;
		
		for (i = 1; i <= n; ++i) {
			// the edge weight distrubuting likes this
			// b->v first len edges, v->c, next dist(b, c) - len edges, v->a, next dist(a, b) - len edges
			if (dist[i][0] + dist[i][1] + dist[i][2] <= m) {
					int len =  dist[i][1];
					ans = min(ans, prefix[dist[i][0] + dist[i][1] + dist[i][2]] + prefix[len]);
			}
		}
		
		printf("%I64d\n", ans);
		--T;
	}
	return 0;
}