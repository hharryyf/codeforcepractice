#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 100011
typedef long long ll;
using namespace std;

ll dp[MAX_SIZE][129];
struct score {
    int a[8];
    bool operator <(score other) const {
        return a[0] > other.a[0];
    }
};
score sc[MAX_SIZE];
int n, p, k;

int main() {
    int i, j, l;
    scanf("%d%d%d", &n, &p, &k);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &sc[i].a[0]);
    }

    for (i = 1; i <= n; ++i) {
        for (j = 1 ; j <= p; ++j) {
            scanf("%d", &sc[i].a[j]);
        }
    }

    sort(sc + 1, sc + 1 + n);

    for (i = 0 ; i <= n; ++i) {
        for (j = 0 ; j < (1 << p); ++j) {
            dp[i][j] = -1e16;
        }
    }

    dp[0][0] = 0;
    for (i = 1; i <= k; ++i) {
        dp[0][0] += sc[i].a[0];
    }

    // cout << dp[0][0] << endl;
    for (i = 0; i < n; ++i) {
        for (j = 0 ; j < (1 << p); ++j) {
            dp[i+1][j] = max(dp[i][j], dp[i+1][j]);
            for (l = 0 ; l < p; ++l) {
                if (((1 << l) & j) != 0) continue;
                int nxt = j | (1 << l);
                int bc = __builtin_popcount(j);
                if (i < bc + k) {
                    dp[i+1][nxt] = max(dp[i+1][nxt], dp[i][j] + sc[i+1].a[l+1] - sc[i+1].a[0] + sc[bc + k + 1].a[0]);
                } else {
                    dp[i+1][nxt] = max(dp[i+1][nxt], dp[i][j] + sc[i+1].a[l+1]);
                }
            }
        }
    }

    ll ans = 0;
    for (i = k+p; i <= n; ++i) {
        ans = max(ans, dp[i][(1 << p) - 1]);
    }

    printf("%I64d\n", ans);
    return 0;
}