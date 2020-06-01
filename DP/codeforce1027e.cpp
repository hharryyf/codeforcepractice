#include <bits/stdc++.h>
#define MAX_SIZE 511
typedef long long ll;
using namespace std;

const int mod = 998244353;
// dp[i][j] refers to the number of ways 
// to color the tiles such that no length > j consecutive
// tiles have the same color
// dp[i][j] = sum(dp[k][j], which k = i-j..i-1)

ll dp[MAX_SIZE][MAX_SIZE];
ll tol[MAX_SIZE];

int main() {
    int n, k, i, j, p;
    scanf("%d%d", &n, &k);
    
    for (i = 1 ; i <= n; ++i) dp[0][i] = 1;
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= n; ++j) {
            for (p = max(i - j, 0); p <= i-1; ++p) {
                dp[i][j] = dp[i][j] + dp[p][j];
                dp[i][j] %= mod;
            }
        }
    }

    for (i = 1; i <= n; ++i) {
        tol[i] = dp[n][i] - dp[n][i-1];
        // cout << tol[i] << endl;
    }

    
    ll ans = 0;
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= n; ++j) {
            if (i * j < k) {
                ans += tol[i] * tol[j];
                ans %= mod;
            }
        }
    }

    ans *= 2;
    cout << (ans % mod + mod) % mod << endl;
    return 0;
}