#include <bits/stdc++.h>
#define MAX_SIZE 1011
using namespace std;

struct edge {
    int from, to;
};

int sz[MAX_SIZE], f[MAX_SIZE];
edge edg[MAX_SIZE * 100];
int n, m, k;

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int a = find(x), b = find(y);
    if (a == b) return;
    if (sz[a] < sz[b]) swap(a, b);
    sz[a] += sz[b];
    f[b] = a;
}

int a[MAX_SIZE];

int main() {
    int i;
    scanf("%d%d%d", &n, &m, &k);
    for (i = 1; i <= n; ++i) {
        f[i] = i;
        sz[i] = 1;
    }

    for (i = 1; i <= k; ++i) scanf("%d", &a[i]);

    for (i = 1; i <= m; ++i) {
        scanf("%d%d", &edg[i].from, &edg[i].to);
        unionset(edg[i].from, edg[i].to);
    }

    

    int mx = sz[find(a[1])], id = a[1], ss = 0;
    for (i = 1; i <= k; ++i) {
        ss += sz[find(a[i])];
        if (mx < sz[find(a[i])]) {
            mx = sz[find(a[i])];
            id = a[i];
        }
    }

    sz[find(id)] += n - ss;
    long long ans = 0;
    for (i = 1; i <= k; ++i) {
        ss = sz[find(a[i])];
        ans += 1ll * ss * (ss - 1) / 2;
    }

    ans -= m;
    printf("%I64d\n", ans);
    return 0;
}