#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 2011
using namespace std;

int f[MAX_SIZE][MAX_SIZE];
int L[MAX_SIZE][MAX_SIZE];
int R[MAX_SIZE][MAX_SIZE];
int N, M;
int Q;
int block_size;

int find(int x, int dim) {
    if (f[dim][x] == x) return x;
    return f[dim][x] = find(f[dim][x], dim);
}

void unionset(int x, int y, int dim) {
    int a = find(x, dim), b = find(y, dim);
    f[dim][a] = b;
    L[dim][b] = min(L[dim][b], L[dim][a]);
    R[dim][b] = max(R[dim][b], R[dim][a]);
}

void update(int x, int y) {
    int a = find(y-1, x), b = find(y+1, x);
    L[x][y] = y - 1, R[x][y] = y + 1;
    if (R[x][a] == y) {
        unionset(y-1, y, x);
    }

    if (L[x][b] == y) {
        unionset(y, y + 1, x);
    }
}

void init() {
    int i, j;
    for (i = 1; i < MAX_SIZE; ++i) {
        for (j = 1; j < MAX_SIZE; ++j) {
            f[i][j] = j;
            L[i][j] = R[i][j] = j;
        }
    }
}

pair<int, int> check_row(int x, int y) {
    int i;
    int ansx = -1, ansy = -1;
    int tx = -1, ty = -1, dist = MAX_SIZE * MAX_SIZE;
    int fi = max(1, x - block_size - 1), se = min(x + block_size + 1, N);
    for (i = x; i >= fi; --i) {
        if (dist < x - i) break;
        tx = i, ty = MAX_SIZE * MAX_SIZE + MAX_SIZE;
        int v = find(y, i);
        if (L[i][v] > 0) ty = L[i][v];
        if (R[i][v] <= M && abs(R[i][v] - y) < abs(ty - y)) ty = R[i][v];
        int d = abs(tx - x) + abs(ty - y);
        if (dist > d || (dist == d && make_pair(ansx, ansy) >= make_pair(tx, ty))) {
            ansx = tx, ansy = ty, dist = d;
        }
    }

    for (i = x + 1; i <= se; ++i) {
        if (dist < i - x) break;
        tx = i, ty = MAX_SIZE * MAX_SIZE + MAX_SIZE;
        int v = find(y, i);
        if (L[i][v] > 0) ty = L[i][v];
        if (R[i][v] <= M && abs(R[i][v] - y) < abs(ty - y)) ty = R[i][v];
        int d = abs(tx - x) + abs(ty - y);
        if (dist > d || (dist == d && make_pair(ansx, ansy) >= make_pair(tx, ty))) {
            ansx = tx, ansy = ty, dist = d;
        }
    }

    return {ansx, ansy};
}

pair<int, int> check_col(int x, int y) {
    int i;
    int ansx = -1, ansy = -1;
    int tx = -1, ty = -1, dist = MAX_SIZE * MAX_SIZE;
    int fi = max(1, y - block_size - 1), se = min(y + block_size + 1, M);
    for (i = y; i >= fi; --i) {
        if (y - i > dist) break;
        ty = i, tx = MAX_SIZE * MAX_SIZE + MAX_SIZE;
        int v = find(x, i);
        if (L[i][v] > 0) tx = L[i][v];
        if (R[i][v] <= N && abs(R[i][v] - x) < abs(tx - x)) tx = R[i][v];
        int d = abs(tx - x) + abs(ty - y);
        if (dist > d || (dist == d && make_pair(ansx, ansy) >= make_pair(tx, ty))) {
            ansx = tx, ansy = ty, dist = d;
        }
    }

    for (i = y + 1; i <= se; ++i) {
        if (i - y > dist) break;
        ty = i, tx = MAX_SIZE * MAX_SIZE + MAX_SIZE;
        int v = find(x, i);
        if (L[i][v] > 0) tx = L[i][v];
        if (R[i][v] <= N && abs(R[i][v] - x) < abs(tx - x)) tx = R[i][v];
        int d = abs(tx - x) + abs(ty - y);
        if (dist > d || (dist == d && make_pair(ansx, ansy) >= make_pair(tx, ty))) {
            ansx = tx, ansy = ty, dist = d;
        }
    }

    return {ansx, ansy};
}

int main() {
    pair<int, int> ret;
    int x, y;
    scanf("%d%d%d", &N, &M, &Q);
    init();
    block_size = 2 * ceil(sqrt(Q));
    while (Q-- > 0) {
        scanf("%d%d", &x, &y);
        if (N > M) {
            ret = check_col(x, y);
        } else {
            ret = check_row(x, y);
        }

        printf("%d %d\n", ret.first, ret.second);
        if (N > M) swap(ret.first, ret.second);
        update(ret.first, ret.second);
    }
    return 0;
}