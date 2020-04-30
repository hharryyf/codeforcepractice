#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, k, mod;
// dp[i][j] refers to the number of ways that
// forms a i digit number which remainder is j (mod k)
//and all its suffix has no numbers that has a remainder of j 
ll dp[1011][111][2], p10[1011];
ll p12[1011];

int main() {
    int i, j, p;
    scanf("%d%d%d", &n, &k, &mod);
    p10[0] = 1 % k;
    p12[0] = 1;
    for (i = 1; i <= n; ++i) {
        p10[i] = (p10[i-1] * 10) % k;
        p12[i] = (p12[i-1] * 10) % mod;
    }
    dp[1][0][0] = 1;
    for (i = 1; i <= 9; ++i) {
        dp[1][i % k][1]++;
    }

    for (i = 1; i < n; ++i) {
        dp[i+1][0][0] = 1;
        for (j = 0; j < k; ++j) {
            for (p = 0; p <= 9; ++p) {
                int nv = (1ll * j + 1ll * p * p10[i]) % k;
                if (j == 0 && p == 0) continue;
                if (j == 0) {
                    dp[i+1][nv][1] = (dp[i+1][nv][1] + dp[i][j][0]) % mod;
                } else {
                    dp[i+1][nv][1] = (dp[i+1][nv][1] + dp[i][j][1]) % mod;
                }
            }
        }
    }

    ll ans = 0;
    for (i = 1; i <= n-1; ++i) {
        ans = ans + 1ll * 9 * dp[i][0][1] * p12[n-i-1];
        ans %= mod;
        // cout << dp[i][0][1] << endl;
    }
    ans += dp[n][0][1];
    ans %= mod;
    printf("%I64d\n", ans);
    return 0;
}