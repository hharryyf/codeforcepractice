#include <bits/stdc++.h>
#define MAX_SIZE 1011
using namespace std;

char g[MAX_SIZE][MAX_SIZE];
int a[MAX_SIZE][MAX_SIZE];
int ok[MAX_SIZE][MAX_SIZE];
vector<pair<int, int>> vc[MAX_SIZE];
int ans[300011], Q, N;
int qx[300011][2], qy[300011][2], f[MAX_SIZE * MAX_SIZE];

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int v = find(x), u = find(y);
    f[v] = u;
}

// -> sum of the square centred (cx, cy) "radius" r
// (cx-r+1, cy-r+1) -> (cx+r-1, cy+r-1)
int query(int cx, int cy, int r) {
    if (cx - r + 1 <= 0 || cy - r + 1 <= 0 || cx + r - 1 > N || cy + r - 1 > N) return 0;
    return a[cx+r-1][cy+r-1] + a[cx-r][cy-r] - a[cx+r-1][cy-r] - a[cx-r][cy+r-1];
}

int idx(int x, int y) {
    return (x - 1) * N + y;
}

int main() {
    int i, j;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%s", g[i] + 1);
        for (j = 1; j <= N; ++j) {
            a[i][j] = a[i-1][j] + a[i][j-1] - a[i-1][j-1] + (g[i][j] == '.');
        }
    }

    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= N; ++j) {
            int low = 1, high = N, curr = 0;
            while (low <= high) {
                int mid = (low + high) / 2;
                if (query(i, j, mid) == (2 * mid - 1) * (2 * mid - 1)) {
                    curr = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }

            ok[i][j] = curr;
            f[idx(i, j)] = idx(i, j);
        }
    }
/*
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= N; ++j) {
            printf("%d ", ok[i][j]);
        }
        printf("\n");
    }
*/
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= N; ++j) {
            int curr = N;
            if (i + 1 <= N) {
                curr = min(curr, ok[i][j]);
                curr = min(curr, ok[i+1][j]);
                if (curr != 0) {
                    vc[curr].emplace_back(idx(i, j), idx(i+1, j));
                }
            }

            curr = N;
            if (j + 1 <= N) {
                curr = min(curr, ok[i][j]);
                curr = min(curr, ok[i][j+1]);
                if (curr != 0) {
                    vc[curr].emplace_back(idx(i, j), idx(i, j+1));
                }
            }
        }
    }
    scanf("%d", &Q);
    for (i = 1; i <= Q; ++i) {
        scanf("%d%d%d%d", &qx[i][0], &qy[i][0], &qx[i][1], &qy[i][1]);
    }

    for (j = N; j >= 1; --j) {
        if (vc[j].empty()) continue;
        for (auto v : vc[j]) {
            unionset(v.first, v.second);
        }

        for (i = 1; i <= Q; ++i) {
            if (find(idx(qx[i][0], qy[i][0])) == find(idx(qx[i][1], qy[i][1]))) {
                ans[i] = max(ans[i], j * 2 - 1);
            }
        }
    }

    for (i = 1; i <= Q; ++i) {
        printf("%d\n", ans[i]);
    }
    return 0;
}