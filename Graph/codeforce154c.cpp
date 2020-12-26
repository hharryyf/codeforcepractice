#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2,fma") 
#include <bits/stdc++.h>
#define MAX_SIZE 1000011
typedef long long ll;
using namespace std;

vector<int> g[MAX_SIZE];
ll pw[MAX_SIZE][2];
const ll mod1 = 100010441, mod2 = 19260817;
const ll base = 1000011;
map<pair<ll, ll>, int> cnt;
int N;

int main() {
    int m, i;
    scanf("%d%d", &N, &m);
    pw[0][0] = pw[0][1] = 1;
    for (i = 1; i <= N; ++i) {
        pw[i][0] = pw[i-1][0] * base;
        pw[i][0] %= mod1;
        pw[i][1] = pw[i-1][1] * base;
        pw[i][1] %= mod2;
    }

    for (i = 1; i <= m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (i = 1; i <= N; ++i) {
        ll tol1 = 0, tol2 = 0;
        for (auto v : g[i]) {
            tol1 = tol1 + pw[v][0];
            tol1 %= mod1;
            tol2 = tol2 + pw[v][1];
            tol2 %= mod2;
        } 
        cnt[make_pair(tol1, tol2)]++;
    }

    long long ans = 0;
    for (auto iter : cnt) {
        ans = ans + 1ll * iter.second * (iter.second - 1) / 2;
    }

    cnt.clear();

    for (i = 1; i <= N; ++i) {
        if (!g[i].empty()) {
            ll tol1 = pw[i][0], tol2 = pw[i][1];
            for (auto v : g[i]) {
                tol1 = tol1 + pw[v][0];
                tol1 %= mod1;
                tol2 = tol2 + pw[v][1];
                tol2 %= mod2;
            } 
            cnt[make_pair(tol1, tol2)]++;
        }
    }

    for (auto iter : cnt) {
        ans = ans + 1ll * iter.second * (iter.second - 1) / 2;
    }
    cout << ans << endl;
    return 0;
}