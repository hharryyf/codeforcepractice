#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

// we find all the biconnected component using tarjan's bridge finding algorithm
// and if the resulting component is more than 1, there's no solution
// otherwise, the edges are ordered as the dfs goes on

int low[MAX_SIZE];
int visited[MAX_SIZE];
vector<int> graph[MAX_SIZE];
set<pair<int, int> > ans;
bool isvalid;
int k = 1;

void dfs(int v, int prev) {
	visited[v] = k++;
	low[v] = visited[v];
	for (auto nextv : graph[v]) {
		if (nextv != prev) {
			if (!visited[nextv]) {
				ans.insert(make_pair(v, nextv));
				dfs(nextv, v);
				low[v] = min(low[v], low[nextv]);
				if (low[nextv] > visited[v]) {
					isvalid = false;
				}
			} else {
				if (ans.find(make_pair(v, nextv)) == ans.end() 
					&& ans.find(make_pair(nextv, v)) == ans.end()) {
					ans.insert(make_pair(v, nextv));
				}
				low[v] = min(low[v], visited[nextv]);
			}
		}
	}
}

int main() {
	int n, m;
	int i;
	scanf("%d%d", &n, &m);
	isvalid = true;
	for (i = 0 ; i < m; i++) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		graph[v1].push_back(v2);
		graph[v2].push_back(v1);
	}
	
	dfs(1, -1);
	
	if (!isvalid) {
		printf("0\n");
	} else {
		for (auto p : ans) {
			printf("%d %d\n", p.first, p.second);
		}
	}
	return 0;
}
