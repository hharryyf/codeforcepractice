#include <bits/stdc++.h>
#define MAX_SIZE 400011
typedef long long ll;
using namespace std;
int L[MAX_SIZE], R[MAX_SIZE];
const ll mod = 1e9 + 7;
char st[MAX_SIZE];
ll fac[MAX_SIZE], inv[MAX_SIZE];
ll fastpower(ll v, ll p) {
    ll ret = 1;
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
    return ((fac[n] * inv[n-k]) % mod * inv[k]) % mod;
}

int main() {
    int i, N;
    ll ans = 0;
    scanf("%s", st + 1);
    N = strlen(st + 1);
    fac[0] = inv[0] = 1;
    for (i = 1; i < MAX_SIZE; ++i) {
        fac[i] = fac[i-1] * i;
        fac[i] %= mod;
        inv[i] = inv[i-1] * fastpower(i, mod - 2);
        inv[i] %= mod;
    }

    for (i = 1; i <= N; ++i) {
        L[i] = L[i-1] + (st[i] == '(');
    }

    for (i = N; i >= 1; --i) {
        R[i] = R[i+1] + (st[i] == ')');
    }

    for (i = 1; i <= N; ++i) {
        if (st[i] == '(' && R[i] > 0) {
            ans = ans + C(L[i] + R[i] - 1, L[i]); 
            ans %= mod;
        }
    }

    printf("%I64d\n", ans);
    return 0;
}