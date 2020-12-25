#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const ll mod = 1e9 + 7;
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

ll inv_2;
ll N, M, ans = 0;

ll mul(ll v, ll u) {
    if (v > mod) {
        v %= mod;
    } 

    if (u > mod) {
        u %= mod;
    }
    return (v * u) % mod;
}

ll solve(ll x) {
    ll low = N / (x + 1) + 1, up = (x == 0 ? M : min(N / x, M));
    if (low > up) return 0;
    ll ret = 0;
    ret += mul(N, up - low + 1);
    ret %= mod;
    ret -= mul(mul(mul(low + up, up - low + 1), inv_2), x);
    ret %= mod;
    if (ret < 0) ret += mod;
    return ret;
}    

int main() {
    cin >> N >> M;
    inv_2 = inv(2);
    ll up = sqrt(N);
    for (ll i = 0; i <= up; ++i) {
        ans = ans + solve(i);
        if (i != 0 && N / i != i) {
            ans = ans + solve(N / i);
            ans = ans % mod;
        }
        ans = ans % mod;
    }
    cout << ans << endl;
    return 0;
}