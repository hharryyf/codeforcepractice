#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 1000111
typedef long long ll;
using namespace std;

int parent[MAX_SIZE][22];
// wt=1 means selected, wt=0 means not
int wt[MAX_SIZE], dep[MAX_SIZE];
vector<int> g[MAX_SIZE];
int select, n;

void dfs(int v, int pre) {
	 int i;
	 dep[v] = 1 + dep[pre];
	 parent[v][0] = pre;
	 for (i = 1; i < 21; ++i) parent[v][i] = parent[parent[v][i-1]][i-1];
	 for (auto nv : g[v]) {
	 	 if (nv != pre) {
		 	dfs(nv, v);		 	 
         }
	 }
}

void update(int v) {
	 while (v != 0 && wt[v] == 0) {
	 	   select--;
           wt[v] = 1;
	 	   v = parent[v][0];
	 }
}

int query(int v) {
	int u = v;
	if (wt[v]) return 0;
	int i;
	for (i = 20; i >= 0; i--) {
		if (parent[v][i] && !wt[parent[v][i]]) {
		   v = parent[v][i];
		}
	}
	return dep[u] - dep[v] + 1;
}

int main() {
	int i, k;
	scanf("%d%d", &n, &k);
	for (i = 1; i < n; i++) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		g[v1].push_back(v2);
		g[v2].push_back(v1);
	}
	
	dfs(n, 0);
	
	select = n - k;
	
	for (i = n; i >= 1; i--) {
		if (wt[i]) continue;
		if (query(i) <= select) {
		   update(i);
		}
	}
	
	for (i = 1; i <= n; i++) {
		if (!wt[i]) {
		   printf("%d ", i);
		}
	}
	printf("\n");
	return 0;
}

