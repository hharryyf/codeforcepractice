#include <bits/stdc++.h>

using namespace std;

#define MAX_SIZE 300111

// graph in adjacency list format and corresponding edge id
vector<pair<int, int> > graph[MAX_SIZE];

// q that records (node, parent)
queue<pair<int, int> > q;

// the node that has been visited
int visited[MAX_SIZE];

// the edge id that should be removed
int flag[MAX_SIZE];

int main(int argc, char *argv[]) {
	int i, n, k, d, u, v;
	cin >> n >> k >> d;
	for (i = 0 ; i < k; i++) {
		cin >> v;
		q.push(pair<int, int>(v, 0));
	}
	
	for (i = 0 ; i < n - 1; i++) {
		cin >> u >> v;
		graph[u].push_back(pair<int, int>(v, i + 1));
		graph[v].push_back(pair<int, int>(u, i + 1));
	}
	
	while (!q.empty()) {
		pair<int, int> p = q.front();
		q.pop();
		if (visited[p.first]) {
			continue;
		}
		
		visited[p.first] = 1;
		
		for (i = 0 ; i < (int) graph[p.first].size(); i++) {
			if (graph[p.first][i].first != p.second) {
				if (visited[graph[p.first][i].first]) {
					flag[graph[p.first][i].second] = 1;
				} else {
					q.push(pair<int, int>(graph[p.first][i].first, p.first));
				}
			}
		}
	}
	
	int cnt = 0;
	for (i = 0 ; i < n; i++) {
		if (flag[i] != 0) {
			cnt++;
		}
	}
	
	cout << cnt << endl;
	
	for (i = 0 ; i < n; i++) {
		if (flag[i] != 0) {
			cout << i << " ";
		}
	}
	
	cout << endl;
	return 0;
}
