#include <bits/stdc++.h>
#define MAX_SIZE 1011
using namespace std;

char st[MAX_SIZE][MAX_SIZE];
bool visited[MAX_SIZE][MAX_SIZE];
int row[MAX_SIZE], col[MAX_SIZE];
int n, m;

void dfs(int x, int y) {
    if (x <= 0 || y <= 0 || x  > n || y > m) return;
    if (visited[x][y] || st[x][y] == '.') return;
    visited[x][y] = true;
    dfs(x-1, y);
    dfs(x +1, y);
    dfs(x, y-1);
    dfs(x, y + 1);
}

int main() {
    int i, ans = 0, j;
    scanf("%d%d", &n, &m);    
    for (i = 1; i <= n; ++i) {
        scanf("%s", st[i] + 1);
    }

    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= m; ++j) {
            if (st[i][j] == '#' && !visited[i][j]) {
                dfs(i, j);
                ++ans;
            }

            if (st[i][j] == '#') {
                row[i] = 1, col[j] = 1;
            }
        }
    }

    for (i = 1; i <= n; ++i) {
        bool flag = false, flag2 = false;
        for (j = 1; j <= m; ++j) {
            if (st[i][j] == '#' && flag2) {
                printf("-1\n");
                return 0;
            }

            if (st[i][j] == '#') {
                flag = true;
            }

            if (flag && st[i][j] == '.') {
                flag2 = true;
            }
        }
    }

    for (i = 1; i <= m; ++i) {
        bool flag = false, flag2 = false;
        for (j = 1; j <= n; ++j) {
            if (st[j][i] == '#' && flag2) {
                printf("-1\n");
                return 0;
            }

            if (st[j][i] == '#') {
                flag = true;
            }

            if (flag && st[j][i] == '.') {
                flag2 = true;
            }
        }
    }

    for (i = 1; i <= n; ++i) {
        if (!row[i]) {
            bool flag = false;
            for (j = 1; j <= m; ++j) {
                if (!col[j]) {
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                printf("-1\n");
                return 0;
            }
        }
    }

    for (i = 1; i <= m; ++i) {
        if (!col[i]) {
            bool flag = false;
            for (j = 1; j <= n; ++j) {
                if (!row[j]) {
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                printf("-1\n");
                return 0;
            }
        }
    }   

    printf("%d\n", ans);
    return 0;
}