#include <bits/stdc++.h>
#define MAX_SIZE 311
#define MAX_Q 2000011
using namespace std;

int g[MAX_SIZE][MAX_SIZE];
int n, m;
vector<pair<int, int>> add[MAX_Q], del[MAX_Q];
int f[MAX_SIZE * MAX_SIZE];
int ans[MAX_Q];
int tol = 1;

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int a = find(x), b = find(y);
    f[a] = b;
}

bool notsameset(int x, int y) {
    return find(x) != find(y);
}

int index(int x, int y) {
    return x * m + y;
}

int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};

void solve(vector<pair<int, int>> &qrs,  int tp) {
    int i, j;
    for (i = 0 ; i < n; ++i) {
        for (j = 0 ; j < m; ++j) {
            g[i][j] = 0;
        }
    }

    for (i = 0 ; i < n * m; ++i) f[i] = i;

    for (auto event : qrs) {
        int x = event.first / m, y = event.first % m;
        g[x][y] = 1;
        int delta = 1;
        for (i = 0 ; i < 4; ++i) {
            int tx = dx[i] + x, ty = dy[i] + y;
            if (tx >= 0 && tx < n && ty >= 0 && ty < m && g[tx][ty] == 1) {
                delta -= notsameset(index(x, y), index(tx, ty));
                unionset(index(x, y), index(tx, ty));
            }
        }

        ans[event.second] += delta * tp;
    }
}

int main() {
    int i, j, q;
    scanf("%d%d%d", &n, &m, &q);
    for (i = 0; i < q; ++i) {
        int x, y, c;
        scanf("%d%d%d", &x, &y, &c);
        x--, y--;
        if (g[x][y] == c) continue;
        tol = c + 1;
        add[c].emplace_back(index(x, y), i);
        del[g[x][y]].emplace_back(index(x, y), i);
        g[x][y] = c;
    }

    for (i = 0 ; i < n; ++i) {
        for (j = 0 ; j < m; ++j) {
            del[g[i][j]].emplace_back(index(i, j), q);
        }
    }

    for (i = 0 ; i < tol; ++i) {
        reverse(del[i].begin(), del[i].end());
    }

    for (i = 0 ; i < tol; ++i) {
        solve(add[i], 1);
    }

    for (i = 0 ; i < tol; ++i) {
        solve(del[i], -1);
    }

    tol = 1;
    for (i = 0 ; i < q; ++i) {
        tol += ans[i];
        printf("%d\n", tol);
    }
    return 0;
}