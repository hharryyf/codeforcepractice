#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 511
using namespace std;

int sz[MAX_SIZE * MAX_SIZE], f[MAX_SIZE * MAX_SIZE];
int cnt[MAX_SIZE * MAX_SIZE];
int black[MAX_SIZE][MAX_SIZE];
char g[MAX_SIZE][MAX_SIZE];
int n, m;
int curr = 0;

int idx(int x, int y) {
    return n * (x - 1) + y;
}

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int a = find(x), b = find(y);
    if (a == b) return;
    if (sz[a] < sz[b]) {
        f[a] = b;
        sz[b] += sz[a];
    } else {
        f[b] = a;
        sz[a] += sz[b];
    }
}

int dx[4] = {0, 0, -1, 1}, dy[4] = {1, -1, 0, 0};

void add(int x, int y) {
    if (x <= 0 || x > n || y <= 0 || y > n || g[x][y] == 'X') return;
    cnt[find(idx(x, y))]++;
    if (cnt[find(idx(x, y))] == 1) curr += sz[find(idx(x, y))];
}

void del(int x, int y) {
    if (x <= 0 || x > n || y <= 0 || y > n || g[x][y] == 'X') return;
    cnt[find(idx(x, y))]--;
    if (cnt[find(idx(x, y))] == 0) curr -= sz[find(idx(x, y))];
}

void rebuild(int r) {
    int i, j;
    memset(cnt, 0, sizeof(cnt));
    curr = 0;
    for (i = r - 1; i <= r + m; ++i) {
        for (j = 1; j <= 1 + m; ++j) {
            if (i == r - 1 && j == m + 1) continue;
            if (i == r + m && j == m + 1) continue;
            add(i, j);
        }
    }
}

// shift the square from (r, c) to (r, c + 1)
void rightshift(int r, int c) {
    int i;
    for (i = r; i <= r + m - 1; ++i) del(i, c - 1);
    del(r - 1, c);
    del(r + m, c);
    add(r - 1, c + m);
    add(r + m, c + m);
    for (i = r; i <= r + m - 1; ++i) add(i, c + m + 1);
}

 // #define WRONGANSWER
int query(int r, int c) {
    int ret = curr + black[r+m-1][c+m-1] + black[r-1][c-1] - black[r+m-1][c-1] - black[r-1][c+m-1];
    #ifdef WRONGANSWER
    printf("(%d, %d)= %d, curr= %d\n", r, c, ret, curr);
    #endif
    return ret;
}

int main() {
    int i, j, ans = 0, k;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i) {
        scanf("%s", g[i]+1);
    }

    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= n; ++j) {
            f[idx(i, j)] = idx(i, j);
            if (g[i][j] == '.') {
                sz[idx(i, j)] = 1;
            }

            black[i][j] = black[i-1][j] + black[i][j-1] - black[i-1][j-1] + (g[i][j] == 'X');
        }
    }

    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= n; ++j) {
            for (k = 0 ; k < 4; ++k) {
                if (g[i][j] == 'X') continue;
                int ti = i + dx[k], tj = j + dy[k];
                if (ti > n || tj > n || ti <= 0 || tj <= 0 || g[ti][tj] == 'X') continue;
                unionset(idx(i, j), idx(ti, tj));
            }
        }
    }

    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= n; ++j) {
            if (find(idx(i, j)) == idx(i, j)) {
                ans = max(ans, sz[idx(i, j)]);
            }
        }
    }

    // Now comes the fun part, we do a line sweep from left to right in each row
    for (i = 1; i <= n - m + 1; ++i) {
        rebuild(i);
        ans = max(ans, query(i, 1));
        for (j = 1; j <= n - m; ++j) {
            rightshift(i, j);
            ans = max(ans, query(i, j + 1));
        }
    }

    printf("%d\n", ans);
    return 0;
}