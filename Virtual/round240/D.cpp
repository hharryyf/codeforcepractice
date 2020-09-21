#include <bits/stdc++.h>
#define MAX_SIZE 2011
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
ll dp[MAX_SIZE][MAX_SIZE];
int n, k;

int main() {
    int i, j, p;
    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; ++i) {
        dp[1][i] = 1;
    }

    for (i = 2; i <= k; ++i) {
        for (j = 1; j <= n; ++j) {
            for (p = 1; p * j <= n; ++p) {
                dp[i][p * j] += dp[i-1][j];
                dp[i][p * j] %= mod;
            }
        }
    }
    ll ans = 0;
    for (i = 1; i <= n; ++i) {
        ans += dp[k][i];
        ans %= mod;
    }

    cout << ans << endl;
    return 0;
}