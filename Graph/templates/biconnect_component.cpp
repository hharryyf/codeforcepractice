#include <bits/stdc++.h>
#define MAX_SIZE 200011

using namespace std;

vector<int> graph[MAX_SIZE];

unordered_set<int> res[MAX_SIZE];

int n, m;

int visited[MAX_SIZE];

int low[MAX_SIZE];

int k = 1;

set<pair<int, int> > bridges;

int cn[MAX_SIZE];

int id = 1;

void dfs(int v, int prev) {
	visited[v] = k++;
	low[v] = visited[v];
	for (auto nextv : graph[v]) {
		if (nextv != prev) {
			if (visited[nextv]) {
				low[v] = min(visited[nextv], low[v]);
			} else {	
				dfs(nextv, v);
				low[v] = min(low[nextv], low[v]);
				if (low[nextv] > visited[v]) {
					bridges.insert(make_pair(nextv, v));
					bridges.insert(make_pair(v, nextv));
				}
			}
		}
	}	
}

void dfs2(int v) {
	cn[v] = k;
	for (auto nextv : graph[v]) {
		if (!cn[nextv] && bridges.find(make_pair(v, nextv)) == bridges.end()) {
			dfs2(nextv);
		}
	}
}
int main() {
	int i;
	scanf("%d%d", &n, &m);
	for (i = 0 ; i < m; i++) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		graph[v1].push_back(v2);
		graph[v2].push_back(v1);
	}
	
	for (i = 1 ; i <= n; i++) {
		if (!visited[i]) {
			dfs(i, -1);
		}
	}
	
	k = 1;
	for (i = 1; i <= n; i++) {
		if (!cn[i]) {
			dfs2(i);
			k++;
		}
	}
	
	for (i = 1; i <= n; i++) {
		for (auto nextv : graph[i]) {
			if (cn[i] != cn[nextv]) {
				res[cn[i]].insert(cn[nextv]);
				res[cn[nextv]].insert(cn[i]);
			}
		}
	}
	
	int ans = 0;
	for (int i = 1; i < k; i++) {
		if ((int) res[i].size() <= 1) {
			ans++;
		}
	}
	
	cout << ans << endl;
	return 0;
}

