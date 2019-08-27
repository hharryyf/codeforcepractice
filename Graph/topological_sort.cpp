#include <bits/stdc++.h>
#define WHITE 0
#define GREY 1
#define BLACK 2

using namespace std;

vector<int> c;
bool fail = false;
list<int> ans;

void dfs(vector<vector<int> > &graph, int v);

int main(int argc, char *argv[]) {
	int n, m;
	vector<vector<int> > graph;
	cin >> n >> m;
	graph = vector<vector<int> >(n, vector<int>());
	c = vector<int>(n, WHITE);
	ans = list<int>();
	while (m > 0) {
		int v, u;
		cin >> v >> u;
		graph[v].push_back(u);
		m--;
	}
	
	for (int i = 0 ; i < n; i++) {
		if (c[i] == WHITE) {
			dfs(graph, i);
		}
	}
	if (fail) {
		cout << "no solution" << endl;
	} else {
		for (auto num : ans) {
			cout << num << " ";
		}
		cout << endl;
	}
	return 0;
}

void dfs(vector<vector<int> > &graph, int v) {
	if (c[v] != WHITE) return;
	c[v] = GREY;
	for (auto nextv : graph[v]) {
		if (c[nextv] == GREY) {
			fail = true;
		}
		if (c[nextv] == WHITE) {
			dfs(graph, nextv);
		}
	}
	c[v] = BLACK;
	ans.push_front(v);
}
