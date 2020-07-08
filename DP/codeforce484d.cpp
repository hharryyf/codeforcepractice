#pragma GCC  optimize(3)
#pragma GCC  optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 1000111
typedef long long ll;
using namespace std;

int a[MAX_SIZE];
ll dp[MAX_SIZE][2];
int n;

int main() {
    int i;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) scanf("%d", &a[i]);
    dp[2][1] = abs(a[2] - a[1]);
    for (i = 3; i <= n; ++i) {
        if ((a[i-1] <= a[i] && a[i-1] <= a[i-2]) || (a[i-1] >= a[i] && a[i-1] >= a[i-2])) {
            dp[i][1] = dp[i-1][0] + abs(a[i] - a[i-1]);
            dp[i][0] = max(dp[i-1][0], dp[i-1][1]);
        } else {
            dp[i][1] = max(dp[i-1][0], dp[i-1][1]) + abs(a[i] - a[i-1]);
            dp[i][0] = max(dp[i-1][0], dp[i-1][1]);
        }
    }

    printf("%I64d\n", max(dp[n][0], dp[n][1]));
    return 0;
}
