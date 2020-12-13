#include <bits/stdc++.h>
#define MAX_SIZE 200111
typedef long long ll;
using namespace std;

const ll mod = 1e9 + 7;
vector<int> g[MAX_SIZE];
ll dp[MAX_SIZE][2], f[MAX_SIZE][2], a[MAX_SIZE];
ll ans = 0;
int sz[MAX_SIZE];
int N;

void dfs1(int v, int p) {
    dp[v][0] = 1;
    sz[v] = 1;
    for (auto nv : g[v]) {
        if (nv != p) {
            dfs1(nv, v);
            dp[v][0] += dp[nv][1];
            dp[v][1] += dp[nv][0];
            sz[v] += sz[nv];
        }
    }

    for (auto nv : g[v]) {
        if (nv != p) {
            ans += (dp[nv][1] * (sz[v] - sz[nv])) % mod * a[v] % mod;
            //cout << "nxt= " << nv << " ans= " << ans << endl; 
            ans -= (dp[nv][0] * (sz[v] - sz[nv])) % mod * a[v] % mod;
            //cout << "nxt= " << nv << " ans= " << ans << endl; 
            //ans += ((dp[v][0] - dp[nv][1]) * sz[nv]) % mod * a[v] % mod;
            //cout << "nxt= " << nv << " ans= " << ans << endl; 
            //ans -= ((dp[v][1] - dp[nv][0]) * sz[nv]) % mod * a[v] % mod;
            //cout << "nxt= " << nv << " ans= " << ans << endl; 
            ans %= mod;
        }
    }

    ans += a[v] * (sz[v] - 1);
    ans %= mod;
    // cout << v << " --> " << ans << endl;
}

void dfs2(int v, int p) {
    for (auto nv : g[v]) {
        if (nv != p) {
            f[nv][0] += f[v][1];
            f[nv][1] += f[v][0];
            f[nv][0] += dp[v][1] - dp[nv][0];
            f[nv][1] += dp[v][0] - dp[nv][1];
            ans += (((f[nv][0] * sz[nv]) % mod) * a[nv]) % mod;
            ans -= (((f[nv][1] * sz[nv]) % mod) * a[nv]) % mod;
            ans += (((dp[nv][0] * (N - sz[nv])) % mod) * a[nv]) % mod;
            ans -= (((dp[nv][1] * (N - sz[nv])) % mod) * a[nv]) % mod;
            //ans += a[nv] * (N - sz[nv]) % mod;
            ans %= mod;
            dfs2(nv, v);
        }
    }
}



int main() {
    int i;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%I64d", &a[i]);
        ans = ans + a[i];
        ans %= mod;
    }
    for (i = 0 ; i < N - 1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs1(1, 0);
    //ans /= 2;
    dfs2(1, 0);
    ans = (ans % mod + mod) % mod;
    printf("%I64d\n", ans);
    return 0;
}