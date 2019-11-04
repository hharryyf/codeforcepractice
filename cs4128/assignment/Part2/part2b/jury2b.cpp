#include <bits/stdc++.h>
#define MAX_SIZE 2048

using namespace std;

multiset<int> g[MAX_SIZE];

pair<int, int> qr[MAX_SIZE];

int n, q;

unordered_set<int> visited;

void dfs(int v) {
	visited.insert(v);
	for (auto p : g[v]) {
		if (visited.find(p) == visited.end()) {
			dfs(p);
		}
	}
}

int connected(int v1, int v2) {
	visited = unordered_set<int>();
	dfs(v1);
	return visited.find(v2) != visited.end();
}

int main() {
	scanf("%d%d", &n, &q);
	int i;
	for (i = 1; i <= q; i++) {
		int op, v1, v2;
		scanf("%d", &op);
		if (op == 1) {
			scanf("%d%d", &v1, &v2);
			g[v1].insert(v2);
			g[v2].insert(v1);
			qr[i].first = v1;
			qr[i].second = v2;
		} else if (op == 2) {
			int v;
			scanf("%d", &v);
			v1 = qr[v].first, v2 = qr[v].second;
			g[v1].erase(g[v1].find(v2));
			g[v2].erase(g[v2].find(v1));
		} else {
			scanf("%d%d", &v1, &v2);
			cout << connected(v1, v2) << endl;
		}
	}
	return 0;
}
