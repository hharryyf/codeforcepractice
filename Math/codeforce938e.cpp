#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 1000011
typedef long long ll;
using namespace std;
const ll mod = 1e9 + 7;

ll fac[MAX_SIZE];
ll inv(ll p) {
    ll ret = 1, base = p, pw = mod - 2;
    while (pw > 0) {
        if (pw % 2 == 1) {
            ret = ret * base;
            ret %= mod;
            pw--;
        } else {
            base = base * base;
            base %= mod;
            pw /= 2;
        }
    }
    return ret;
}

ll C(int N, int K) {
    return (((fac[N] * inv(fac[K])) % mod) * inv(fac[N-K])) % mod;
}

map<int, int> mp;

int main() {
    int i, n;
    ll ans = 0;
    fac[0] = 1;
    scanf("%d", &n);
    for (i = 1; i < MAX_SIZE; ++i) fac[i] = fac[i-1] * i, fac[i] %= mod;
    for (i = 0 ; i < n; ++i) {
        int v;
        scanf("%d", &v);
        mp[v]++;
    }

    int cnt = 0;
    mp.erase(mp.rbegin()->first);
    for (auto iter : mp) {
        ans += (((C(n, cnt) * fac[n - cnt - 1]) % mod) * fac[cnt]) % mod * (iter.second * iter.first) % mod;
        ans %= mod;
        cnt += iter.second;
    }

    cout << ans << endl;
    return 0;
}