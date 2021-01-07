#include <bits/stdc++.h>
#define MAX_SIZE 122
using namespace std;

int visited[MAX_SIZE][MAX_SIZE];
char board[MAX_SIZE][MAX_SIZE];
int N, M;
int dx[4] = {1, 0, 0, -1}, dy[4] = {0, 1, -1, 0};

bool ok(int x, int y) {
    if (x <= 0 || y <= 0 || x > N || y > M || visited[x][y] || board[x][y] == '#') return false;
    return true;
}

set<string> win;
set<pair<int, int>> curr;

void putin() {
    if (curr.empty()) return;
    int ux = curr.begin()->first, uy = curr.begin()->second;
    int dx = curr.rbegin()->first, dy = curr.rbegin()->second;
    vector<vector<char>> ini = vector<vector<char>>(dx - ux + 1, vector<char>(dy - uy + 1, '.'));
    set<string> version;
    int i, j;
    string ss;
    for (i = 0; i < dx - ux + 1; ++i) {
        for (j = 0 ; j < dy - uy + 1; ++j) {
            ini[i][j] = board[i + ux][j + uy];
        }
    } 
    // version 1
    ss = "";
    for (i = 0 ; i < dx - ux + 1; ++i) {
        for (j = 0 ; j < dy - uy + 1; ++j) {
            ss += ini[i][j];
        }
    }

    version.insert(ss);
    ss = "";
    for (i = dx - ux; i >= 0; --i) {
        for (j = dy - uy; j >= 0; --j) {
            ss += ini[i][j];
        }
    }

    version.insert(ss);

    if (dx - ux == dy - uy) {
        ss = "";
        for (i = dy - uy; i >= 0; --i) {
            for (j = 0; j <= dx - ux; ++j) {
                ss += ini[j][i];
            }
        }

        version.insert(ss);

        ss = "";
        for (i = 0; i <= dy - uy; ++i) {
            for (j = dx - ux; j >= 0; --j) {
                ss += ini[j][i];
            }
        }

        version.insert(ss);
    }

    win.insert(*version.begin());
}

void dfs(int x, int y) {
    int i;
    visited[x][y] = 1;
    curr.insert(make_pair(x, y));
    for (i = 0 ; i < 4; ++i) {
        int tx = dx[i] + x, ty = dy[i] + y;
        if (ok(tx, ty)) {
            dfs(tx, ty);
        }
    }
}

int main() {
    int i, j;
    scanf("%d%d", &N, &M);
    for (i = 1; i <= N; ++i) {
        scanf("%s", board[i] + 1);
    }

    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= M; ++j) {
            if (ok(i, j)) {
                curr.clear();
                dfs(i, j);
                putin();
            }
        }
    }    

    printf("%d\n", (int) win.size());
    return 0;
}