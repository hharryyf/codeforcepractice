#include <bits/stdc++.h>
#define MAX_SIZE 1000011
typedef long long ll;
using namespace std;
const ll mod = 1e9 + 7;
ll fac[MAX_SIZE], inv[MAX_SIZE];

/*
consider the first time a subsequence of length k occurs in the array of length n
and there are j elements at the end of that array, the contribution is
sum(sum(m^k*m^j*(m-1)^(n-k-j)*c(n-j-1, k-1), j = 0..n-k), k = 1..n)
use the substitution k+j = s, we get
sum(m^s*(m-1)^(n-s)*sum(c(n-j-1,s-j-1), j = 0..s-1), s = 1..n)
Note that sum(c(n-j-1,s-j-1), j = 0..s-1) = c(n,s-1) and we are done
*/
ll mul(ll v, ll u) {
    return (v * u) % mod;
}

ll add(ll u, ll v) {
    return u + v <= mod ? u + v : u + v - mod;    
}

int N, M;
ll fastpower(ll v, ll p) {
    ll ret = 1;
    while (p > 0) {
        if (p % 2 == 1) {
            ret = ret * v;
            ret %= mod;
            p--;
        } else {
            v = v * v;
            v %= mod;
            p /= 2;
        }
    }
    return ret;
}

ll C(int n, int k) {
    return mul(mul(fac[n], inv[k]),  inv[n-k]);
}

int main() {
    int i;
    fac[0] = inv[0] = 1;
    for (i = 1; i < MAX_SIZE; ++i) {
        fac[i] = mul(fac[i-1], i);
        inv[i] = mul(inv[i-1], fastpower(i, mod - 2));
    }

    scanf("%d%d", &N, &M);
    ll ans = fastpower(M, N);
    for (i = 1; i <= N; ++i) {
        ans = add(ans, mul(mul(fastpower(M, i), fastpower(M - 1, N - i)), C(N, i - 1)));
    }

    printf("%I64d\n", (ans % mod + mod) % mod);
    return 0;
}