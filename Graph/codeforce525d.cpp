#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 2011
using namespace std;

char g[MAX_SIZE][MAX_SIZE];
int n, m;
queue<pair<int, int>> q;

int val(int x, int y) {
    return g[x][y] == '*';
}

pair<int,int> check(int x, int y) {
    if (x <= 1 || y <= 1 || x > n || y > m) return make_pair(-1, -1);
    if (val(x-1, y-1) + val(x-1, y) + val(x, y-1) + val(x, y) == 1) {
        if (val(x-1, y-1)) {
            return make_pair(x-1, y-1);
        }

        if (val(x-1, y)) {
            return make_pair(x-1, y);
        }

        if (val(x, y-1)) {
            return make_pair(x, y-1);
        }

        return make_pair(x, y);
    }

    return make_pair(-1, -1);
}

int main() {
    int i, j;
    scanf("%d%d", &n, &m);    
    for (i = 1; i <= n; ++i) scanf("%s", g[i]+1);

    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= m; ++j) {
            if (check(i, j).first != -1) {
                q.push(make_pair(i, j));
            }
        }
    }

    while (!q.empty()) {
        auto p = q.front();
        auto cd = check(p.first, p.second);
        q.pop();
        if (cd.first != -1) {
            g[cd.first][cd.second] = '.';
            // cout << "eliminate " << cd.first << " " << cd.second << endl;
        } else {
            continue;
        }

        int x = cd.first, y = cd.second;
        for (i = 0; i <= 1; ++i) {
            for (j = 0; j <= 1; ++j) {
                auto p = check(x+i, y+j);
                if (p.first != -1) {
                    q.push(make_pair(x+i, y+j));
                }
            }
        }
    }

    for (i = 1; i <= n; ++i) {
        printf("%s\n", g[i]+1);
    }
    return 0;
}