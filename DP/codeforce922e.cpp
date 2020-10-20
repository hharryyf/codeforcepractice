#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 10004
using namespace std;

ll dp[1004][MAX_SIZE];
int c[1004], cost[1004];
const ll inf = 1e15;

int main() {
    int n, i, j, k, W, B, X, limit = 0;
    scanf("%d%d%d%d", &n, &W, &B, &X);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &c[i]);
        limit += c[i];
    }

    for (i = 1; i <= n; ++i) {
        scanf("%d", &cost[i]);
    }

    for (i = 1; i <= limit; ++i) dp[0][i] = -inf;
    for (i = 1; i <= n; ++i) {
        for (j = 0; j <= limit; ++j) {
            dp[i][j] = -inf;
        }
    }

    dp[0][0] = W;
    for (k = 0; k <= c[1]; ++k) {
        ll capacity = W;
        ll money = min(dp[0][0], capacity);
        if (money >= 1ll * cost[1] * k) {
            dp[1][k] = max(dp[1][k], money - 1ll * cost[1] * k);
        }
    }
    for (i = 1; i < n; ++i) {
        for (j = 0; j <= limit; ++j) {
            // from dp[i][j] to dp[i+1][next]
            if (dp[i][j] < 0) continue;
            for (k = 0; k <= c[i+1] && j + k <= limit; ++k) {
                // total number of birds = j + k
                // total capacity before this round = W + B * dp[i][j]
                // total money before this round = min(dp[i][j] + X, capacity)
                // maximum money = max(dp[i+1][j + k], money - cost[i+1] * k)
                ll capacity = 1ll * B * j + W;
                ll money = min(dp[i][j] + X, capacity);
                if (money >= 1ll * cost[i+1] * k) {
                    dp[i+1][j+k] = max(dp[i+1][j+k], money - 1ll * cost[i+1] * k);
                }
            }
        }
    }

    for (i = limit; i >= 0; --i) {
        if (dp[n][i] >= 0) {
            printf("%d\n", i);
            return 0;
        }
    }

    return 0;
}