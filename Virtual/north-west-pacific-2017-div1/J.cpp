#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 33
using namespace std;

char st[MAX_SIZE][MAX_SIZE];
int rb[MAX_SIZE], rr[MAX_SIZE];
ll dp[MAX_SIZE][MAX_SIZE];
int N, M;

int main() {
    int i, j, k;
    scanf("%d%d", &N, &M);
    for (i = 1; i <= N; ++i) scanf("%s", st[i] + 1);
    if (st[1][1] == 'R') {
        for (i = 1; i <= N; ++i) {
            for (j = 1; j <= M; ++j) {
                if (st[i][j] == 'B') {
                    printf("0\n");
                    return 0;
                }
            }
        }

        printf("1\n");
        return 0;
    }

    for (i = 1; i <= N; ++i) {
        rr[i] = M + 1;
        for (j = 1; j <= M; ++j) {
            if (st[i][j] == 'R') {
                rr[i] = j;
                break;
            }
        }

        for (j = M; j >= 1; --j) {
            if (st[i][j] == 'B') {
                rb[i] = j;
                break;
            }
        }
    }

    dp[0][M] = 1;
    ll ans = 0;
    for (i = 1; i <= N; ++i) {
        for (j = rb[i]; j < rr[i]; ++j) {
            for (k = j; k <= M; ++k) {
                dp[i][j] += dp[i-1][k];
            }
        }
    }

    for (i = 0 ; i <= M; ++i) {
        ans += dp[N][i];
    }
    cout << ans << endl;
    return 0;
}