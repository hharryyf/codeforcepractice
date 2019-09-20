#include <bits/stdc++.h>
using namespace std;

int timestamp = 0;

void tarjan(vector<vector<int> > &graph);

int main(int argc, char *argv[]) {
	int n, m;
	cin >> n >> m;
	vector<vector<int> > graph = vector<vector<int> >(n, vector<int>());
	while (m > 0) {
		int v, u;
		cin >> v >> u;
		graph[v].push_back(u);
		m--;
	} 	
	tarjan(graph);
	return 0;
}

void dfs(vector<vector<int> > &graph, int v, stack<int> &s, vector<int> &visited, 
		 vector<int> &instack, vector<int> &low) {
 	low[v] = visited[v] = ++timestamp;
	s.push(v);
	instack[v] = 1;
	for (auto nextv : graph[v]) {
		// tree edge
		if (visited[nextv] == -1) {
			dfs(graph, nextv, s, visited, instack, low);
			low[v] = min(low[v], low[nextv]);
		} else if (instack[nextv] == 1) {
			// back edge
			low[v] = min(low[v], visited[nextv]);
		}
	}
	
	if (low[v] == visited[v]) {
		while (s.top() != v) {
			cout << s.top() << " ";
			instack[s.top()] = 0;
			s.pop();
		}
		
		cout << s.top() << endl;
		instack[s.top()] = 0;
		s.pop();
	}
}

void tarjan(vector<vector<int> > &graph) {
	stack<int> s = stack<int>();
	vector<int> low = vector<int>(graph.size(), -1);
	vector<int> visited = vector<int>(graph.size(), -1);
	vector<int> instack = vector<int>(graph.size(), 0);
	for (int i = 0 ; i < (int) graph.size(); i++) {
		if (visited[i] == -1) {	
			dfs(graph, i, s, visited, instack, low);
		}
	}
}




