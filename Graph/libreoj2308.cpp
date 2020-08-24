#include <bits/stdc++.h>
#define MAX_SIZE 111
typedef long long ll;
using namespace std;

const ll inf = 1e13;
ll T[MAX_SIZE][MAX_SIZE], income[MAX_SIZE][MAX_SIZE];
ll dist[MAX_SIZE][MAX_SIZE];
ll S[MAX_SIZE][MAX_SIZE * 10], B[MAX_SIZE][MAX_SIZE * 10];
int n;

bool check(ll curr) {
    int i, j, p;
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= n; ++j) {
            if (T[i][j] < inf) {
                dist[i][j] = income[i][j] - curr * T[i][j];
            } else {
                dist[i][j] = -inf; 
            }
        }
    }

    for (p = 1; p <= n; ++p) {
        for (i = 1; i <= n; ++i) {
            for (j = 1; j <= n; ++j) {
                dist[i][j] = max(dist[i][j], dist[i][p] + dist[p][j]);
            }
        }
    }

    for (i = 1; i <= n; ++i) {
        if (dist[i][i] >= 0) return true;
    }

    return false;
}

int main() {
    int i, j, m, k, p;
    scanf("%d%d%d", &n, &m, &k);
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= k; ++j) {
            scanf("%lld%lld", &B[i][j], &S[i][j]);
        }
    }

    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= n; ++j) {
            T[i][j] = inf;
        }
    }

    for (i = 1; i <= m; ++i) {
        int v1, v2;
        ll v;
        scanf("%d%d%lld", &v1, &v2, &v);
        T[v1][v2] = min(T[v1][v2], v);
    }

    for (p = 1; p <= n; ++p) {
        for (i = 1; i <= n; ++i) {
            for (j = 1; j <= n; ++j) {
                T[i][j] = min(T[i][j], T[i][p] + T[p][j]);
            }
        }
    }

    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= n; ++j) {
            for (p = 1; p <= k; ++p) {
                if (B[i][p] != -1 && S[j][p] != -1) {
                    income[i][j] = max(income[i][j], S[j][p] - B[i][p]);
                }
            }
        }
    }

    ll ans = 0, low = 0, high = 1e9;
    while (low <= high) {
        ll mid = low + (high - low) / 2;
        if (check(mid)) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    printf("%lld\n", ans);
    return 0;
}