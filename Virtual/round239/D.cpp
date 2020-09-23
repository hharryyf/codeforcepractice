#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const ll mod = 1e9 + 7;
ll dp[1011][1011];
int p[1011];
int n;

ll f(int l, int r) {
    // cout << l << " " << r << endl;
    if (l > r) return 0;
    if (dp[l][r] != -1) return dp[l][r];
    dp[l][r] = 1ll * 2 + f(p[l], l-1) + f(l+1, r);
    dp[l][r] %= mod;
    return dp[l][r];
}

int main() {
    int i, j;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &p[i]);
        for (j = i; j <= n; ++j) {
            dp[i][j] = -1;
        }
    }

    f(1, n);
    cout << dp[1][n] << endl;
    return 0;
}