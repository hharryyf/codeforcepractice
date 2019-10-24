#include <bits/stdc++.h>

#define MAX_SIZE 111

using namespace std;

double dp[MAX_SIZE][MAX_SIZE][MAX_SIZE];

int main() {
	int r, s, p, i, j, k;
	scanf("%d%d%d", &r, &s, &p);
	dp[r][s][p] = 1.00;
	for (i = r; i >= 0; i--) {
		for (j = s; j >= 0; j--) {
			for (k = p; k >= 0; k--) {
				int num = i * j + i * k + j * k;
				if (num != 0) {
					if (k) {
						dp[i][j][k-1] += (dp[i][j][k] * j * k) / (1.0 * num);
					}
				
					if (i) {
						dp[i-1][j][k] += (dp[i][j][k] * i * k) / (1.0 * num);
					}
				
					if (j) {
						dp[i][j-1][k] += (dp[i][j][k] * i * j) / (1.0 * num);
					}
				}
				// printf("dp[%d][%d][%d] = %lf\n", i, j, k, dp[i][j][k]);
			}
		}
	}
	
	double rr = 0.0, rs = 0.0, rp = 0.0;
	for (i = 1; i <= r; i++) {
		rr = rr + dp[i][0][0];	
	}
	
	for (i = 1; i <= s; i++) {
		rs = rs + dp[0][i][0];
	}
	
	for (i = 1; i <= p; i++) {
		rp = rp + dp[0][0][i];
	}
	
	printf("%.12lf %.12lf %.12lf\n", rr, rs, rp);
	return 0;
}
