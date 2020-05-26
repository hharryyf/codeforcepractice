#include <bits/stdc++.h>
#define MAX_SIZE 511
using namespace std;

int g[MAX_SIZE][MAX_SIZE];
int color[MAX_SIZE];
vector<int> rg[MAX_SIZE];
int visited[MAX_SIZE];
char ans[MAX_SIZE];
bool valid = true;
void dfs(int v) {
    visited[v] = 1;
    for (auto nv : rg[v]) {
        if (color[nv] != 0 && color[nv] == color[v]) {
            valid = false;
        }
        
        color[nv] = color[v] == 1 ? 2 : 1;

        if (!visited[nv]) {
            dfs(nv);
        }
    }
}

int main() {
    int i, j, n, m;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; ++i) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        g[v1][v2] = 1, g[v2][v1] = 1;
    }

    for (i = 1; i <= n; ++i) {
        for (j = i + 1; j <= n; ++j) {
            if (g[i][j] == 0) {
                rg[i].push_back(j);
                rg[j].push_back(i);
            }
        }
    }
    for (i = 1; i <= n; ++i) {
        if (visited[i] == 0 && !rg[i].empty()) {
            color[i] = 1;
            dfs(i);
        }
    }

    if (!valid) {
        printf("No\n");
        return 0;
    }

    for (i = 1; i <= n; ++i) {
        if (color[i] == 0) {
            ans[i] = 'b';
        } else if (color[i] == 1) {
            ans[i] = 'a';
        } else {
            ans[i] = 'c';
        }
    }

    for (i = 1; i <= n; ++i) {
        for (j = i + 1; j <= n; ++j) {
            if (g[i][j] && abs(ans[i] - ans[j]) > 1) {
                printf("No\n");
                return 0;
            }

            if (!g[i][j] && abs(ans[i] - ans[j]) <= 1) {
                printf("No\n");
                return 0;
            }
        }
    }

    printf("Yes\n");
    for (i = 1; i <= n; ++i) {
        printf("%c", ans[i]);
    }
    printf("\n");
    return 0;
}