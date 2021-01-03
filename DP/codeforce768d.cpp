#include <bits/stdc++.h>
using namespace std;

double dp[8011][1011];
int K, Q;

int sgn(double x) {
    if (fabs(x) <= 1e-10) return 0;
    if (x > 0) return 1;
    return -1;
}

int main() {
    int i, j;
    scanf("%d%d", &K, &Q);
    dp[1][1] = 1;
    for (i = 2; i <= 8010; ++i) {
        for (j = 1; j <= i && j <= K; ++j) {
            dp[i][j] = dp[i-1][j] * j / K + dp[i-1][j-1] * (K - j + 1) / K;
        }
    }

    // printf("%lf\n", dp[8010][K]);
    while (Q-- > 0) {
        int p;
        scanf("%d", &p);
        for (i = 1; i <= 8010; ++i) {
            if (sgn(dp[i][K] - ((1.0 * p - 1e-7)/ 2000)) >= 0) {
                printf("%d\n", i);
                break;
            }
        }
    }
    return 0;
}