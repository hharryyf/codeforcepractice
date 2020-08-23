#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;
#define WRONGANSWER
int f[MAX_SIZE * 12];
char g[MAX_SIZE][12];
int N, M;
int block_size = 1;
int coord[MAX_SIZE][2], critical[MAX_SIZE * 12];
char op[MAX_SIZE], dir[MAX_SIZE], st[4];

int idx(int x, int y) {
    return x * (M + 2) + y;
}

int find(int x, int y) {
    int id = idx(x, y);
    int nid = id;
    int tx = x, ty = y;
    if (x == N + 1 || y == M + 1 || x == 0 || y == 0) {
        f[id] = id;
        return f[id];
    }
    if (f[id] != -1) return f[id];
    if (g[x][y] == '<') {
        nid = id - 1;
        ty--;
    } else if (g[x][y] == '>') {
        nid = id + 1;
        ty++;
    } else {
        nid = id - (M + 2);
        tx--;
    }

    if (g[x][y] == '>' && g[tx][ty] == '<') {
        f[id] = nid;
    } else if (g[x][y] == '<' && g[tx][ty] == '>') {
        f[id] = nid;
    } else {
        if (critical[idx(tx, ty)]) {
            f[id] = nid;
        } else {
            f[id] = find(tx, ty);
        }
    }

    #ifndef WRONGANSWER
    cout << "id= " << id << " parent= " << f[id] << endl;
    #endif
    return f[id];
}

int trace(int id) {
    #ifndef WRONGANSWER
    cout << "trace id= " << id << " parent= " << f[id] << endl;
    #endif
    if (f[id] == id) return id;
    if (f[f[id]] == id) return -2;
    return trace(f[id]);
}

void update(int x, int y, char ch) {
    g[x][y] = ch;
    int id = idx(x, y);
    if (ch == '<') {
        f[id] = id - 1;
    } else if (ch == '>') {
        f[id] = id + 1;
    } else {
        f[id] = id - (M + 2);
    }
}

int main() {
    int q, i, j, k;
    scanf("%d%d%d", &N, &M, &q);
    for (i = 1; i <= N; ++i) scanf("%s", g[i]+1);

    block_size = sqrt(N * M);
    for (i = 0; i < q; ++i) {
        int L = i * block_size, R = min(q - 1, L + block_size - 1);
        if (L > R) break;
        for (j = L; j <= R; ++j) {
            scanf("%s%d%d", st, &coord[j][0], &coord[j][1]);
            op[j] = st[0];
            if (st[0] == 'C') {
                scanf("%s", st);
                dir[j] = st[0];
                critical[idx(coord[j][0], coord[j][1])] = 1;
            }
        }

        memset(f, -1, sizeof(f));
        for (j = 0 ; j <= N + 1; ++j) {
            for (k = 0; k <= M + 1; ++k) {
                if (f[idx(j, k)] == -1) {
                    f[idx(j, k)] = find(j, k);
                }
            }
        }

        for (j = L; j <= R; ++j) {
            if (op[j] == 'C') {
                update(coord[j][0], coord[j][1], dir[j]);
                critical[idx(coord[j][0], coord[j][1])] = 0;
            } else {
                int ret = trace(idx(coord[j][0], coord[j][1]));
                if (ret == -2) {
                    printf("-1 -1\n");
                } else {
                    int x = ret / (M + 2), y = ret % (M + 2);
                    printf("%d %d\n", x, y);
                }
            }
        }
    }
    return 0;
}