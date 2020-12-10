#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MAX_SIZE 200011
const ll mod = 998244353;
ll prefix[MAX_SIZE];
int d[MAX_SIZE];

ll inv(ll v) {
    ll p = mod - 2, ret = 1;
    while (p > 0) {
        if (p % 2 == 0) {
            v = v * v;
            v %= mod;
            p /= 2;
        } else {
            ret = ret * v;
            p--;
            ret %= mod;
        }
    }

    return ret;
}

ll mul(ll u, ll v) {
    u %= mod, v %= mod;
    return (u * v) % mod;
}

int main() {
    int n, m, i;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i) scanf("%d", &d[i]);
    sort(d + 1, d + 1 + n);
    for (i = 1; i <= n; ++i) {
        prefix[i] = prefix[i-1] + d[i];
        prefix[i] %= mod;
    }
    while (m-- > 0) {
        int a, b;
        scanf("%d%d", &a, &b);
        int idx = lower_bound(d + 1, d + 1 + n, b) - d;
        int large = n - idx + 1;
        if (large < a) {
            printf("0\n");
            continue;
        }

        ll largecost = mul(prefix[n] - prefix[idx - 1], 1ll - mul(inv(large), a));
        ll smallcost = mul(prefix[idx-1], 1ll - mul(inv(large + 1), a));
        ll ans = (largecost + smallcost) % mod;
        if (ans < 0) ans += mod;
        printf("%I64d\n", ans);
    }
    return 0;
}