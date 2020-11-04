#include <bits/stdc++.h>
#define MAX_SIZE 3011
using namespace std;
typedef long long ll;
const ll mod = 998244353;
ll dp[MAX_SIZE][MAX_SIZE];
char s[MAX_SIZE], t[MAX_SIZE];

int main() {
    int n, m, i, j;
    scanf("%s", s + 1);
    scanf("%s", t + 1);
    n = strlen(s + 1), m = strlen(t + 1);
    for (i = 1; i <= n; ++i) {
        if (i > m || s[1] == t[i]) dp[i][i] = 2;
    }

    for (i = 2; i <= n; ++i) {
        for (j = 1; j + i - 1 <= n; ++j) {
            int r = j + i - 1;
            if (j > m || t[j] == s[i]) dp[j][r] += dp[j+1][r];
            if (r > m || t[r] == s[i]) dp[j][r] += dp[j][r-1];
            dp[j][r] %= mod;
        }
    }

    ll ans = 0;
    for (i = m; i <= n; ++i) {
        ans += dp[1][i];
        ans %= mod;
    }

    cout << ans << endl;
    return 0;
}