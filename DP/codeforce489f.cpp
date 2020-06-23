#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 503
typedef long long ll;
using namespace std;

ll dp[2][MAX_SIZE][MAX_SIZE];
char s[MAX_SIZE];
int cnt[MAX_SIZE];
int mod;

int main() {
    int i, j, n, m, k;
    scanf("%d%d%d", &n, &m, &mod);
    for (i = 0; i < m; ++i) {
        scanf("%s", s);
        for (j = 0 ; j < n; ++j) {
            cnt[j] += s[j] - '0';
        }
    }

    int c0 = 0, c1 = 0;
    for (i = 0 ; i < n; ++i) {
        if (cnt[i] == 0) c0++;
        else if (cnt[i] == 1) c1++;
    }

    dp[m & 1][c0][c1] = 1;
    for (i = m; i < n; ++i) {
        for (j = 0 ; j <= n; ++j) {
                k = 2 * n - 2 * j - 2 * i;
                if (k < 0 || k + j > n) continue;    
                if (j >= 2 && k+2 <= n) {
                    dp[(i+1) & 1][j-2][k+2] += (dp[i & 1][j][k] * (j * (j - 1) / 2));
                    dp[(i+1) & 1][j-2][k+2] %= mod;
                }

                if (k >= 2) {
                    dp[(i+1) & 1][j][k-2] += (dp[i & 1][j][k] * (k * (k-1) / 2));
                    dp[(i+1) & 1][j][k-2] %= mod;
                }

                if (j >= 1) {
                    dp[(i+1) & 1][j-1][k] += dp[i & 1][j][k] * (j * k);
                    dp[(i+1) & 1][j-1][k] %= mod;
                }
        }
    }

    cout << dp[n & 1][0][0] % mod << endl;
    return 0;
}