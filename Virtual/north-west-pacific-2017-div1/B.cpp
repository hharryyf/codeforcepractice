#include <bits/stdc++.h>
#pragma GCC optimize(3)
#pragma GCC optimize(2)
using namespace std;

int dp[1<<12][12][702];
int N, X, p[12];

int main() {
    int i, j, k, l, mx = 0;
    scanf("%d%d", &N, &X);
    for (i = 0 ; i < N; ++i) {
        scanf("%d", &p[i]);
        mx = max(mx, p[i]);
    }  
    
    for (i = 0 ; i < N; ++i) {
        if (p[i] == mx) continue;
        if ((mx - p[i] + 1) * N <= X) {
            dp[1 << i][i][X - N * (mx - p[i] + 1)] = 1;
        }
    }

    for (i = 1; i < (1 << N); ++i) {
        for (j = 0; j < N; ++j) {        
            if (i & (1 << j)) continue;
            for (k = 0; k <= X; ++k) {
                for (l = 0 ; l < N; ++l) {
                    if (dp[i][l][k] == 0) continue;
                    int nxt = i | (1 << j);
                    int dif = max(0, p[l] - p[j] + 1);
                    int tol = dif * (N - __builtin_popcount(i));
                    if (tol > k) continue;
                    dp[nxt][j][k - tol] += dp[i][l][k];
                }
            }
        }
    }

    int ans = 0;
    for (i = 0; i <= X; ++i) {
        for (j = 0; j < N; ++j) {
            ans += dp[(1 << N) - 1][j][i];
        }
    }

    printf("%d\n", ans);
    return 0;
}