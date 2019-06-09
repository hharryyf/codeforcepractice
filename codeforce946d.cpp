#include <bits/stdc++.h>
#define MAX_LEN 512
#define INF 260000
using namespace std;

// the minimum number of hours in school when there's i days amd skips k courses
int dp[MAX_LEN][MAX_LEN];
// the prefix sum of the ith day
int prefix[MAX_LEN][MAX_LEN];
// the minimum length of working hour of the ith day that contains j courses
int workload[MAX_LEN][MAX_LEN];
// string input
char str[MAX_LEN];

int main(int argc, char *argv[]) {
	int n, m, k, i, j, p;
	cin >> n >> m >> k;
	for (i = 0 ; i < n; i++) {
		scanf("%s", str);
		for (j = 0; j < m; j++) {
			if (j == 0) {
				prefix[i][j] = str[j] - '0';
			} else {
				prefix[i][j] = prefix[i][j-1] + (str[j] - '0');
			}
		}
	}
	
	for (i = 0 ; i < n; i++) {
		for (j = 0 ; j <= max(m, k); j++) {
			dp[i][j] = INF;
			if (j == 0) {
				workload[i][j] = 0; 
			} else {
				workload[i][j] = INF;
			}
		}
	}
	
	for (i = 0 ; i < n; i++) {
		for (j = 0; j < m; j++) {
			for (p = j; p < m; p++) {
				int current = prefix[i][p] - (j > 0 ? prefix[i][j-1] : 0);
				workload[i][current] = min(workload[i][current], p - j + 1); 
			}
		}
	}
	
	/* 
	   we enter the dp part finally, define the dp[i][j] as the minimum number of
	   hours that must be in school when only considering the ith day and has skiped
	   j courses 
	   dp[i][j] = min(dp[i-1][p] + workload[i][prefix[i][m-1] - j + p])
	*/
	
	for (i = 0; i < n; i++) {
		for (j = 0; j <= k; j++) {
			for (p = 0; p <= j; p++) {
				if (prefix[i][m-1] - j + p >= 0) {
					if (i == 0) {
						dp[i][j] = min(dp[i][j], workload[i][prefix[i][m-1] - j + p]);
					} else {
						dp[i][j] = min(dp[i][j], dp[i-1][p] + workload[i][prefix[i][m-1] - j + p]);
					}
				}
			}
			// cout << "dp[" << i << " ," << j << "]= " << dp[i][j] << endl;
		}
	}
	
	int ans = INF;
	for (i = 0 ; i <= k; i++) {
		ans = min(ans, dp[n-1][i]);
	}
	cout << ans << endl;
	return 0;
}
