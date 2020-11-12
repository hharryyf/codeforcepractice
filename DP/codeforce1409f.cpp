#include <bits/stdc++.h>

using namespace std;

int dp[211][211][211];
char s[211], t[4];

int main() {
    int N, K, i, j, k;
    scanf("%d%d", &N, &K);
    scanf("%s", s + 1);
    scanf("%s", t + 1);
    if (t[1] == t[2]) {
        for (i = 1; i <= N && K > 0; ++i) {
            if (s[i] != t[1]) {
                s[i] = t[1];
                K--;
            }
        }
        int cnt = 0;
        for (i = 1; i <= N; ++i) {
            if (t[1] == s[i]) {
                cnt++;
            }
        }
        printf("%d\n", cnt * (cnt - 1) / 2);
        return 0;
    }
    for (i = 0 ; i < 211; ++i) {
        for (j = 0 ; j < 211; ++j) {
            for (k = 0 ; k < 211; ++k) {
                dp[i][j][k] = -1000000;
            }
        }
    }

    dp[0][0][0] = 0;

    for (i = 0 ; i < N; ++i) {
        for (j = 0 ; j <= i; ++j) {
            for (k = 0; k <= K && k <= i; ++k) {
                if (s[i+1] == t[1]) {
                    dp[i+1][j+1][k] = max(dp[i+1][j+1][k], dp[i][j][k]);
                } else {
                    if (k < K) {
                        dp[i+1][j+1][k+1] = max(dp[i+1][j+1][k+1], dp[i][j][k]);
                    }
                    dp[i+1][j][k] = max(dp[i+1][j][k], dp[i][j][k]);
                }

                if (s[i+1] == t[2]) {
                    dp[i+1][j][k] = max(dp[i+1][j][k], dp[i][j][k] + j);
                } else {
                    if (k < K) {
                        dp[i+1][j][k+1] = max(dp[i+1][j][k+1], dp[i][j][k] + j);
                    }
                }
            }
        }
    }

    int ans = 0;
    for (i = 0; i <= N; ++i) {
        for (j = 0; j <= K; ++j) {
            ans = max(dp[N][i][j], ans);
        }
    }

    printf("%d\n", ans);
    return 0;
}