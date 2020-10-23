#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll dp[41];
int a[41], b[41];

ll dfs(int pos, int limit1, int limit2) {
    int i, j;
    if (pos == -1) return 1;
    if (!limit1 && !limit2 && dp[pos] != -1) return dp[pos];
    int up1 = limit1 ? a[pos] : 1;
    int up2 = limit2 ? b[pos] : 1;
    ll ret = 0;
    for (i = 0; i <= up1; ++i) {
        for (j = 0 ; j <= up2; ++j) {
            if ((i & j) != 0) continue;
            ret += dfs(pos - 1, limit1 && (i == up1), limit2 && (j == up2));
        }
    }

    if (!limit1 && !limit2) dp[pos] = ret;
    return ret;
}

ll query(int v1, int v2) {
    if (v1 < 0 || v2 < 0) return 0;
    int i, len1 = 0, len2 = 0;
    for (i = 0; i < 40; ++i) a[i] = b[i] = 0;
    while (v1 > 0) {
        a[len1++] = v1 & 1;
        v1 >>= 1;
    }

    while (v2 > 0) {
        b[len2++] = v2 & 1;
        v2 >>= 1;
    }
    
    return dfs(len2 - 1, 1, 1);
}

int main() {
    int T, i;
    for (i = 0 ; i < 40; ++i) {
        dp[i] = -1;
    }

    scanf("%d", &T);
    while (T-- > 0) {
        int l, r;
        scanf("%d%d", &l, &r);
        ll ans = query(r, r);
        ans += query(l - 1, l - 1);
        ans -= query(l-1, r) * 2;
        printf("%lld\n", ans);
    }
    return 0;
}