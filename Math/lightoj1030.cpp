#include <cstdio>
#include <iostream>
#include <vector>
#include <vector>
#define MAX_SIZE 111
using namespace std;

int value[MAX_SIZE];
double dp[MAX_SIZE];
int main() {
	int T, n, t, i, j;
	scanf("%d", &T);
	for (t = 1; t <= T; ++t) {
		scanf("%d", &n);
		for (i = 1; i <= n; ++i) {
			scanf("%d", &value[i]);
			dp[i] = 0.0;
		}
		
		for (i = n; i >= 1; --i) {
			int total = min(6, n - i);
			dp[i] = 1.0 * value[i];
			for (j = 1; j <= total; ++j) {
				dp[i] = dp[i] + 1.0 / (total * 1.0) * dp[j+i];
			}
		}
		
		printf("Case %d: %lf\n", t, dp[1]);
	}
	return 0;
}