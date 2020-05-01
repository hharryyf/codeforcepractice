#include <bits/stdc++.h>
#define MAX_SIZE 511
#define MOD 1000000007
typedef long long ll;
using namespace std;

ll dp[MAX_SIZE][MAX_SIZE][2];
int b[MAX_SIZE];
int n;

ll dfs(int l, int r, int dim) {
    if (l > r) return 1;
    if (l == r) return 1;
    if (dp[l][r][dim] != -1) return dp[l][r][dim];
    ll ans = 0;
    if (dim == 0) {
        ans = dfs(l + 1, r, 1);
    } else {
        int i;
        ans = dfs(l, r, 0);
        for (i = l; i < r; ++i) {
            if (b[i+1] > b[l]) {
                ans += dfs(l, i, 0) * dfs(i+1, r, 1);
                ans %= MOD;
            }
        }
    }
    return dp[l][r][dim] = ans;
}

int main() {
    int i, j;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) scanf("%d", &b[i]);
    for (i = 0; i <= n; ++i) {
        for (j = 0 ; j <= n; ++j) {
            dp[i][j][0] = dp[i][j][1] = -1;
        }
    }

    
    printf("%I64d\n", dfs(1, n, 0));
    return 0;
}
