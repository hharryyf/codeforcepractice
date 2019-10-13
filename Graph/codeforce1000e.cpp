#include <bits/stdc++.h>
#define MAX_SIZE 300011

using namespace std;

int low[MAX_SIZE];
int instack[MAX_SIZE];
int visited[MAX_SIZE];
vector<int> g[MAX_SIZE];
unordered_set<int> t[MAX_SIZE];
stack<int> s;
int n;
int k = 1;
int id = 1;
int cmpid[MAX_SIZE];
int dpt = 0;
int depth[MAX_SIZE];

void dfs(int v, int pre) {
	int t1 = 0, t2 = 0;
	
	for (auto nv : t[v]) {
		if (nv != pre) {
			dfs(nv, v);
			depth[v] = max(depth[v], 1 + depth[nv]);
			// cout << v << "----" << depth[v] << endl;
			if (1 + depth[nv] >= t1) {	
				t2 = max(t1, t2);
				t1 = depth[nv] + 1;
			} else {
				t2 = max(t2, depth[nv] + 1);
			}
		}
	}
	
	dpt = max(dpt, t1 + t2);
	// cout << v << " " << depth[v] << " " << t1 << " " << t2 << endl;
}

void tarjan(int v, int pre) {
	instack[v] = 1;
	s.push(v);
	visited[v] = low[v] = k++;
	for (auto nv : g[v]) {
		if (nv != pre) {
			if (!visited[nv]) {
				tarjan(nv, v);
				low[v] = min(low[v], low[nv]);
			} else if (instack[nv]) {
				low[v] = min(low[v], visited[nv]);
			}
		}
	}
	
	if (visited[v] == low[v]) {
		while (s.top() != v) {
			cmpid[s.top()] = id;
			instack[s.top()] = 0;
			s.pop();
		}
		
		cmpid[s.top()] = id;
		instack[s.top()] = 0;
		s.pop();
		id++;
	}
}

int main() {
	int m, i;
	scanf("%d%d", &n, &m);
	for (i = 0 ; i < m; i++) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		g[v1].push_back(v2);
		g[v2].push_back(v1);
	}	
	
	tarjan(1, -1);
	
	
	for (i = 1; i <= n; i++) {
		for (auto v : g[i]) {
			if (cmpid[v] != cmpid[i]) {
				t[cmpid[v]].insert(cmpid[i]);
				t[cmpid[i]].insert(cmpid[v]);
			}
		}
	}
	
	dfs(1, -1);
	
	printf("%d\n", dpt);
	return 0;
}
