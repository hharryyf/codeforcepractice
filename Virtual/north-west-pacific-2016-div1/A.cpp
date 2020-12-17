#include <bits/stdc++.h>
#define MAX_SIZE 200011
typedef long long ll;
using namespace std;

int dp[55][28];
char st[55];
char pt[28];

int main() {
	int i, j;
	scanf("%s", st + 1);
	int N = strlen(st + 1);
	int M = 26;
	for (i = 1; i <= M; ++i) {
		pt[i] = 'a' + i - 1;
	}

	for (i = 1; i <= N; ++i) {
		for (j = 1; j <= M; ++j) {
			if (st[i] == pt[j]) {
				dp[i][j] = max(dp[i][j], dp[i-1][j-1] + 1);
			}

			dp[i][j] = max(dp[i][j], dp[i-1][j]);
			dp[i][j] = max(dp[i][j], dp[i][j-1]);
		}
	}

	printf("%d\n", 26 - dp[N][M]);
	return 0;
}
