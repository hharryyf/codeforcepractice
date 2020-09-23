#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 100011
typedef long long ll;
using namespace std;
const ll mod = 1e9 + 7;

ll c[MAX_SIZE][103];
ll pre[MAX_SIZE][103];
ll curr[MAX_SIZE][103];
ll a[MAX_SIZE];
void init() {
    int i, j;
    for (i = 0 ; i < MAX_SIZE; ++i) c[i][0] = 1;
    for (j = 1 ; j <= 102; ++j) {
        for (i = j ; i < MAX_SIZE; ++i) {
            c[i][j] = c[i-1][j] + c[i-1][j-1];
            c[i][j] %= mod;
        }
    }
}


int main() {
    init();
    int i, j, k, l, r, n, m;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i) scanf("%I64d", &a[i]);
    while (m-- > 0) {
        scanf("%d%d%d", &l, &r, &k);
        curr[l][k+1] += 1;
        curr[l][k+1] %= mod;
        for (j = k + 1; j > 0; --j) {
            curr[r+1][j] = curr[r+1][j] - c[k - j + r - l + 1][k - j + 1];
            curr[r+1][j] %= mod;
        }
    }

    for (i = 101; i >= 0; --i) {
        for (j = 1; j <= n; ++j) {
            pre[j][i] += pre[j-1][i] + pre[j][i+1];
            pre[j][i] %= mod;
        }

        for (j = 1; j <= n; ++j) {
            pre[j][i] += curr[j][i];
            pre[j][i] %= mod;
        }
    }

    for (i = 1; i <= n; ++i) {
        pre[i][0] += a[i];
        pre[i][0] %= mod;
        pre[i][0] += mod;
        pre[i][0] %= mod;
    }

    for (i = 1; i <= n; ++i) {
        printf("%I64d ", pre[i][0]);
    }
    return 0;
}