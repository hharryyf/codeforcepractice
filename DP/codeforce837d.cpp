#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 211
typedef long long ll;
using namespace std;

int a[MAX_SIZE][2];
ll num[MAX_SIZE];
int dp[2][5402][201];

void fac(int idx) {
	 while (num[idx] > 0 && num[idx] % 2 == 0) {
	 	   a[idx][0]++, num[idx] /= 2;
	 }
	 
	 while (num[idx] > 0 && num[idx] % 5 == 0) {
	 	   a[idx][1]++, num[idx] /= 5;
	 }
}

int main() {
	int n, i, j, k, l;
	scanf("%d%d", &n, &k);
	for (i = 1; i <= n; i++) scanf("%lld", &num[i]);
	for (i = 1; i <= n; i++) fac(i);
	
	for (i = 0 ; i < 5402; ++i) {
		for (j = 0 ; j < 201; ++j) {
			dp[0][i][j] = -10000000;
			dp[1][i][j] = -10000000;
		}
	}
	dp[0][0][0] = 0;
	
	int ans = 0;
	for (i = 1; i <= n; ++i) {
		for (j = 0; j < 5402; ++j) {
			for (l = 0 ; l <= k; ++l) {
				if (j >= a[i][1] && l >= 1) {
				   dp[i % 2][j][l] = max(dp[(i-1) % 2][j-a[i][1]][l-1] + a[i][0],
				                         dp[(i-1) % 2][j][l]);	 
				} else {
				   dp[i % 2][j][l] = dp[(i-1) % 2][j][l];
				}
				if (l == k) {
				   ans = max(ans, min(j, dp[i % 2][j][l]));
				}
			}	
		}
	}
	
	printf("%d\n", ans);
	return 0;
}

