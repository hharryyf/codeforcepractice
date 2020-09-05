#include <bits/stdc++.h>
#define MAX_SIZE 2011
typedef long long ll;
using namespace std;
const ll mod = 1e9+7;
ll dp[MAX_SIZE][MAX_SIZE];
int a[MAX_SIZE];
int n, h;

int main() {
    int i, j;
    dp[0][0] = 1;
    scanf("%d%d", &n, &h);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        a[i] = h - a[i];
        if (a[i] < 0) {
            printf("0\n");
            return 0;
        }
    }

    for (i = 1; i <= n; ++i) {
        for (j = max(0,a[i] - 1); j <= a[i] + 1; ++j) {
            if (j == a[i]) {
                dp[i][j] = dp[i-1][j] + (j >= 1 ? dp[i-1][j-1] : 0);
            }

            if (j + 1 == a[i]) {
                dp[i][j] += dp[i-1][j+1] * (j+1) + dp[i-1][j] + dp[i-1][j] * j;
            }

            dp[i][j] %= mod;
            // cout << "dp[" << i << "][" << j << "]= " << dp[i][j] << endl;
        }
    }

    cout << dp[n][0] << endl;
    return 0;
}