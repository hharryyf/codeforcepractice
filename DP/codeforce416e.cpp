#include <bits/stdc++.h>
#define MAX_SIZE 511
using namespace std;

const int inf = 650000000;

int g[MAX_SIZE][MAX_SIZE];
int dist[MAX_SIZE][MAX_SIZE];
int dp[MAX_SIZE][MAX_SIZE];
int ans[MAX_SIZE][MAX_SIZE];

int main() {
	int i, j, k, n;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) {
		for (j = 1; j <= n; ++j) {
			g[i][j] = inf;
			if (i != j) {
				dist[i][j] = inf;
			}
		}
	} 
	
	int m;
	scanf("%d", &m);
	for (i = 0 ; i < m; ++i) {
		int v1, v2, w;
		scanf("%d%d%d", &v1, &v2, &w);
		g[v1][v2] = g[v2][v1] = w;
		dist[v1][v2] = dist[v2][v1] = w;
	}
	
	for (k = 1; k <= n; ++k) {
		for (i = 1; i <= n; ++i) {
			for (j = 1; j <= n; ++j) {
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}
	
	for (i = 1; i <= n; ++i) {
		for (j = 1; j <= n; ++j) {
			for (k = 1; k <= n; ++k) {
				if (g[i][k] < inf && dist[i][j] == g[i][k] + dist[k][j]) {
					dp[i][j] += 1;
				} 
			}
		}
	}
	
	for (k = 1; k <= n; ++k) {
		for (i = 1; i <= n; ++i) {
			for (j = 1; j <= n; ++j) {
				if (dist[i][j] == dist[i][k] + dist[k][j]) {
					ans[i][j] += dp[k][j];
				} 
			}
		}
	}
	
	for (i = 1; i <= n; ++i) {
		for (j = i + 1; j <= n; ++j) {
			if (dist[i][j] < inf) {
				printf("%d ", ans[i][j]);
			} else {
				printf("0 ");
			}
		}
	}
	printf("\n");
	return 0;
}

/*

5 7
1 5 1
1 4 2
5 4 1
5 2 2
4 2 1
3 4 3
2 1 3

*/