#include <bits/stdc++.h>

using namespace std;

vector<vector<int> > ans;

void dfs_1(vector<vector<int> > &graph, int v, stack<int> &s, vector<int> &visited);
void dfs_2(vector<vector<int> > &graph, int v, vector<int> &visited);

int main(int argc, char *argv[]) {
	int n, m, v1, v2;
	vector<vector<int> > graph;
	vector<vector<int> > rgraph;
	vector<int> visited;
	cin >> n >> m;
	graph = vector<vector<int> >(n, vector<int>());
	rgraph = vector<vector<int> >(n, vector<int>());
	visited = vector<int>(n, 0);
	while (m > 0) {
		cin >> v1 >> v2;
		graph[v1].push_back(v2);
		rgraph[v2].push_back(v1);
		m--;
	}
	
	stack<int> s = stack<int>();
	
	int i;
	for (i = 0; i < n; i++) {
		if (!visited[i]) {
			dfs_1(graph, i, s, visited);
		}
	}
	
	visited = vector<int>(n, 0);
	while (!s.empty()) {
		int v = s.top();
		s.pop();
		if (!visited[v]) {
			ans.push_back(vector<int>());
			dfs_2(rgraph, v, visited);
		}
	}
	
	i = 1;
	for (auto vc : ans) {
		cout << i << ": [";
		for (auto num : vc) {
			cout << " " << num;
		}
		cout << "]" << endl;
		i++;
	}
	return 0;
}

void dfs_1(vector<vector<int> > &graph, int v, stack<int> &s, vector<int> &visited) {
	if (visited[v]) return;
	visited[v] = 1;
	for (auto nextv : graph[v]) {
		if (!visited[nextv]) {
			dfs_1(graph, nextv, s, visited);
		}
	}
	s.push(v);
}

void dfs_2(vector<vector<int> > &graph, int v, vector<int> &visited) {
	if (visited[v]) return;
	visited[v] = 1;
	ans[ans.size() - 1].push_back(v);
	for (auto nextv : graph[v]) {
		if (!visited[nextv]) {
			dfs_2(graph, nextv, visited);
		}
	}
}
