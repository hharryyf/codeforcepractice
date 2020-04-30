#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 511
using namespace std;

/*
    key observation, each segment[i, j], if it can be merged
    to a single element, the element is the same.
    This can be proved by induction.

    Then, we just need to maintain a[i][j], the final element if we merge
    arr[i:j] all together, and dp[i][j], the minimum length of the segment [i:j]
    after we merge
*/

int dp[MAX_SIZE][MAX_SIZE], a[MAX_SIZE][MAX_SIZE];
int n;

int main() {
    int i, j, k, l, r;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &a[i][i]);
        for (j = i; j <= n; ++j) {
            dp[i][j] = j - i + 1;
        }
    }

    for (i = 2; i <= n; ++i) {
        for (l = 1; l <= n; ++l) {
            r = l + i - 1;
            if (r > n) break;
            for (k = l; k < r; ++k) {
                if (dp[l][k] == 1 && dp[k+1][r] == 1 && a[l][k] == a[k+1][r]) {
                    dp[l][r] = 1;
                    a[l][r] = a[l][k] + 1;
                } else {
                    dp[l][r] = min(dp[l][r], dp[l][k] + dp[k+1][r]);
                }
            }
        }
    }

    printf("%d\n", dp[1][n]);
    return 0;
}