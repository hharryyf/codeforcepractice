#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;
const int inf = 100000000;
int dp[MAX_SIZE][53];
int N, K, G1, G2, G3;
char st[MAX_SIZE];

int main() {
    int i, j, tol = 0;
    for (i = 0 ; i < MAX_SIZE; ++i) {
        for (j = 0 ; j < 53; ++j) {
            dp[i][j] = -inf;
        }
    }

    dp[0][0] = 0;
    scanf("%d%d%d%d%d", &N, &K, &G1, &G2, &G3);
    scanf("%s", st + 1);
    for (i = 1; i <= N; ++i) tol += (st[i] == '#');
    for (i = 1; i <= N; ++i) {
        for (j = 0; j <= tol; ++j) {
            dp[i][j] = dp[i-1][j];
            if (i >= 2 && st[i] != '#' && st[i-1] != '#') {
                dp[i][j] = max(dp[i][j], dp[i-2][j] + 1);
            }

            if (i >= 3 && st[i] != '#' && st[i-1] == '#' && st[i-2] != '#' && j > 0) {
                dp[i][j] = max(dp[i][j], dp[i - 3][j - 1]);
            }
        }
    }

    int ans = 0;
    for (i = 0; i <= tol; ++i) {
        for (j = 0 ; j <= dp[N][i]; ++j) {
            ans = max(ans, G3 * i + G2 * j + G1 * min(N - j * 2 - i * 2 - tol, K));
        }
    }

    printf("%d\n", ans);
    return 0;
}