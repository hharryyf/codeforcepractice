#include <bits/stdc++.h>
#define MAX_SIZE 2011
typedef long long ll;
using namespace std;

const ll mod = 1e9 + 7;
ll dp[MAX_SIZE];
pair<int, int> a[MAX_SIZE];
ll fac[MAX_SIZE * 100];

ll fastpower(ll v, ll p) {
    ll base = v, ret = 1;
    while (p > 0) {
        if (p % 2 == 0) {
            base = base * base;
            base %= mod;
            p /= 2;
        } else {
            ret = ret * base;
            ret %= mod;
            p--;
        }
    }
    return ret;
}

ll C(ll n, ll m) {
    if (n < m) return 0;
    return ((fac[n] * fastpower(fac[n - m], mod - 2)) % mod * fastpower(fac[m], mod - 2)) % mod;
}

int main() {
    int i, j, h, w, n;
    scanf("%d%d%d", &h, &w, &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d%d", &a[i].first, &a[i].second);
    }
    
    fac[0] = 1;
    for (i = 1; i <= h + w; ++i) {
        fac[i] = fac[i-1] * i;
        fac[i] %= mod;
    }

    sort(a + 1, a + 1 + n);
    a[n + 1].first = h, a[n + 1].second = w;
    ++n;
    for (i = 1; i <= n; ++i) {
        dp[i] = C(a[i].first + a[i].second - 2, a[i].first - 1);
        for (j = 1; j < i; ++j) {
            if (a[i].first < a[j].first || a[i].second < a[j].second) continue;
            dp[i] -= dp[j] * C(a[i].first - a[j].first + a[i].second - a[j].second, a[i].first - a[j].first);
            dp[i] %= mod;
        }
    }

    printf("%I64d\n", (dp[n] + mod) % mod);
    return 0;
}