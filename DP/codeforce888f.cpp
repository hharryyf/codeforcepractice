#include <bits/stdc++.h>
#define MAX_SIZE 511
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
int g[MAX_SIZE][MAX_SIZE];
ll dp[MAX_SIZE][MAX_SIZE][2];
int N;

int main() {
    int i, j, k;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= N; ++j) {
            scanf("%d", &g[i][j]);
        }
    }    

    for (i = 1; i <= N; ++i) {
        dp[i][i][0] = 1;
    }

    for (i = 1; i < N; ++i) {
        for (j = 1; j <= N - i; ++j) {
            int r = i + j;
            for (k = j; k < r; ++k) {
                if (g[j][r]) {
                    dp[j][r][0] += (dp[j][k][0] + dp[j][k][1]) * (dp[k+1][r][0] + dp[k+1][r][1]);
                }
                if (k != j) {
                    dp[j][r][1] += dp[j][k][0] * (dp[k][r][0] + dp[k][r][1]);
                }
                dp[j][r][0] %= mod;
                dp[j][r][1] %= mod;
            }
        }
    }

    printf("%I64d\n", (dp[1][N][0] + dp[1][N][1]) % mod);
    return 0;
}