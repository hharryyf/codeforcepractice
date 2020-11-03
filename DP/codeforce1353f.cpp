#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 111
using namespace std;
typedef long long ll;
ll dp[MAX_SIZE][MAX_SIZE];
ll a[MAX_SIZE][MAX_SIZE];
const ll inf = 1e18;

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int n, m, i, j, k, l;
        scanf("%d%d", &n, &m);
        for (i = 1; i <= n; ++i) {
            for (j = 1; j <= m; ++j) {
                scanf("%I64d", &a[i][j]);
            }
        }

        ll ans = 1e18;
        for (i = 1; i <= n; ++i) {
            for (j = 1; j <= m; ++j) {
                for (k = 1; k <= n; ++k) {
                    for (l = 1; l <= m; ++l) {
                        dp[k][l] = inf;
                    }
                }

                ll ht = a[i][j];
                dp[i][j] = 0;
                for (k = i; k >= 1; --k) {
                    for (l = j; l >= 1; --l) {
                        ll h = ht - (i - k) - (j - l);
                        if (h > a[k][l]) continue;
                        if (k + 1 <= i) {
                            dp[k][l] = min(dp[k+1][l] + a[k][l] - h, dp[k][l]);
                        }

                        if (l + 1 <= j) {
                            dp[k][l] = min(dp[k][l+1] + a[k][l] - h, dp[k][l]);
                        }
                    }
                }

                for (k = i; k <= n; ++k) {
                    for (l = j; l <= m; ++l) {
                        ll h = ht + (k - i) + (l - j);
                        if (h > a[k][l]) continue;
                        if (k - 1 >= i) {
                            dp[k][l] = min(dp[k-1][l] + a[k][l] - h, dp[k][l]);
                        }

                        if (l - 1 >= j) {
                            dp[k][l] = min(dp[k][l-1] + a[k][l] - h, dp[k][l]);
                        }
                    }
                }

                ans = min(ans, dp[1][1] + dp[n][m]);
            }
        }

        printf("%I64d\n", ans);
    }
    return 0;
}