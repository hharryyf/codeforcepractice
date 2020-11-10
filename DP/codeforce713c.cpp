#include <bits/stdc++.h>
#define MAX_SIZE 3011
using namespace std;
typedef long long ll;
ll dp[MAX_SIZE][MAX_SIZE];
int a[MAX_SIZE], b[MAX_SIZE];

int main() {
    int n, i, j;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        a[i] -= i;
        b[i] = a[i];
    }

    sort(b + 1, b + 1 + n);
    for (i = 1; i <= n; ++i) {
        dp[i][1] = dp[i-1][1] + abs(b[1] - a[i]);
        for (j = 2; j <= n; ++j) {
            dp[i][j] = min(dp[i][j-1], dp[i-1][j] + abs(b[j] - a[i]));
        }
    }

    cout << dp[n][n] << endl;
    return 0;
}