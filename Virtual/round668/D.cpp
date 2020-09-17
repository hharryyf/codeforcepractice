#include <bits/stdc++.h>
#define MAX_SIZE 100111
using namespace std;
typedef long long ll;

vector<int> g[MAX_SIZE];
int N, a, b, da, db;
int d1[MAX_SIZE], d2[MAX_SIZE];

void init() {
    int i;
    for (i = 0 ; i <= N; ++i) {
        g[i].clear();
        d1[i] = d2[i] = 0;
    }
}

void dfs1(int v, int pre, int h = 0) {
    d1[v] = h;
    for (auto nv : g[v]) {
        if (nv != pre) {
            dfs1(nv, v, h + 1);
        }
    }
}


void dfs2(int v, int pre, int h = 0) {
    d2[v] = h;
    for (auto nv : g[v]) {
        if (nv != pre) {
            dfs2(nv, v, h + 1);
        }
    }
}

int main() {
    int T, i;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d%d%d%d%d", &N, &a, &b, &da, &db);
        init();
        for (i = 0 ; i < N - 1; ++i) {
            int x, y;
            scanf("%d%d", &x, &y);
            g[x].push_back(y);
            g[y].push_back(x);
        }

        if (2 * da >= db) {
            printf("Alice\n");
        } else {
            // we check whether the diameter is greater or equal to 2 * a + 1
            // and Alice cannot eat Bob in one move
            dfs1(a, 0);
            if (d1[b] <= da) {
                printf("Alice\n");
            } else {
                int pt = a;
                for (i = 1; i <= N; ++i) {
                    if (d1[pt] <= d1[i]) pt = i;
                }

                dfs2(pt, 0);
                int d = 0;
                for (i = 1; i <= N; ++i) {
                    d = max(d, d2[i]);
                }

                if (d >= 2 * da + 1) {
                    printf("Bob\n");
                } else {
                    printf("Alice\n");
                }
            }
        }
    }
    return 0;
}