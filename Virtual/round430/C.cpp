#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;
const int mx = 2e5;
vector<int> fac[MAX_SIZE];
vector<int> g[MAX_SIZE];
int a[MAX_SIZE];
int cnt[MAX_SIZE];
int ans[MAX_SIZE];
int n;

void dfs(int v, int pre, int d) {
    for (auto nv : fac[a[v]]) {
        ++cnt[nv];
        // cout << "add " << nv << endl;
        if (cnt[nv] >= d - 1) {
            ans[v] = max(ans[v], nv);
        }
    }

    if (pre) {
        for (auto nv : fac[a[pre]]) {
            if (cnt[nv] >= d - 1) {
                ans[v] = max(ans[v], nv);
            }            
        }
    }

    for (auto nv : g[v]) {
        if (nv != pre) {
            dfs(nv, v, d + 1);
        }
    }

    for (auto nv : fac[a[v]]) {
        --cnt[nv];
    }
}

int main() {
    int i, j;
    // memset(ans, 1, sizeof(ans));
    scanf("%d", &n);
    for (i = 1 ; i <= n; ++i) {
        scanf("%d", &a[i]);
    }

    for (i = 0 ; i < n - 1; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        g[x].push_back(y);
        g[y].push_back(x);
    }

    for (i = 1; i <= mx; ++i) {
        for (j = 1; j * i <= mx; ++j) {
            fac[i * j].push_back(i);
        }
    }

    dfs(1, 0, 1);
    for (i = 1; i <= n; ++i) {
        printf("%d ", ans[i]);
    }
    return 0;
}