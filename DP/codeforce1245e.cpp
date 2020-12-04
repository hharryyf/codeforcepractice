#include <bits/stdc++.h>

using namespace std;

int a[11][11], num[11][11];
pair<int, int> coord[111];
double dp[111][2];
const int n = 10;

int main() {
    int i, j, tol = 1;
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= n; ++j) {
            scanf("%d", &a[i][j]);
        }
    }

    for (i = 1; i <= n; ++i) {
        if (i % 2 == 1) {
            for (j = 1; j <= n; ++j) {
                coord[tol] = make_pair(i, j);
                num[i][j] = tol++;
            }
        } else {
            for (j = n; j >= 1; --j) {
                coord[tol] = make_pair(i, j);
                num[i][j] = tol++;
            }
        }
    }

    for (i = 1; i <= n * n; ++i) dp[i][0] = dp[i][1] = 1000;

    dp[1][0] = dp[1][1] = 0.0;
    for (i = 2; i <= 6; ++i) dp[i][0] = dp[i][1] = 6;
    for (i = 7; i <= n * n; ++i) {
        dp[i][0] = 1.0 + 1.0 / 6.0 * (min(dp[i-1][0], dp[i-1][1]) + min(dp[i-2][0], dp[i-2][1]) + min(dp[i-3][0], dp[i-3][1]) + 
                   min(dp[i-4][0], dp[i-4][1]) + min(dp[i-5][0], dp[i-5][1]) + min(dp[i-6][0], dp[i-6][1]));
        dp[i][1] = dp[i][0];
        int x = coord[i].first, y = coord[i].second;
        if (a[x][y] != 0) {
            int nxt = num[x - a[x][y]][y];
            // printf("index= (%d, %d) \n", x, y);
            // printf("%d %d\n", i, nxt);
            dp[i][1] = min(dp[i][1], dp[nxt][0]);
        }
    }
    

    printf("%.10lf\n", min(dp[n * n][0], dp[n * n][1]));
    return 0;
}
