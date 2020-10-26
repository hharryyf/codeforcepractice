#include <bits/stdc++.h>
#define MAX_SIZE 411
using namespace std;

int dp[MAX_SIZE][MAX_SIZE];
char s[MAX_SIZE], t1[MAX_SIZE], t2[MAX_SIZE], t[MAX_SIZE];
int nxt[MAX_SIZE][26];
int n, m, m1, m2;

bool check() {
    int i, j;
    for (i = 0; i <= m1; ++i) {
        for (j = 0 ; j <= m2; ++j) {
            dp[i][j] = MAX_SIZE;
        }
    }

    dp[0][0] = 0;

    for (i = 0 ; i <= m1; ++i) {
        for (j = 0 ; j <= m2; ++j) {
            if (dp[i][j] > n) continue;
            // dp[i][j] -> dp[i+1][j], dp[i][j+1]
            if (i + 1 <= m1) {
                dp[i+1][j] = min(dp[i+1][j], nxt[dp[i][j] + 1][t1[i+1] - 'a']); 
            }

            if (j + 1 <= m2) {
                dp[i][j+1] = min(dp[i][j+1], nxt[dp[i][j] + 1][t2[j+1] - 'a']);
            }
        }
    }
    return dp[m1][m2] <= n;
}

void init() {
    int i, j;
    for (i = 0 ; i < MAX_SIZE; ++i) {
        for (j = 0 ; j < 26; ++j) {
            nxt[i][j] = MAX_SIZE;
        }
    }

    for (i = n; i >= 0; --i) {
        for (j = 0 ; j < 26; ++j) {
            if (s[i] == 'a' + j) {
                nxt[i][j] = i;
            } else {
                nxt[i][j] = nxt[i+1][j];
            }
        }
    }
}

int main() {
    int T, i, j, ok;
    scanf("%d", &T);
    while (T-- > 0) {
        ok = 0;
        scanf("%s", s + 1);
        scanf("%s", t + 1);
        n = strlen(s + 1);
        m = strlen(t + 1);
        init();
        for (i = 1; i <= m; ++i) {
            m1 = i, m2 = m - i;
            for (j = 1; j <= m1; ++j) {
                t1[j] = t[j];
            }

            for (j = 1; j <= m2; ++j) {
                t2[j] = t[j + m1];
            }

            if (check()) {
                printf("YES\n");
                ok = 1;
                break;
            }
        }

        if (!ok) {
            printf("NO\n");
        }
    }
    return 0;
}