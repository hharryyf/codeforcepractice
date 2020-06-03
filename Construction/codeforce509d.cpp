#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 111
using namespace std;

ll g[MAX_SIZE][MAX_SIZE];
ll a[MAX_SIZE], b[MAX_SIZE];

int main() {
    int i, j, n, m;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= m; ++j) {
            scanf("%I64d", &g[i][j]);
        }
    }

    for (i = 1; i <= m; ++i) {
        b[i] = g[1][i];
    }

    ll k = 2e9;

    vector<ll> useful;
    for (i = 1; i <= m - 1; ++i) {
        vector<ll> dif;
        for (j = 1; j <= n; ++j) {
            dif.push_back(g[j][i+1] - g[j][i]);
        }

        sort(dif.begin(), dif.end());
        for (j = 0; j < (int) dif.size() - 1; ++j) {
            if (dif[j] != dif[j+1]) {
                k = min(k, dif[j + 1] - dif[j]);
            }
        }

        useful.push_back(k);
    }

    sort(useful.begin(), useful.end());

    for (i = 0 ; i < (int) useful.size() - 1; ++i) {
        if (useful[i+1] != useful[i]) {
            k = min(useful[i+1] - useful[i], k);
        }
    }
    for (i = 1; i <= n; ++i) {
        a[i] = ((g[i][1] - b[1]) % k + k) % k;
    }

    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= m; ++j) {
            if (g[i][j] != (a[i] + b[j]) % k) {
                printf("NO\n");
                return 0;
            }
        }
    }

    printf("YES\n");
    printf("%I64d\n", k);
    for (i = 1; i <= n; ++i) {
        printf("%I64d ", a[i]);
    }
    printf("\n");
    for (i = 1; i <= m; ++i) {
        printf("%I64d ", b[i]);
    }
    printf("\n");
    return 0;
}