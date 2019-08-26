#include <bits/stdc++.h>
#define MAX_SIZE 200101

using namespace std;

int c[MAX_SIZE];
vector<int> graph[MAX_SIZE];
vector<int> minigraph[MAX_SIZE];

int parent[MAX_SIZE];

void dfs(int v, int prev);

int diameter(int v, int prev);

int d = 0;

int main(int argc, char *argv[]) {
	int n, i;
	scanf("%d", &n);
	
	for (i = 1; i <= n; i++) {
		scanf("%d", &c[i]);
	}
	
	for (i = 1; i < n; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	
	
	parent[1] = 1;
	dfs(1, 1);
	#ifdef DEBUG
	for (i = 1; i <= n; i++) {
		cout << parent[i] << " ";
	}
	cout << endl;
	for (i = 1; i <= n; i++) {
		cout << i << ": ";
		for (auto v : minigraph[i]) {
			cout << v << " ";
		}
		cout << endl;
	}
	#endif
	
	diameter(1, 1);
	// cout << d << endl;
	cout << d / 2 << endl;
	 
	return 0;
}

int diameter(int v, int prev) {
	int height1 = 0, height2 = 0;
	
	for (auto nextnode : minigraph[v]) {
		if (nextnode != prev) {
			int t = diameter(nextnode, v);
			if (t >= height1) {
				height2 = height1;
				height1 = t;
			}
			
			if (height1 > t && t >= height2) {
				height2 = t;
			}
		}
	}
	
	 
	d = max(height1 + height2 + 1, d);
	// cout << v << " " << height1 << " " << height2 << " " << d << endl;
	return height1 + 1;
}

void dfs(int v, int prev) {
	for (auto nextnode : graph[v]) {
		if (nextnode != prev) {
			if (c[nextnode] != c[v]) {
				parent[nextnode] = nextnode;
				minigraph[nextnode].push_back(parent[v]);
				minigraph[parent[v]].push_back(nextnode);
			} else {
				parent[nextnode] = parent[v];
			}
			
			dfs(nextnode, v);
		}
	}
}
