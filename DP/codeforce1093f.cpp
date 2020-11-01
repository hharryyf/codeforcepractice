#include <bits/stdc++.h>
#define MAX_SIZE 100111
using namespace std;

int dp[MAX_SIZE][101];
int ans[MAX_SIZE];
int cnt[MAX_SIZE][101];
int a[MAX_SIZE];
int n, k, len;
const int mod = 998244353;

int main() {
    int i, j;
    scanf("%d%d%d", &n, &k, &len);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        if (a[i] == -1) {
            for (j = 1; j <= k; ++j) cnt[i][j] = cnt[i-1][j] + 1;
        } else {
            for (j = 1; j <= k; ++j) {
                if (j != a[i]) {
                    cnt[i][j] = 0;
                } else {
                    cnt[i][j] = cnt[i-1][j] + 1;
                }
            }
        }
    }

    if (len == 1) {
        printf("0\n");
        return 0;
    }

    ans[0] = 1;
    if (a[1] == -1) {
        for (i = 1; i <= k; ++i) dp[1][i] = 1;
        ans[1] = k;
    } else {
        dp[1][a[1]] = 1;
        ans[1] = 1;
    }   

    for (i = 2; i <= n; ++i) {
        for (j = 1; j <= k; ++j) {
            if (a[i] == -1 || a[i] == j) {
                dp[i][j] = ans[i-1];
                // cout << cnt[i][j] << " - " << cnt[i-len][j] << endl;
                if (i >= len && cnt[i][j] - cnt[i-len][j] == len) {
                    dp[i][j] -= (ans[i-len] - dp[i-len][j]) % mod; 
                    // cout << i << " -> " << ans[i-len] << " " << dp[i-len][j] << endl;
                    dp[i][j] %= mod;
                }        
            }

            ans[i] += dp[i][j];
            ans[i] %= mod;
            // cout << dp[i][j] << " ";
        }
        // cout << endl;
    }

    printf("%d\n", ((ans[n] % mod) + mod) % mod);
    return 0;
}