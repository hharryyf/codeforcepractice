#include <bits/stdc++.h>
#define MAX_SIZE 2011
using namespace std;

char st[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE];
int deg[MAX_SIZE][MAX_SIZE];
int dx[4] = {1, 0, 0, -1}, dy[4] = {0, 1, -1, 0};
int n, m;

int main() {
    int i,j;
    scanf("%d%d", &n, &m);
    for (i = 0 ; i < n; ++i) {
        scanf("%s", st[i]);
    }

    for (i = 0 ; i < n; ++i) {
        for (j = 0 ; j < m; ++j) {
            if (j < m - 1 && st[i][j] == '.' && st[i][j+1] == '.') {
                ++deg[i][j], ++deg[i][j+1];
            }

            if (i < n - 1 && st[i][j] == '.' && st[i+1][j] == '.') {
                ++deg[i][j], ++deg[i+1][j];
            }
        }
    }

    queue<pair<int, int>> q;
    for (i = 0 ; i < n; ++i) {
        for (j = 0 ; j < m; ++j) {
            if (deg[i][j] == 1) {
                q.push(make_pair(i, j));
                // cout << "push in " << i << " " << j << endl;
            }
        }    
    }

    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        if (visited[p.first][p.second]) continue;
        bool match = false;
        visited[p.first][p.second] = 1;
        for (i = 0 ; i < 4; ++i) {
            int tx = dx[i] + p.first, ty = dy[i] + p.second;
            if (tx < 0 || tx >= n || ty < 0 || ty >= m) continue;
            if (visited[tx][ty] || st[tx][ty] != '.') continue;
            visited[tx][ty] = 1;
            match = true;
            // match tx, ty with p.first, p.second
            if (p.first == tx && p.second < ty) {
                st[tx][p.second] = '<', st[tx][ty] = '>';
            } else if (p.first == tx) {
                st[tx][ty] = '<', st[tx][p.second] = '>';
            } else if (p.second == ty && p.first < tx) {
                st[p.first][ty] = '^', st[tx][ty] = 'v';
            } else {
                st[p.first][ty] = 'v', st[tx][ty] = '^';
            }
            for (j = 0; j < 4; ++j) {
                int x = tx + dx[j], y = ty + dy[j];
                if (x < 0 || x >= n || y < 0 || y >= m) continue;
                if (visited[x][y] || st[x][y] != '.') continue;
                --deg[x][y];
                if (deg[x][y] == 1) {
                    q.push(make_pair(x, y));
                }
            } 
            break;
        }

        if (!match) {
            printf("Not unique\n");
            // cout << "no matching!" << " " << p.first << " " << p.second << endl;
            return 0;
        }
    }

    for (i = 0 ; i < n; ++i) {
        for (j = 0 ; j < m; ++j) {
            if (st[i][j] == '.') {
                printf("Not unique\n");
                return 0;
            }
        }
    }
    for (i = 0 ; i < n; ++i) {
        for (j = 0 ; j < m; ++j) {
            putchar(st[i][j]);
        }
        putchar('\n');
    }

    return 0;
}