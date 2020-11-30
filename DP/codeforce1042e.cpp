#include <bits/stdc++.h>
#define MAX_SIZE 1011
typedef long long ll;
using namespace std;

const ll mod = 998244353;
ll dp[MAX_SIZE][MAX_SIZE];
int a[MAX_SIZE][MAX_SIZE];
ll invs[MAX_SIZE * MAX_SIZE];
int n, m;
ll tolx, toly, tolx2, toly2, toldp;
map<int, vector<pair<int, int>>> mp;

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



int main() {
    int i, j, sx, sy;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= m; ++j) {
            scanf("%d", &a[i][j]);
            mp[a[i][j]].emplace_back(i, j);
        }
    }

    for (i = 1; i <= n * m; ++i) {
        invs[i] = fastpower(i, mod - 2);
    }

    scanf("%d%d", &sx, &sy);
    int sz = 0;
    for (auto &iter : mp) {
        if (sz != 0) {
            ll inv = invs[sz];
            for (auto &e : iter.second) {
                dp[e.first][e.second] += tolx2;
                dp[e.first][e.second] += toly2;
                dp[e.first][e.second] += 1ll * e.first * e.first * sz;
                dp[e.first][e.second] += 1ll * e.second * e.second * sz;
                dp[e.first][e.second] += toldp;
                dp[e.first][e.second] -= (tolx * e.first * 2);
                dp[e.first][e.second] -= (toly * e.second * 2);
                dp[e.first][e.second] %= mod;
                dp[e.first][e.second] *= inv;
                dp[e.first][e.second] %= mod;
                if (dp[e.first][e.second] < 0) dp[e.first][e.second] += mod;
            }
        }

        for (auto &e : iter.second) {
            tolx += e.first, toly += e.second, tolx2 += 1ll * e.first * e.first;
            toly2 += 1ll * e.second * e.second, toldp += dp[e.first][e.second];
            tolx %= mod, toly %= mod, tolx2 %= mod, toly2 %= mod, toldp %= mod;
        }

        sz += (int) iter.second.size();
    }    
    

    printf("%I64d\n", dp[sx][sy]);
    return 0;
}