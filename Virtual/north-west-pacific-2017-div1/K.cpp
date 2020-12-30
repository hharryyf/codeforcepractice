#include <bits/stdc++.h>

using namespace std;

const int inf = 1000000;
int dp[44][2][2];
char st[44];
int a[44];
int N;

int main() {
    int i, j, k, x, y, nxt;
    scanf("%s", st + 1);
    N = strlen(st + 1);
    for (i = 1; i <= N; ++i) a[i] = st[i] - '0';
    for (i = 0 ; i <= N; ++i) {
        for (j = 0 ; j < 2; ++j) {
            for (k = 0 ; k < 2; ++k) {
                dp[i][j][k] = inf;
            }
        }
    }

    int M = N / 2;
    // minimum cost to make s[1:i] = reverse(s[N-i+1:N])
    // which j carry from i+1 ->i
    // and k carry from N-i->N-i+1
    dp[0][0][0] = dp[0][1][0] = 0;
    for (i = 0 ; i < M; ++i) {
        for (j = 0 ; j < 2; ++j) {
            for (k = 0 ; k < 2; ++k) {
                if (dp[i][j][k] == inf) continue;
                int l = i + 1, r = N - i;
                for (x = 0 ; x <= 9; ++x) {
                    for (y = 0 ; y <= 9; ++y) {
                        for (nxt = 0; nxt < 2; ++nxt) {
                            int ld = x + a[l] + nxt;
                            int rd = y + a[r] + k;
                            int lc = ld / 10, rc = rd / 10;
                            ld %= 10, rd %= 10;
                            if (lc != j) continue;
                            if (ld != rd) continue;
                            dp[i+1][nxt][rc] = min(dp[i+1][nxt][rc], dp[i][j][k] + x + y);
                        }
                    }
                }
            }
        }
    }

    int ans = inf;
    if (N % 2 == 1) {
        for (i = 0; i < 10; ++i) {
            for (j = 0 ; j < 2; ++j) {
                for (k = 0 ; k < 2; ++k) {
                    int d = a[M + 1] + i + k;
                    int c = d / 10;
                    if (c != j) continue;
                    ans = min(ans, dp[M][j][k] + i);
                }
            }
        }
    } else {
        for (i = 0; i < 2; ++i) {
            ans = min(ans, dp[M][i][i]);
        }
    }

    printf("%d\n", ans);
    return 0;
}