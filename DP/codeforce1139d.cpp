#include <bits/stdc++.h>
#define MAX_SIZE 100011
typedef long long ll;
using namespace std;
const ll mod = 1e9 + 7;
ll dp[MAX_SIZE];
int visited[MAX_SIZE];
vector<int> divs[MAX_SIZE];
vector<int> pdiv[MAX_SIZE];
int n;

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
// calculate the number of elements that is no more than n and has gcd(v, f) = x
// <=> calculate the number of elements that is coprime with f / x and is no greater than n / x
int calc(int f, int x) {
    int up = n / x, ff = f / x;
    int ret = 0, sz = pdiv[ff].size(), i, j;
    for (i = 1 ; i < (1 << sz); ++i) {
        int curr = 1;
        for (j = 0 ; j < (int) pdiv[ff].size(); ++j) {
            if ((1 << j) & i) {
                curr = curr * pdiv[ff][j];
            }
        }

        int bit = __builtin_popcount(i);
        if (bit % 2 == 1) {
            ret += up / curr;
        } else {
            ret -= up / curr;
        }
    }
    return up - ret;
}

int main() {
    int i, j;
    scanf("%d", &n);       
    for (i = 1; i <= n; ++i) {
        for (j = 1; j * i <= n; ++j) {
            divs[i * j].push_back(i);
        }
    }

    for (i = 2; i <= n; ++i) {
        if (!visited[i]) {
            visited[i] = 1;
            for (j = 1; j * i <= n; ++j) {
                visited[i * j] = 1;
                pdiv[i * j].push_back(i);
            }
        }
    }

    dp[1] = 1;
    ll inv = fastpower(n, mod - 2);
    for (i = 2; i <= n; ++i) {
        dp[i] = 1;
        for (auto v : divs[i]) {
            if (v == i) {
                int cnt = n / v;
                ll coeff = (1ll - inv * cnt) % mod;
                coeff = fastpower(coeff, mod - 2);
                dp[i] *= coeff;
                dp[i] %= mod;
            } else {
                dp[i] += ((dp[v] * calc(i, v)) % mod * inv) % mod;
                dp[i] %= mod;
            }
        }
    }

    ll ans = 0;
    for (i = 1; i <= n; ++i) {
        ans += dp[i];
        ans %= mod;
    }

    ans = ans * inv;
    ans %= mod;
    if (ans < 0) ans += mod;
    cout << ans << endl;
    return 0;
}