#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const ll mod = 1e9 + 7;
ll dp[10011][65], inv[65];
ll N;
int K;
map<ll, int> cnt;
ll fastpower(ll val, ll p) {
    ll ret = 1;
    while (p > 0) {
        if (p % 2 == 1) {
            ret = ret * val;
            ret %= mod;
            p--;
        } else {
            val = val * val;
            val %= mod;
            p /= 2;
        }
    }

    return ret;
}

ll solve(int p, ll prime) {
    int i, j, k;
    memset(dp, 0, sizeof(dp));
    dp[0][p] = 1;
    for (i = 1; i <= K; ++i) {
        for (j = 0; j <= p; ++j) {
            for (k = j; k <= p; ++k) {
                dp[i][j] += dp[i-1][k] * inv[k+1];
                dp[i][j] %= mod;
            }
        }
    }

    ll ret = 0;
    for (i = 0; i <= p; ++i) {
        ret = ret + dp[K][i] * fastpower(prime, i);
        ret = ret % mod;
    }

    if (ret < 0) ret += mod;
    return ret;
}


int main() {
    int i;
    scanf("%I64d%d", &N, &K);
    for (i = 1; i < 65; ++i) {
        inv[i] = fastpower(i, mod - 2);
    }

    ll sz = sqrt(N);
    for (i = 2; i <= (int) sz; ++i) {
        while (N % i == 0) {
            cnt[i]++;
            N = N / i;
        }
    }

    if (N > 1) cnt[N]++;
    ll ans = 1;
    for (auto e : cnt) {
        ans = ans * solve(e.second, e.first);
        ans = ans % mod;
    }

    printf("%I64d\n", ans);
    return 0;
}