#include <bits/stdc++.h>
#define MAX_LEN 311

typedef long long ll;

using namespace std;

const ll INF = -10000000000;
ll dp[MAX_LEN][MAX_LEN][MAX_LEN];
ll arr[MAX_LEN][MAX_LEN];
int n;

ll points(int x, int y, int z);

int main(int argc, char *argv[]) {
	int i, j, k, w;
	cin >> n;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			cin >> arr[i][j];
		}
	}
	
	/*
		let dp[i][j][k] refers to the maximum number of points that can be
		gained if the first person is at (i, j), and the second person is at
		(k, i + j - k). which 1 <= i + j - k <= n
		if i + j - k is in an invalid range dp[i][j][k] = INF
		if i > 1 and w > 1
			dp[i][j][k] = dp[i-1][j][k] + point(i, j, k)
		if i > 1 and k > 1
			dp[i][j][k] = max(dp[i-1][j][k-1] + point(i, j, k), dp[i][j][k])
		...
	*/
	
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			for (k = 1; k <= n; k++) {
				if (i == 1 && j == 1 && k == 1) {
					dp[i][j][k] = arr[1][1];
					continue;
				}
				dp[i][j][k] = INF;
				w = i + j - k;
				if (w > n || w < 1) {
					continue;
				}
				
				if (i > 1 && w > 1) {
					dp[i][j][k] = dp[i-1][j][k] + points(i, j, k);
				}
				
				if (i > 1 && k > 1) {
					dp[i][j][k] = max(dp[i-1][j][k-1] + points(i, j, k), dp[i][j][k]);
				}
				
				if (j > 1 && k > 1) {
					dp[i][j][k] = max(dp[i][j-1][k-1] + points(i, j, k), dp[i][j][k]);
				}
				
				if (j > 1 && w > 1) {
					dp[i][j][k] = max(dp[i][j-1][k] + points(i, j, k), dp[i][j][k]);
				}
			}
		}
	}
	cout << dp[n][n][n] << endl;
	return 0;
}

ll points(int x, int y, int z) {
	if (x + y - z > n || x + y - z < 1) return INF;
	if (x == z) {
		return arr[x][y];
	} 
	return arr[x][y] + arr[z][x + y - z];
}
