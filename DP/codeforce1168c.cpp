#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 300011
using namespace std;

int dp[MAX_SIZE][19], a[MAX_SIZE], N, Q;
int pos[19];

int main() {
    int i, j, k;
    scanf("%d%d", &N, &Q);
    for (i = 1; i <= N; ++i) scanf("%d", &a[i]);
    for (i = 1; i <= N; ++i) {
        for (j = 0 ; j <= 18; ++j) {
            if (a[i] & (1 << j)) {
                for (k = 0 ; k <= 18; ++k) {
                    if (a[i] & (1 << k)) continue;
                    dp[i][k] = max(dp[pos[j]][k], dp[i][k]);
                }
            }
        }

        for (j = 0 ; j <= 18; ++j) {
            if (a[i] & (1 << j)) {
                pos[j] = i;
                dp[i][j] = i;
            }
        }
    }

    while (Q-- > 0) {
        int l, r, ok = 0;
        scanf("%d%d", &l, &r);
        for (i = 0 ; i <= 18; ++i) {
            if (a[l] & (1 << i)) {
                if (dp[r][i] >= l) {
                    ok = 1;
                    break;
                }
            }
        }

        if (ok) {
            printf("Shi\n");
        } else {
            printf("Fou\n");
        }
    }
    return 0;
}