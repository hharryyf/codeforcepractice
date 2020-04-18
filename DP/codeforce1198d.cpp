#include <bits/stdc++.h>
#define MAX_SIZE 54
using namespace std;

int dp[MAX_SIZE][MAX_SIZE][MAX_SIZE][MAX_SIZE];
char g[MAX_SIZE][MAX_SIZE];
int pre[MAX_SIZE][MAX_SIZE];
int n;

int query(int x1, int y1, int x2, int y2) {
	if (x1 > x2 || y1 > y2) return 0;
	return pre[x1-1][y1-1] + pre[x2][y2] - pre[x1-1][y2] - pre[x2][y1-1];
}

int dfs(int x1, int y1, int x2, int y2) {
	if (x1 > x2 || y1 > y2) return 0;
	if (query(x1, y1, x2, y2) == 0) return 0;
	if (dp[x1][y1][x2][y2] != -1) return dp[x1][y1][x2][y2];
	int ret = max(x2 - x1 + 1, y2 - y1 + 1);
	int i;
	for (i = x1; i < x2; ++i) {
		ret = min(dfs(x1, y1, i, y2) + dfs(i + 1, y1, x2, y2), ret);
	}
	
	for (i = y1; i < y2; ++i) {
		ret = min(dfs(x1, y1, x2, i) + dfs(x1, i + 1, x2, y2), ret);
	}
	return dp[x1][y1][x2][y2] = ret;
}

int main() {
	int i, j;
	scanf("%d", &n);
	memset(dp, -1, sizeof(dp));
	for (i = 1; i <= n; ++i) {
		scanf("%s", g[i] + 1);
		for (j = 1; j <= n; ++j) {
			pre[i][j] = pre[i-1][j] + pre[i][j-1] - pre[i-1][j-1];
			if (g[i][j] == '#') {
				pre[i][j] += 1;
			}
		}
	}
	
	printf("%d\n", dfs(1, 1, n, n));
	return 0;
}