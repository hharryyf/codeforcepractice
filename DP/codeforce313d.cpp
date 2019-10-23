#include <bits/stdc++.h>
#define MAX_SIZE 311
#define INF 3010000000000ll
typedef long long ll;
using namespace std;

ll dp[MAX_SIZE][MAX_SIZE];

/* cost[i][j] refers to the minimum cost of covering segment [i, j] */
ll cost[MAX_SIZE][MAX_SIZE];

int main() {
	int n, m, k;
	int i, j, p;
	cin >> n >> m >> p;
	for (i = 0; i <= n; i++) {
		for (j = 0; j <= n; j++) {
			if (j != 0) {
				dp[i][j] = INF;
			}
			cost[i][j] = INF;
		}
	}
	
	/* this is where the IQ humiliating part took place */
	while (m > 0) {
		int x, y;
		ll c;
		cin >> x >> y >> c;
		for (i = x; i <= y; i++) {
			/* a greedy approach */
			cost[x][i] = min(cost[x][i], c);
		}
		m--;
	}
	
	for (i = 1 ; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			dp[i][j] = dp[i-1][j];
			for (k = 1; k <= i; k++) {
				dp[i][j] = min(dp[i][j], dp[i-k][j-k] + cost[i-k+1][i]);
			}
		}
	}
	cout << (dp[n][p] < INF ? dp[n][p] : -1) << endl;
	return 0;
}
