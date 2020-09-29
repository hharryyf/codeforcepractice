#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<ll> prime;

const ll mod = 998244353;

vector<int> fac(ll v) {
    vector<int> ret(prime.size());
    int i = 0;
    for (auto p : prime) {
        int curr = 0;
        while (v % p == 0) {
            v = v / p;
            ++curr;
        }
        ret[i] = curr;
        ++i;
    }
    return ret;
} 

ll fc[72], ivt[72];

ll fastpower(ll val, ll p) {
    ll ret = 1, base = val;
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

void init() {
    fc[0] = 1, ivt[0] = 1;
    int i;
    for (i = 1; i < 72; ++i) {
        fc[i] = fc[i-1] * i;
        fc[i] %= mod;
        ivt[i] = ivt[i-1] * fastpower(i, mod - 2);
        ivt[i] %= mod;
    }
}

ll solve(vector<int> &src, vector<int> &target) {
    ll ret = 1;
    int i, tol = 0, sz = src.size();
    for (i = 0 ; i < sz; ++i) {
        ret = ret * ivt[src[i] - target[i]];
        ret %= mod;
        tol += src[i] - target[i];
    }

    // cout << "tol= " << tol << endl;
    ret = ret * fc[tol];
    ret %= mod;
    return ret;
}

int main() {
    ll D;
    init();
    scanf("%I64d", &D);
    for (auto i = 2; i <= sqrt(D); ++i) {
        if (D % i == 0) {
            prime.push_back(i);
            while (D % i == 0) D /= i;  
        }
    }

    if (D > 1) prime.push_back(D);
    int q;
    scanf("%d", &q);
    while (q-- > 0) {
        ll u, v;
        scanf("%I64d%I64d", &u, &v);
       // the path is any shortest path from u->gcd(u, v)->v
        auto f1 = fac(u), f = fac(__gcd(u, v)), f2 = fac(v);
        ll v1 = solve(f1, f), v2 = solve(f2, f);
        ll ans = v1 * v2;
        ans %= mod;
        printf("%I64d\n", ans);
    }
    return 0;
}