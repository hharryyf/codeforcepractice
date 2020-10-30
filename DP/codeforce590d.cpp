#include <bits/stdc++.h>
#define MAX_SIZE 152
using namespace std;

int dp[2][MAX_SIZE][MAX_SIZE * MAX_SIZE];
int N, K, S;
int a[MAX_SIZE];

int main() {
    int i, j, k;
    scanf("%d%d%d", &N, &K, &S);
    S = min(S, N * (N - 1) / 2);
    for (i = 1; i <= N; ++i) scanf("%d", &a[i]);
    for (i = 0 ; i < 2; ++i) {
        for (j = 0 ; j < MAX_SIZE; ++j) {
            for (k = 0 ; k < MAX_SIZE * MAX_SIZE; ++k) {
                dp[i][j][k] = 800000000;
            }
        }
    }
    dp[0][0][0] = 0;
    for (i = 1; i <= N; ++i) {
        memset(dp[i & 1][0], 0, sizeof(dp[i & 1][0]));
        for (j = 1; j <= i; ++j) {
            for (k = 0; k <= i * (i - 1) / 2; ++k) {
                dp[i & 1][j][k] = dp[(i-1) & 1][j][k];
                if (k >= i - j) {
                    dp[i & 1][j][k] = min(dp[i & 1][j][k], dp[(i-1) & 1][j-1][k - (i-j)] + a[i]);
                }
            }
        }
    }

    int ans = 800000000;
    for (i = 0; i <= S; ++i) {
        ans = min(ans, dp[N & 1][K][i]);
       // cout << dp[N & 1][K][i];
    }

    printf("%d\n", ans);
    return 0;
}