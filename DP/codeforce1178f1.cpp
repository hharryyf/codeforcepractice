#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 511
using namespace std;
// f[i][j] total number of ways to color [i, j]

const ll mod = 998244353;

ll f[MAX_SIZE][MAX_SIZE];
int a[MAX_SIZE];

ll dfs(int l, int r) {
    // cout << l << " " << r << endl;
    if (l - r > 1) return 0;
    if (l >= r) return 1;
    if (f[l][r] != -1) return f[l][r];
    // since we firstly color the minimum color
    // let's think how to color it
    // it must cover [pl, pr] with pl <= t <= pr
    int t = l, i;
    for (i = l; i <= r; ++i) {
        if (a[t] > a[i]) t = i;
    }

    ll ansL = 0, ansR = 0;
    for (i = l; i <= t; ++i) {
        ansL = ansL + dfs(l, i-1) * dfs(i, t - 1);
        ansL %= mod;
    }

    for (i = t; i <= r; ++i) {
        ansR = ansR + dfs(t + 1, i) * dfs(i + 1, r);
        ansR %= mod;
    }
    // cout << ansL << " * " << ansR << endl;
    f[l][r] = (ansL * ansR) % mod;
    // cout << l << " " << r << " " << f[l][r] << endl;
    return f[l][r];
}

int main() {
    int n, i, j, v;
    scanf("%d%d", &n, &v);
    for (i = 1; i <= n; ++i) scanf("%d", &a[i]);
    a[0] = 1e9 + 7;
    for (i = 0 ; i < MAX_SIZE; ++i) {
        for (j = 0 ; j < MAX_SIZE; ++j) {
            f[i][j] = -1;
        }
    }

    for (i = 1; i < MAX_SIZE; ++i) {
        f[i][i] = 1; 
        f[i][i-1] = 1;
    }

    printf("%I64d\n", dfs(1, n));
    return 0;
} 