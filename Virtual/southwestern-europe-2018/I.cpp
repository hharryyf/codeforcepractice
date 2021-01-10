#include <bits/stdc++.h>
#define MAX_SIZE 1011
using namespace std;

char st[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE];
int dx[8] = {1, 1, 1, 0, 0, -1, -1, -1}, dy[8] = {0, 1, -1, 1, -1, 0, 1, -1};
int N, M;
vector<pair<int, int>> curr;

int ok(int x, int y) {
    return x >= 1 && x <= N && y >= 1 && y <= M;
}

int val(int x, int y) {
    if (!ok(x, y)) return 0;
    return st[x][y] == '.';
}

int white(int x, int y) {
    int i, ret = 0;
    for (i = 0 ; i < 8; ++i) {
        int tx = x + dx[i], ty = y + dy[i];
        ret += val(tx, ty);
    }
    return ret;
}

void dfs(int x, int y) {
    visited[x][y] = 1;
    curr.emplace_back(x, y);
    int i;
    for (i = 0 ; i < 8; ++i) {
        int tx = dx[i] + x, ty = dy[i] + y;
        if (ok(tx, ty) && !visited[tx][ty] && st[tx][ty] == '#') {
            dfs(tx, ty);
        }
    }
}

bool isA(vector<pair<int, int>> &vc) {
    int cnt = 0, l = vc.back().second, r = vc.back().second;
    for (auto v : vc) {
        if (v.first == vc.back().first) {
            cnt++;
            l = min(l, v.second), r = max(r, v.second);
        }
    }

    // cout << l << " " << r << " " << cnt << endl;
    return (r - l + 1) != cnt;
}

bool isB(vector<pair<int, int>> &vc) {
    int cnt = 0, l = vc.back().first, r = vc.back().first;
    for (auto v : vc) {
        if (v.second == vc.back().second) {
            cnt++;
            l = min(l, v.first), r = max(r, v.first);
        }
    }
    return (r - l + 1) == cnt;
}

int main() {
    int i, j;
    scanf("%d%d", &M, &N);
    for (i = 1; i <= N; ++i) scanf("%s", st[i] + 1);
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= M; ++j) {
            if (white(i, j) == 8 && st[i][j] == '#') visited[i][j] = 1;
        }
    }
    dfs(1, 1);
    int A = 0, B = 0, C = 0;
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= M; ++j) {
            if (!visited[i][j] && st[i][j] == '#') {
                curr.clear();
                dfs(i, j);
                sort(curr.begin(), curr.end());
                if (isA(curr)) {
                    A++;
                } else if (isB(curr)) {
                    B++;
                } else {
                    C++;
                }
            }
        }
    }

    printf("%d %d %d\n", A, B, C);
    return 0;
}