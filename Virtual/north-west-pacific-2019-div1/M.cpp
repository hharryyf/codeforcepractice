#include <bits/stdc++.h>
#define MAX_SIZE 4111111
using namespace std;

int f[MAX_SIZE];

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int a = find(x), b = find(y);
    f[a] = b;
}

int R, C;
char st[1011][1011];

int idx(int x, int y) {
    return (x - 1) * 2011 + y;
} 

int main() {
    int i, j, cnt = 0;
    scanf("%d%d", &R, &C);
    for (i = 0 ; i < MAX_SIZE; ++i) f[i] = i;
    for (i = 1; i <= R; ++i) scanf("%s", st[i] + 1);
    for (i = 1; i <= R; ++i) {
        for (j = 1; j <= C; ++j) {
            if (st[i][j] == '/') {
                if (find(idx(2 * i - 1, 2 * j + 1)) != find(idx(2 * i + 1, 2 * j - 1))) {
                    unionset(idx(2 * i - 1, 2 * j + 1), idx(2 * i + 1, 2 * j - 1));
                } else {
                    cnt++;
                }
            } else if (st[i][j] == '\\') {
                if (find(idx(2 * i - 1, 2 * j - 1)) != find(idx(2 * i + 1, 2 * j + 1))) {
                    unionset(idx(2 * i - 1, 2 * j - 1), idx(2 * i + 1, 2 * j + 1));
                } else {
                    cnt++;
                }
            }
        }
    }

    printf("%d\n", cnt);
    return 0;
}