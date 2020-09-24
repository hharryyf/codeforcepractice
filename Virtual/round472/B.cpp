#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

char st[55][55];
int n, m;
int f[111];
char g[55][55];

int find(int x) {
    if (x == f[x]) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    x = find(x), y = find(y);
    f[x] = y;
}

vector<int> ss[111];

int main() {
    int i, j;
    scanf("%d%d", &n, &m);
    for (i = 0 ; i < n; ++i) {
        scanf("%s", st[i]);
    }

    for (i = 0 ; i < n + m; ++i) f[i] = i;

    for (i = 0 ; i < n; ++i) {
        for (j = 0 ; j < m; ++j) {
            if (st[i][j] == '#') {
                unionset(i, j + n);
            }
            g[i][j] = '.';
        }
    }

    for (i = 0 ; i < n + m; ++i) {
        ss[find(i)].push_back(i);
    }

    for (i = 0 ; i < n + m; ++i) {
        if ((int) ss[i].size() <= 1) continue;
        vector<int> row;
        vector<int> col;
        for (auto v : ss[i]) {
            if (v < n) row.push_back(v);
            else {
                col.push_back(v - n);
            }
        }

        for (auto v : row) {
            for (auto nv : col) {
                g[v][nv] = '#';
            }
        }
    }

    for (i = 0; i < n; ++i) {
        for (j = 0 ; j < m; ++j) {
            if (g[i][j] != st[i][j]) {
                printf("No\n");
                return 0;
            }
        }
    }

    printf("Yes\n");
    return 0;
}