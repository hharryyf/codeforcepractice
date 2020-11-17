#include <bits/stdc++.h>
#define MAX_SIZE 1011
using namespace std;
const int mod = 998244353;
int dp[MAX_SIZE][MAX_SIZE];
int sm[MAX_SIZE][MAX_SIZE];
int a[MAX_SIZE * 100];
int N, K;

int solve(int x) {
    int i, j, k = 0;
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= K; ++j) {
            dp[i][j] = sm[i][j] = 0;
        }
    }

    for (i = 1; i <= N; ++i) dp[i][1] = 1;
    sm[1][1] = 1;
    for (i = 2; i <= N; ++i) {
        while (k + 1 < i && a[i] - a[k + 1] >= x) ++k;
        for (j = 2; j <= K; ++j) {
            dp[i][j] = sm[k][j-1];
            if (dp[i][j] >= mod) dp[i][j] -= mod;
        }

        for (j = 0 ; j <= K; ++j) {
            sm[i][j] = sm[i-1][j] + dp[i][j];
            if (sm[i][j] >= mod) sm[i][j] -= mod;
        }
    }

    int ret = 0;
    for (i = 1; i <= N; ++i) {
        ret += dp[i][K];
        if (ret >= mod) ret -= mod;
    }

    return ret;
}

int main() {
    int i, mx = 0;
    int ans = 0;
    scanf("%d%d", &N, &K);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &a[i]);
        mx = max(mx, a[i]);
    }

    a[0] = -mx - 1;
    sort(a + 1, a + 1 + N);
    for (i = 1; i <= mx / (K - 1); ++i) {
        ans = ans + solve(i);
        if (ans >= mod) ans -= mod;
    }

    printf("%d\n", ans);
    return 0;
}