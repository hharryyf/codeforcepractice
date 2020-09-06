#include <bits/stdc++.h>
#define MAX_SIZE 200111
using namespace std;
typedef long long ll;
const ll mod = 998244353;

ll fac[MAX_SIZE], inv[MAX_SIZE];

ll C(int n, int k) {
    // cout << fac[n] << " " << inv[k] << " " << inv[n-k] << endl;
    return (((fac[n] * inv[k]) % mod) * inv[n-k]) % mod;
}

ll fastpower(ll base, ll p) {
    ll ret = 1;
    while (p > 0) {
        if (p % 2 == 1) {
            ret = ret * base;
            ret %= mod;
            --p;
        } else {
            base = base * base;
            base %= mod;
            p /= 2;
        }
    }
    return ret;
}

int main() {
    int i;
    fac[0] = inv[0] = 1;
    for (i = 1; i < MAX_SIZE; ++i) {
        fac[i] = fac[i-1] * i;
        fac[i] %= mod;
        inv[i] = fastpower(fac[i], mod - 2);
    }

    int n, k;
    ll sign = 1, ans = 0;
    scanf("%d%d", &n, &k);
    if (k >= n) {
        printf("0\n");
        return 0;
    }
    for (i = n - k; i >= 1; --i) {
        ll curr = C(n - k, i) * fastpower(i, n) * sign;
        // cout << C(n, i) << " n= " << n << " i= " << i << endl;
        sign = sign * (-1);
        ans = ans + curr;
        ans %= mod;
    }

    ans = ans * C(n, n - k);

    if (k > 0) {
        ans = ans * 2;
        ans %= mod;
    }

    cout << ((ans + mod) % mod) << endl;
    return 0;
}