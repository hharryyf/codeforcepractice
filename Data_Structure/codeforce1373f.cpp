#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 1000011
typedef long long ll;
using namespace std;

int n;
ll a[MAX_SIZE], b[MAX_SIZE];
ll c[MAX_SIZE], d[MAX_SIZE];
// the total amount of items given by b[1] to a[1]
int fail(ll x) {
    int i;
    for (i = 1; i <= n; ++i) c[i] = a[i], d[i] = b[i];
    c[1] -= x;
    d[1] -= x;
    for (i = 1; i < n; ++i) {
        // d[i] gives to c[i+1]
        // d[i+1] gives to c[i+1]
        c[i+1] = max(0ll, c[i+1] - d[i]);
        if (d[i+1] < c[i+1]) return -1; 
        d[i+1] -= c[i+1];
        c[i+1] = 0;
    }

    if (d[n] >= c[1]) return 0;
    return 1;
}

int main() {
    int T, i;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d", &n);
        for (i = 1; i <= n; ++i) {
            scanf("%I64d", &a[i]);
        }

        for (i = 1; i <= n; ++i) {
            scanf("%I64d", &b[i]);
        }

        ll low = 0, high = min(a[1], b[1]);
        bool ok = false;
        while (low <= high) {
            ll mid = (low + high) / 2;
            int ret = fail(mid);
            if (ret == -1) {
                // giving too much to a[1], such that the middle breaks down
                high = mid - 1;
            } else if (ret == 1) {
                // giving too less to a[1], such that a[1] fails
                low = mid + 1;
            } else {
                ok = true;
                printf("YES\n");
                break;
            }
        }

        if (!ok) {
            printf("NO\n");
        }
    }

    return 0;
}