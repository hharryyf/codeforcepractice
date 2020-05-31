#include <bits/stdc++.h>
#define MAX_SIZE 511
using namespace std;

int g[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE];
int n;
vector<char> oper;

void dfs(int x, int y, char pmove) {
    visited[x][y] = 1;
    int i;
    if (g[x][y] == 0) {
        g[x][y] = 1;
        oper.push_back('1');
    }

    for (i = y + 1; i <= n; ++i) {
        if (g[x][i] == 1 && !visited[x][y+1]) {
            oper.push_back('R');
            dfs(x, y + 1, 'R');
            break;
        }
    }

    
    for (i = y - 1; i >= 1; --i) {
        if (g[x][i] == 1 && !visited[x][y-1]) {
            oper.push_back('L');
            dfs(x, y - 1, 'L');
            break;
        }
    }

    
    for (i = x + 1; i <= n; ++i) {
        if (g[i][y] == 1 && !visited[x+1][y]) {
            oper.push_back('D');
            dfs(x+1, y, 'D');
            break;
        }
    }

    for (i = x - 1; i >= 1; --i) {
        if (g[i][y] == 1 && !visited[x-1][y]) {
            oper.push_back('U');
            dfs(x - 1, y, 'U');
            break;
        }
    }

    if (g[x][y] == 1) {
        g[x][y] = 0;
        oper.push_back('2');
    }

    if (pmove == 'U') {
        oper.push_back('D');
    } else if (pmove == 'D') {
        oper.push_back('U');
    } else if (pmove == 'L') {
        oper.push_back('R');
    } else if (pmove == 'R') {
        oper.push_back('L');
    }
} 

int main() {
    int i, j, x, y;
    scanf("%d%d%d", &n, &x, &y);
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= n; ++j) {
            scanf("%d", &g[i][j]);
        }
    }

    dfs(x, y, '3');

    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= n; ++j) {
            if (g[i][j] == 1) {
                printf("NO");
                return 0;
            }
        }
    }

    printf("YES\n");
    for (auto c : oper) {
        putchar(c);
    }
    return 0;
}