#include <bits/stdc++.h>
#define MAX_SIZE 600111
#define INF 12000011
using namespace std;

int f[MAX_SIZE];
int wt[MAX_SIZE];
int sz[MAX_SIZE];
int n, k;
// g[i].size() = 2 refers to (a, b) must seperated at step i
// g[i].size() = 1 refers to a must be selected
vector<int> g[MAX_SIZE];
char s[MAX_SIZE];

int find(int x) {
	if (f[x] == x) return x;
	return f[x] = find(f[x]);
}

void unionset(int x, int y) {
	int a = find(x), b = find(y);
	if (a == b) return;
	if (sz[a] < sz[b]) {
		f[a] = b;
		sz[b] += sz[a];
		wt[b] += wt[a];
	} else {
		f[b] = a;
		sz[a] += sz[b];
		wt[a] += wt[b];
	}
}
// the weight of the the component x
// it should be the min of the friend set x and the enemy set x
int weight(int x) {
	return min(wt[find(x)], wt[find(x + k)]);
}

int main() {
	int ans = 0;
	int i;
	scanf("%d%d", &n, &k);
	scanf("%s", s + 1);
	for (i = 1; i <= k; ++i) {
		f[i] = i;
		f[i + k] = i + k;
		sz[i] = 1;
		sz[i + k] = 1;
		wt[i + k] = 1;
	}
	
	wt[2 * k + 1] = INF;
	sz[2 * k + 1] = 1;
	f[2 * k + 1] = 2 * k + 1;
	
	for (i = 1; i <= k; ++i) {
		int x;
		scanf("%d", &x);
		while (x > 0) {
			int v;
			scanf("%d", &v);
			g[v].push_back(i);
			--x;
		}
	}
	
	for (i = 1; i <= n; ++i) {
		int c = g[i].size();
		if (c == 1) {
			// cout << i << ": " << g[i][0] << endl;
			if (s[i] == '0') {
				// s[i] = 0 means g[i][0] must belongs to the 1 set
				// it is when we calculate weight(g[i][0]) 
				// the wt[g[i][0]+k] must be calculated
				ans -= weight(g[i][0]);
				unionset(g[i][0], 2 * k + 1);
				ans += weight(g[i][0]);
			} else {
				ans -= weight(g[i][0]);
				unionset(g[i][0] + k, 2 * k + 1);
				ans += weight(g[i][0]);
			}
		} else if (c == 2) {
			// cout << i << ": " << g[i][0] << " " << g[i][1] << endl;
			// if s[i] = 0 means for g[i][0] and g[i][1] we should
			// only switch 1 of them, in other words g[i][0] and g[i][1]
			// should be in different part of the bipartite graph
			if (s[i] == '0') {
				if (find(g[i][0]) != find(g[i][1] + k)) {
					ans -= weight(g[i][0]);
					ans -= weight(g[i][1]);
					unionset(g[i][0], g[i][1] + k);
					unionset(g[i][1], g[i][0] + k);
					ans += weight(g[i][0]);
				}
			} else {
				if (find(g[i][0]) != find(g[i][1])) {
					ans -= weight(g[i][0]);
					ans -= weight(g[i][1]);
					unionset(g[i][0], g[i][1]);
					unionset(g[i][0] + k, g[i][1] + k);
					ans += weight(g[i][0]);
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}