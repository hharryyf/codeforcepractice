#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll dp[23][11][2];
int a[22];

ll dfs(int pos, int pre, bool has49, bool limit) {
    if (pos < 0) return has49;
    if (!limit && dp[pos][pre][has49] != -1) return dp[pos][pre][has49];
    int up = limit ? a[pos] : 9;
    int i;
    ll ans = 0;
    for (i = 0 ; i <= up; i++) {
        ans += dfs(pos - 1, i, (has49 || (pre == 4 && i == 9)), (limit && i == up));
    }
    if (!limit) dp[pos][pre][has49] = ans;
    return ans;
}

int main() {
    int i, j;
    for (i = 0 ; i < 22; i++) {
        for (j = 0 ; j < 10; j++) {
            dp[i][j][0] = dp[i][j][1] = -1;
        }
    }
    
    int T;
    scanf("%d", &T);
    while (T > 0) {
        ll n;
        scanf("%lld", &n);
        int len = 0;
        while (n > 0) {
            a[len++] = n % 10;
            n = n / 10;
        }
        
        printf("%lld\n", dfs(len - 1, -1, false, true));
        T--;
    }
    return 0;
}
