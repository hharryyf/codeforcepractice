#include <bits/stdc++.h>
using namespace std;
// maximum reduction on blue when we have mask as the set and r reduction
// on red
int dp[1 << 16][142];
char c[16], st[4];
int r[16], b[16];
int costb[1 << 16], costr[1 << 16];

int main() {
    int i, j, n, k, tr = 0, tb = 0;
    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
        scanf("%s%d%d", st, &r[i], &b[i]);
        c[i] = st[0];
        tr += r[i], tb += b[i];
    }

    for (i = 0 ; i < 1 << 16; ++i) {
        for (j = 0 ; j < 129; ++j) {
            dp[i][j] = -10000000;
        }
    }

    dp[0][0] = 0;

    for (i = 0 ; i < (1 << n); ++i) {
        for (j = 0 ; j < n; ++j) {
            if ((1 << j) & i) {
                costr[i] += (c[j] == 'R'), costb[i] += (c[j] == 'B');
            } 
        }
    }    

    for (i = 0 ; i < (1 << n); ++i) {
        for (k = 0 ; k < 129; ++k) {
            for (j = 0 ; j < n; ++j) {
                if (i & (1 << j)) continue;
                int nxt = i | (1 << j);
                // we have k red reductions and dp[i][k] blue reductions
                int red = min(r[j], costr[i]), blue = min(b[j], costb[i]);
                dp[nxt][k + red] = max(dp[nxt][k + red], dp[i][k] + blue);
            }
        }
    }

    int ans = 1000000000;
    for (i = 0 ; i < 129; ++i) {
        if (dp[(1 << n) - 1][i] >= 0) {
            ans = min(ans, n + max(tr - i, tb - dp[(1 << n) - 1][i]));
        }
    }

    printf("%d\n", ans);
    return 0;
}