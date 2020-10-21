#include <bits/stdc++.h>
#define MAX_SIZE 100011
typedef long long ll;
using namespace std;

char st[MAX_SIZE];
ll fac[MAX_SIZE];
ll pre[MAX_SIZE], p[MAX_SIZE];
const ll mod = 1e9 + 7;
ll ans;

ll inv(ll v) {
    ll ret = 1, p = mod - 2;
    while (p > 0) {
        if (p % 2 == 0) {
            v = v * v;
            v %= mod;
            p /= 2;
        } else {
            ret = ret * v;
            ret %= mod;
            p--;
        }
    }
    return ret;
}

ll C(int n, int k) {
    return ((fac[n] * inv(fac[k])) % mod * inv(fac[n-k])) % mod;
}

int main() {
    int i, n, k;
    scanf("%d%d", &n, &k);
    scanf("%s", st + 1);
    p[0] = fac[0] = 1;
    for (i = 1; i < MAX_SIZE; ++i) fac[i] = (fac[i-1] * i) % mod;
    for (i = 1; i < MAX_SIZE; ++i) p[i] = (p[i-1] * 10) % mod;
    for (i = 0; i < MAX_SIZE; ++i) {
        if (n - i - 2 >= k - 1) {
            pre[i] =  p[i] * C(n - i - 2, k - 1);
            if (i > 0) pre[i] += pre[i-1];
            pre[i] %= mod;
        } else {
            pre[i] = pre[i-1];
        }
    }   
/*
    for (i = 0; i <= n; ++i) {
        cout << pre[i] << endl;
    }*/
    for (i = 1; i <= n; ++i) {
        //cout << "Add " << n - 1 - i << endl;
        if (n - 1 - i >= 0) {
            ans = ans + pre[n - 1 - i] * (st[i] - '0');
        }
        //cout << "ans= " << ans << endl;
        ans %= mod;
        if (i - 1 >= k) {
            ans = ans + C(i - 1, k) * p[n - i] * (st[i] - '0');
        } 
        ans %= mod;
    }

    printf("%I64d\n", ans);
    return 0;
}