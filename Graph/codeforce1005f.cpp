#include <bits/stdc++.h>
#define MAX_SIZE 200011
#define MAX_V 2000011
using namespace std;

struct edge {
	int to, id;
};

vector<edge> g[MAX_SIZE];
// the shortest path dag
vector<edge> dag[MAX_SIZE];
int dist[MAX_SIZE];
bool visited[MAX_SIZE];
int n, k, m;
int curr[MAX_V];
vector<vector<char> > ans;
// find the shortest path from 1 to all the other nodes
// construct the shortest path dag
void BFS() {
	int i;
	// since this is an unweighted graph, we just set the INF to 4e5
	for (i = 2; i <= n; ++i) dist[i] = (MAX_SIZE << 1);
	queue<pair<int, int> > q;
	q.push(make_pair(1, 0));
	while (!q.empty()) {
		auto p = q.front();
		q.pop();
		if (visited[p.first]) continue;
		visited[p.first] = true;
		for (auto e : g[p.first]) {
			int nv = e.to;
			if (!visited[nv]) {
				if (dist[nv] == p.second + 1) {
					dag[nv].push_back(edge{p.first, e.id});
				} else if (dist[nv] > p.second + 1) {
					dag[nv].push_back(edge{p.first, e.id});
					dist[nv] = p.second + 1;
					q.push(make_pair(nv, p.second + 1));
				}
			}
		}
	}
}

void dfs(int v) {
	if ((int) ans.size() >= k) return;
	if (v == n + 1) {
		int sz = ans.size(), i;
		ans.push_back(vector<char>());
		for (i = 1; i <= m; ++i) {
			ans[sz].push_back(curr[i] + '0');
		}
		return;
	}
	
	for (auto e : dag[v]) {
		curr[e.id] = 1;
		dfs(v + 1);
		curr[e.id] = 0;
	}
}

int main() {
	int i;
	scanf("%d%d%d", &n, &m, &k);
	for (i = 1; i <= m; ++i) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		g[v1].push_back(edge{v2, i});
		g[v2].push_back(edge{v1, i});
	}
	
	BFS();
	
	dfs(2);
	int sz = ans.size();
	printf("%d\n", sz);
	for (i = 0 ; i < sz; ++i) {
		for (auto ch : ans[i]) {
			putchar(ch);
		}
		putchar('\n');
	}
	
	return 0;
}