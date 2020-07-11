#include <bits/stdc++.h>
#define MAX_SIZE 1000011
using namespace std;

int dp[MAX_SIZE][3][3];
int cnt[MAX_SIZE];

int main() {
    int i, n, m, j, k, l;
    memset(dp, -1000000, sizeof(dp));
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i) {
        int v;
        scanf("%d", &v);
        ++cnt[v];
    }

    dp[0][0][0] = 0;
    for (i = 1; i <= m; ++i) {
        for (j = 0 ; j < 3; ++j) {
            for (k = 0 ; k < 3; ++k) {
                for (l = 0 ; l < 3; ++l) {
                    if (j + k + l > cnt[i]) continue;
                    dp[i][j][k] = max(dp[i][j][k], dp[i-1][l][j] + (cnt[i] - j - k - l) / 3 + l);
                }
            }
        }
    }

    printf("%d\n", dp[m][0][0]);
    return 0;
}