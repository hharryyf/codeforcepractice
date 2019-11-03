#include <bits/stdc++.h>
#define MAX_SIZE 1025

using namespace std;

stack<pair<int, int> > edg;

unordered_set<int> visited;

multiset<int> g[MAX_SIZE];

void dfs(int v) {
	visited.insert(v);
	for (auto nv : g[v]) {
		if (visited.find(nv) == visited.end()) {
			dfs(nv);
		}
	}
}

void disconnect() {
	if (!edg.empty()) {
		int v1 = edg.top().first, v2 = edg.top().second;
		g[v1].erase(g[v1].find(v2));
		g[v2].erase(g[v2].find(v1));
		edg.pop();
	}
}

void addedge(int v1, int v2) {
	g[v1].insert(v2);
	g[v2].insert(v1);
	edg.push(make_pair(v1, v2));
}

int sameset(int v1, int v2) {
	visited = unordered_set<int>();
	dfs(v1);
	return visited.find(v2) != visited.end();
}

int main() {
	int n;
	scanf("%d", &n);
	int q, i;
	scanf("%d", &q);
	for (i = 0 ; i < q; i++) {
		int op;
		scanf("%d", &op);
		if (op == 1) {
			int a, b;
			scanf("%d%d", &a, &b);
			addedge(a, b);
		} else if (op == 2) {
			disconnect();
		} else {
			int a, b;
			scanf("%d%d", &a, &b);
			printf("%d\n", sameset(a, b));
		}
	}
	return 0;
}
