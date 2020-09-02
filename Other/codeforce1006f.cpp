#include <bits/stdc++.h>
#define MAX_SIZE 23
using namespace std;
typedef long long ll;
map<ll, ll> mp[MAX_SIZE][MAX_SIZE];
int n, m;
ll k;
ll g[MAX_SIZE][MAX_SIZE];
ll ans = 0;

void dfs1(int x, int y, int step, ll val) {
    if (x > n || y > m) return;
    if (x + y - 2 == step) {
        mp[x][y][val]++;
        return;
    }

    dfs1(x+1, y, step, val ^ g[x+1][y]);
    dfs1(x, y+1, step, val ^ g[x][y+1]);
}

void dfs2(int x, int y, int step, ll val) {
    if (x <= 0 || y <= 0) return;
    if (n + m - x - y == step) {
        ans += mp[x][y][val ^ k ^ g[x][y]];
        return;
    }
    
    dfs2(x-1, y, step, val ^ g[x-1][y]);
    dfs2(x, y-1, step, val ^ g[x][y-1]);
}

int main() {
    int i, j;
    scanf("%d%d%I64d", &n, &m, &k);
    for (i = 1 ; i <= n; ++i) {
        for (j = 1 ; j <= m; ++j) {
            scanf("%I64d", &g[i][j]);
        }
    }

    dfs1(1, 1, (n+m - 2) / 2, g[1][1]);
    dfs2(n,m,m + n - 2 - (n+m - 2) / 2,g[n][m]);
    printf("%I64d\n", ans);
    return 0;
}