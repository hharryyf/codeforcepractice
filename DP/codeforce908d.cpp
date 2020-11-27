#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const ll mod = 1e9 + 7;
#define MAX_SIZE 1011
ll fastpower(ll val, ll p) {
    ll ret = 1;
    while (p > 0) {
        if (p % 2 == 0) {
            val = val * val;
            val %= mod;
            p /= 2;
        } else {
            ret = ret * val;
            ret %= mod;
            p--;
        }
    }
    return ret;
}

ll pa, pb;
int k;
// dp[i][j] = probability of j ab sequences and i a.
ll dp[MAX_SIZE][MAX_SIZE];

ll mul(ll v, ll u) {
    return (v * u) % mod;
}

int main() {
    ll a, b;
    int i, j;
    cin >> k >> a >> b;
    pa = mul(a, fastpower(a + b, mod - 2)), pb = mul(b, fastpower(a + b, mod - 2));
    // cout << pa << endl;
    dp[0][0] = mul(pb, fastpower(pa, mod - 2));
    dp[1][0] = pa;
    for (i = 0; i < k; ++i) {
        for (j = 0; i + j < k; ++j) {
            if (i != 0 || i + j != 0) {
                dp[i][i + j] += mul(dp[i][j], pb);
                dp[i][i + j] %= mod;
            }
            dp[i+1][j] += mul(dp[i][j], pa);
            dp[i+1][j] %= mod;
        }
    }

    ll ans = 0;
    ll v = mul(pa, fastpower(pb, mod - 2));
    for (i = 0 ; i <= k; ++i) {
        for (j = 0; j <= k; ++j) {
            if (i + j >= k) {
                // ans += dp[i][j] * (pb * (j + i)  + pa * pb * ((j + i) + 1) + pa * pa * pb * (j + i + 2) + ...)
                // ans += dp[i][j] * pb * ((i+j) * (1 + pa + pa * pa + ...) + pa + 2 * pa * pa + ...)
                ans += mul(dp[i][j], (i + j) + v);               
                ans %= mod;
            }
        }
    }

    cout << ((ans + mod) % mod) << endl;
    return 0;
}