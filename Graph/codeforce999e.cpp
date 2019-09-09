#include <bits/stdc++.h>
#define MAX_SIZE 5011

using namespace std;

int n, m, s;

vector<int> graph[MAX_SIZE];

vector<int> rgraph[MAX_SIZE];

stack<int> st;
bool visited[MAX_SIZE];

int component[MAX_SIZE];

int curr = 0;

void dfs_1(int v);
void dfs_2(int v);

unordered_set<int> fgraph[MAX_SIZE];
unordered_set<int> rfgraph[MAX_SIZE];

void dfs_3(int v);

int main(int argc, char *argv[]) {
	scanf("%d%d%d", &n, &m, &s);
	int i, cnt = 0;
	for (i = 0 ; i < m; i++) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		graph[v1].push_back(v2);
		rgraph[v2].push_back(v1);
	}
	
	memset(visited, false, sizeof(visited));
	
	for (i = 1; i <= n; i++) {
		if (!visited[i]) {
			dfs_1(i);
		}
	}
	
	memset(visited, false, sizeof(visited));
	
	while (!st.empty()) {
		int v = st.top();
		st.pop();
		if (!visited[v]) {
			cnt++;
			curr++;
			dfs_2(v);
		}
	}
	
	memset(visited, false, sizeof(visited));
	
	
	for (i = 1; i <= n; i++) {
		// cout << "vertex " << i << " belongs to component " << component[i] << endl;
		for (auto nextv : graph[i]) {
			// cout << "establish edge between " << component[i] << " " << component[nextv] << endl;
			if (component[nextv] != component[i]) {
				fgraph[component[i]].insert(component[nextv]);
				rfgraph[component[nextv]].insert(component[i]);
			}
		} 
	}
	
	dfs_3(component[s]);
	
	cnt = 0;
	for (int i = 1; i <= curr; i++) {
		if (!visited[i] && rfgraph[i].size() == 0) {
			cnt++;
			dfs_3(i);
		}
	}
	
	cout << cnt << endl;
	return 0;
}

void dfs_3(int v) {
	if (visited[v]) return;
	visited[v] = true;
	for (auto nextv : fgraph[v]) {
		if (!visited[nextv]) dfs_3(nextv);
	}
}

void dfs_1(int v) {
	if (visited[v]) return;
	visited[v] = true;
	for (auto nextv : graph[v]) {
		if (!visited[nextv]) {
			dfs_1(nextv);
		}
	}
	
	st.push(v);
}

void dfs_2(int v) {
	if (visited[v]) return;
	visited[v] = true;
	component[v] = curr;
	for (auto nextv : rgraph[v]) {
		if (!visited[nextv]) dfs_2(nextv);
	}
}
