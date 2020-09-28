#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 200011
using namespace std;
char st[63][63];
int rcnt[63], ccnt[63];

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int i, j, n, m, cnt = 0, side = 0;
        memset(rcnt, 0, sizeof(rcnt));
        memset(ccnt, 0, sizeof(ccnt));
        scanf("%d%d", &n, &m);
        for (i = 0 ; i < n; ++i) {
            scanf("%s", st[i]);
            for (j = 0 ; j < m; ++j) {
                if (st[i][j] == 'A') {
                    rcnt[i]++, ccnt[j]++, cnt++;
                    if (i == 0 || i == n - 1 || j == 0 || j == m - 1) side++;
                }
            }
        }

        if (cnt == 0) {
            printf("MORTAL\n");
            continue;
        }

        if (cnt == n * m) {
            printf("0\n");
            continue;
        }

        if (rcnt[0] == m || rcnt[n-1] == m || ccnt[0] == n || ccnt[m - 1] == n) {
            printf("1\n");
            continue;
        }

        if (st[0][m-1] == 'A' || st[n-1][m-1] == 'A' || st[n-1][0] == 'A' || st[0][0] == 'A') {
            printf("2\n");
            continue;
        }

        bool ok = false;
        for (i = 0 ; i < n; ++i) {
            if (rcnt[i] == m) {
                ok = true;
            }
        }

        for (i = 0 ; i < m; ++i) {
            if (ccnt[i] == n) {
                ok = true;
            }
        }

        if (ok) {
            printf("2\n");
            continue;
        }

        if (side) {
            printf("3\n");
        } else {
            printf("4\n");
        }

    }
    return 0;
}