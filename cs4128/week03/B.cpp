#include <bits/stdc++.h>
#define MAX_SIZE 311
using namespace std;

vector<int> a[MAX_SIZE];
int d[MAX_SIZE], visited[MAX_SIZE], cost[MAX_SIZE];
int n;

bool dfs1(int v) {
	if (v == n) return true;
	visited[v] = 1;
	for (auto nextv : a[v]) {
		if (!visited[nextv]) {
			if (dfs1(nextv)) return true;
		}
	}
	return false;
}

bool dfs(int v, int pw) {
	if (v == n) return true;
	d[v] = pw + cost[v];
	for (auto nextv : a[v]) {
		if (d[v] + cost[nextv] > 0) {
			if (!d[nextv]) {
				if (dfs(nextv, d[v])) return true;
			} else if (d[v] + cost[nextv] > d[nextv]) {
				memset(visited, 0, sizeof(visited));
				if (dfs1(nextv)) return true;
			}
		}
	}
	
	return false;
}

int main(int argc, char *argv[]) {
	while (scanf("%d", &n) != EOF) {
		memset(visited, 0, sizeof(visited));
		memset(d, 0, sizeof(d));
		memset(cost, 0, sizeof(cost));
		for (int i = 0; i < MAX_SIZE; i++) {
			a[i] = vector<int>();
		}
		if (n == -1) break;
		for (int i = 1; i <= n; i++) {
			int m;
			scanf("%d", &cost[i]);
			scanf("%d", &m);
			for (int j = 1; j <= m; j++) {
				int v;
				scanf("%d", &v);
				a[i].push_back(v);
			}
		}
		
		if (dfs(1, 100)) {
			cout << "winnable" << endl;
		} else {
			cout << "hopeless" << endl;
		}
	}
	return 0;
}
