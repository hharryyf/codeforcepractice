#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
const int inf = 1e7;
int dp[2][3411][83][83];
int a[83], pos[83];
int n;

int main() {
    int i, j = 0, k, l, tol_0 = 0, tol_1 = 0;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        if (a[i] == 1) {
            pos[++j] = i;
            tol_1++;
        } else {
            tol_0++;
        }
    }

    int sz = n * (n - 1) / 2, limit = tol_0 * (tol_0 - 1) / 2;
    for (i = 0 ; i < 2; ++i) {
        for (j = 0 ; j <= sz; ++j) {
            for (k = 0; k <= n; ++k) {
                for (l = 0 ; l <= tol_1; ++l) {
                    dp[i][j][k][l] = inf;
                }
            }
        }
    }

    dp[0][0][0][0] = 0;
    
    for (i = 0 ; i < n; ++i) {
        int curr = i & 1, nxt = (i + 1) & 1;
        for (j = 0 ; j <= sz; ++j) {
            for (k = 0 ; k <= tol_0; ++k) {
                for (l = 0 ; l <= tol_1; ++l) {
                    dp[nxt][j][k][l] = inf;
                }
            }
        }

        for (j = 0 ; j <= sz; ++j) {
            for (k = 0 ; k <= tol_0; ++k) {
                for (l = 0 ; l <= tol_1; ++l) {
                    if (dp[curr][j][k][l] >= inf) continue;
                    // consider what to put at i + 1
                    if (k + 1 <= tol_0) dp[nxt][j][k+1][l] = min(dp[nxt][j][k+1][l], dp[curr][j][k][l] + k);
                    if (l + 1 <= tol_1) dp[nxt][j + abs(pos[l + 1] - i - 1)][0][l+1] = min(dp[nxt][j + abs(pos[l + 1] - i - 1)][0][l+1], 
                                                                                           dp[curr][j][k][l]);
                }
            }
        }
    }

    int ans = 0;
    for (i = 0 ; i <= sz; ++i) {
        int curr = inf;
        for (k = 0; k <= tol_0; ++k) {
            for (l = 0 ; l <= tol_1; ++l) {
                curr = min(curr, dp[n & 1][i][k][l]);
            }
        }
        ans = max(ans, limit - curr);
        printf("%d ", ans);
    }
    return 0;
}