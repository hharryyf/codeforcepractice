#include <bits/stdc++.h>
#define MAX_SIZE 1048592
using namespace std;

int n;
int depth[MAX_SIZE], f[MAX_SIZE][21];

int query(int u, int v) {
    int i;
    if (depth[u] < depth[v]) swap(u, v);
    int ret = 0;
    for (i = 20; i >= 0; --i) {
        if (depth[u] >= (1 << i) + depth[v]) {
            u = f[u][i];
            ret += (1 << i);
        }
    }

    if (u == v) return ret;

    for (i = 20; i >= 0; --i) {
        if (f[v][i] != f[u][i]) {
            u = f[u][i], v = f[v][i];
            ret += (1 << i) * 2;
        }
    }

    return ret + 2;
}

int main() {
    n = 4;
    f[2][0] = f[3][0] = f[4][0] = 1;
    depth[2] = depth[3] = depth[4] = 1;
    int q, i, v1 = 2, v2 = 4;
    int ans = 2;
    scanf("%d", &q);
    while (q-- > 0) {
        int v;
        scanf("%d", &v);
        // add n+1, n+2 to v's child
        f[n+1][0] = v;
        f[n+2][0] = v;
        depth[n+1] = depth[n+2] = depth[v] + 1;
        for (i = 1; i <= 20; ++i) {
            f[n+1][i] = f[f[n+1][i-1]][i-1];
        }

        for (i = 1; i <= 20; ++i) {
            f[n+2][i] = f[f[n+2][i-1]][i-1];
        }
        // property of tree diameter
        // every vertex's furthest point is on the diameter of the tree        
        int ret = query(n+1, v1);
        if (ret > ans) {
            ans = ret;
            v2 = n + 1;
        }

        ret = query(n + 1, v2);
        if (ret > ans) {
            ans = ret;
            v1 = n + 1;
        }

        n += 2;
        printf("%d\n", ans);
    }
    return 0;
}