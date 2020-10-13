#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;
typedef long long ll;
vector<int> g[MAX_SIZE][2];
int visited[MAX_SIZE];
int dist[MAX_SIZE][2];
struct edge {
	int from, to;
};

edge edg[MAX_SIZE];
int path[MAX_SIZE];
const int inf = 1e7;
int n, m, k;
vector<int> dag[MAX_SIZE];
void BFS(int src, int dim) {
	int i;
	for (i = 0 ; i < MAX_SIZE; ++i) {
		dist[i][dim] = inf, visited[i] = 0;
	}

	dist[src][dim] = 0;
	queue<int> q;
	q.push(src);
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		if (visited[v] == 1) continue;
		visited[v] = 1;
		for (auto nv : g[v][dim]) {
			if (!visited[nv]) {
				dist[nv][dim] = min(dist[nv][dim], dist[v][dim] + 1);
				q.push(nv);
			}
		}
	}
}

void addedge(int from, int to) {
	g[from][0].push_back(to);
	g[to][1].push_back(from);
}

int main() {
	int i;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= m; ++i) {
		scanf("%d%d", &edg[i].from, &edg[i].to);
		addedge(edg[i].from, edg[i].to);
	}
	

	scanf("%d", &k);
	for (i = 1 ; i <= k; ++i) {
		scanf("%d", &path[i]);
	}

	BFS(path[1], 0);
	BFS(path[k], 1);
	for (i = 1; i <= m; ++i) {
		int u = edg[i].from, v = edg[i].to;
		if (1 + dist[v][1] == dist[u][1]) {
			dag[u].push_back(v);
		}
	}

	int cnt1 = 0, cnt2 = 0;
	for (i = 2; i <= k; ++i) {
		int p1 = path[i-1], p2 = path[i];
		if (1 + dist[p2][1] != dist[p1][1]) {
			cnt1++, cnt2++;
		} else if ((int) dag[p1].size() > 1) {
			cnt2++;
		}
	}

	printf("%d %d\n", cnt1, cnt2);
	return 0;
}