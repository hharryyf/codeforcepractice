#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll mod = 1e9 + 7;

ll mul(ll v1, ll v2) {
    v1 %= mod;
    v2 %= mod;
    return (v1 * v2) % mod;
}

ll add(ll v1, ll v2) {
    v1 %= mod;
    v2 %= mod;
    return (v1 + v2) % mod;
}

ll calc(ll r) {
    if (r == 0) return 0;
    ll idx = 0, odd = 1, even = 2, sm = 0, step = 0;
    while (idx < r) {
        if (idx + (1ll << step) <= r) {
            if (step % 2 == 1) {
                // (even + even + 2 * (1 << step - 1)) * step / 2
                // = (even + (1 << step - 1)) * (1 << step)
                sm = add(sm, mul(1ll << step, add(even, (1ll << step) - 1)));
                even = add(even, 1ll << (step + 1));
            } else {
                // (odd + odd + 2 * (1 << step - 1)) * step / 2
                // 
                sm = add(sm, mul(1ll << step, add(odd, (1ll << step) - 1)));
                odd = add(odd, 1ll << (step + 1));
            }
            idx += 1ll << step;
            step++;
        } else {
            ll sz = r - idx;
            if (step % 2 == 1) {
                sm = add(sm, mul(sz, add(even, (sz - 1))));
            } else {
                sm = add(sm, mul(sz, add(odd, (sz - 1))));
            }
            break;
        }
    }
    return sm % mod;
}

int main() {
    ll l, r;
    cin >> l >> r;
    //cout << calc(l) << endl;
    // cout << calc(r) << endl;
    cout << ((calc(r) - calc(l-1)) % mod + mod) % mod << endl;
    return 0;
}