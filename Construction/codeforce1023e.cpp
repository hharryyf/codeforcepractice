#include <bits/stdc++.h>
#define MAX_SIZE 511
using namespace std;

int n;
char st[9];

bool ok(int fx, int fy, int x, int y) {
    printf("? %d %d %d %d\n", fx, fy, x, y);
    fflush(stdout);
    scanf("%s", st);
    if (st[0] == 'Y') {
            return true;
    } else if (st[0] == 'B') {
            exit(0);
    }
    return false;
}

int dx[2] = {1, 0}, dy[2] = {0, 1};

int main() {
    int i;
    scanf("%d", &n);
    int x = 1, y = 1;
    vector<pair<int, int>> coord;
    coord.emplace_back(1, 1);
    while (abs(n - x) + abs(n - y) > n - 1) {
        for (i = 0 ; i < 2; ++i) {
            int tx = x + dx[i], ty = y + dy[i];
            if (tx >= 1 && tx <= n && ty >= 1 && ty <= n && abs(tx - n) + abs(ty - n) >= n - 1) {
                if (ok(tx, ty, n, n)) {
                    coord.emplace_back(tx, ty);
                    x = tx, y = ty;
                    break;
                }
            }
        }
    }
    
    vector<pair<int, int>> coord2;
    coord2.emplace_back(n, n);
    int px = n, py = n;
    while (px != x || py != y) {
        for (i = 1; i >= 0; --i) {
            int tx = px - dx[i], ty = py - dy[i];
            if (tx >= 1 && tx <= n && ty >= 1 && ty <= n && ok(1, 1, tx, ty)) {
                coord2.emplace_back(tx, ty);
                px = tx, py = ty;
                break;
            }
        }
    }

    coord2.pop_back();
    reverse(coord2.begin(), coord2.end());
    for (auto p : coord2) {
        coord.push_back(p);
    }

    printf("! ");
    for (i = 0 ; i < (int) coord.size() - 1; ++i) {
        if (coord[i+1].first - coord[i].first == 1) {
            putchar('D');
        } else {
            putchar('R');
        }
    }
    printf("\n");

    return 0;
}