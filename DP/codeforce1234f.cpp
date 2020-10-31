#include <bits/stdc++.h>
#define MAX_SIZE 1048597
using namespace std;

int dp[MAX_SIZE];
char st[MAX_SIZE];

int main() {
    int i, j;
    scanf("%s", st + 1);
    int n = strlen(st + 1);
    int mx = 0;
    for (i = 1; i <= n; ++i) {
        int bt = 0;
        for (j = 0; j <= 19 && j <= i - 1; ++j) {
            if (bt & (1 << (st[i - j] - 'a'))) break;
            bt |= (1 << (st[i - j] - 'a'));
            dp[bt] = j + 1;
        }

        mx = max(mx, st[i] - 'a');
    }

    mx++;
    for (i = 0 ; i < (1 << mx); ++i) {
        for (j = 0 ; j <= mx; ++j) {
            if (i & (1 << j)) {
                dp[i] = max(dp[i], dp[i ^ (1 << j)]);
            }
        }
    }

    int ans = 0;
    for (i = 0 ; i < (1 << mx); ++i) {
        ans = max(ans, dp[i] + dp[((1 << mx) - 1) ^ i]);
        // cout << dp[i] << " " << dp[((1 << mx) - 1) ^ i] << endl;
    }

    printf("%d\n", ans);
    return 0;
}