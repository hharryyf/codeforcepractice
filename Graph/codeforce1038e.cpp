#include <bits/stdc++.h>
using namespace std;

vector<int> g[4][4];
int tol[4][4];
int in[4], f[4], deg[4];
int idx[10][2] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {1, 1}, {1, 2}, {1, 3}, {2, 2}, {2, 3}, {3, 3}}; 
// mask = 0  --> select none edge
// mask = 1 --> select all but 1 edge
// mask = 2 --> select all edges

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void unionset(int u, int v) {
    int x = find(u), y = find(v);
    f[x] = y;
}

int calc(int mask) {
    int i = 0, cost = 0, j;
    vector<int> bit(10);
    while (mask > 0) {
        bit[i++] = mask % 3;
        mask /= 3;
    }

    for (i = 0; i < 4; ++i) {
        in[i] = deg[i] = 0;
        f[i] = i;
    }

    for (i = 0 ; i < 10; ++i) {
        int x = idx[i][0], y = idx[i][1];
        if (bit[i] == 1) {
            int sz = (int) g[x][y].size() - 1;
            if (sz <= 0) return -1;
            cost += tol[x][y] - g[x][y].front();
            sz = 2 - (sz & 1);
            for (j = 0 ; j < sz; ++j) {
                deg[x]++, deg[y]++;
                in[x] = in[y] = 1;
                unionset(x, y);
            }
        } else if (bit[i] == 2) {
            int sz = (int) g[x][y].size();
            if (sz == 0) return -1;
            sz = 2 - (sz & 1);
            cost += tol[x][y];
            for (j = 0 ; j < sz; ++j) {
                deg[x]++, deg[y]++;
                in[x] = in[y] = 1;
                unionset(x, y);
            }
        }
    }

    int cnt = 0, idx = -1;
    for (i = 0 ; i < 4; ++i) {
        cnt += (deg[i] & 1);
        if (in[i] != 0) idx = i;
    }

    for (i = 0 ; i < 4; ++i) {
        if (idx != -1 && in[i] && find(idx) != find(i)) return -1;
    }

    if (cnt > 2) return -1;
    return cost;
}

int main() {
    int n, i, j;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        int c1, c2, v;
        scanf("%d%d%d", &c1, &v, &c2);
        if (c1 > c2) swap(c1, c2);
        c1--, c2--;
        g[c1][c2].push_back(v);
    }

    for (i = 0; i < 4; ++i) {
        for (j = i; j < 4; ++j) {
            sort(g[i][j].begin(), g[i][j].end());
            for (auto v : g[i][j]) {
                tol[i][j] += v;
            }
        }
    }

    int ans = 0;
    for (i = 0 ; i < 59049; ++i) {
        ans = max(ans, calc(i));
    }

    printf("%d\n", ans);
    return 0;
}