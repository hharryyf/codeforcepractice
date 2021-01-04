#include <bits/stdc++.h>
#define MAX_SIZE 1011
#define MAXQ 100011
using namespace std;

struct qrs {
    // tp = 0, do nothing
    // tp = 1, insert at (x, y)
    // tp = 2, delete at (x, y)
    // tp = 3, invert
    int x, y, tp;  
};

qrs q[MAXQ];
vector<int> g[MAXQ];
int lz[MAX_SIZE], cnt[MAX_SIZE];
int book[MAX_SIZE][MAX_SIZE], ans[MAXQ];
int tol = 0, Q, N, M;
// set (x, y) to val
void update(int x, int y, int val, int id) {
    if ((lz[x] ^ book[x][y]) == val) {
        q[id].tp = 0;
        return;
    }
    cnt[x] += val - (lz[x] ^ book[x][y]);
    tol += val - (lz[x] ^ book[x][y]);
    book[x][y] ^= 1;
}

void invert(int x) {
    tol += M - cnt[x] - cnt[x];
    cnt[x] = M - cnt[x];
    lz[x] ^= 1;
}

void dfs(int v) {
    if (q[v].tp == 1) {
        update(q[v].x, q[v].y, 1, v);
    } else if (q[v].tp == 2) {
        update(q[v].x, q[v].y, 0, v);
    } else if (q[v].tp == 3) {
        invert(q[v].x);
    }

    // cout << "update " << v << " -> " << tol << endl;
    ans[v] = tol;
    for (auto nv : g[v]) {
        dfs(nv);
    }

    if (q[v].tp == 1) {
        update(q[v].x, q[v].y, 0, v);
    } else if (q[v].tp == 2) {
        update(q[v].x, q[v].y, 1, v);
    } else if (q[v].tp == 3) {
        invert(q[v].x);
    }

    // cout << "withdraw " << v << " -> " << tol << endl; 
}

int main() {
    int i, id = 0;
    scanf("%d%d%d", &N, &M, &Q);
    for (i = 1; i <= Q; ++i) {
        scanf("%d", &q[i].tp);
        if (q[i].tp == 1) {
            scanf("%d%d", &q[i].x, &q[i].y);
        } else if (q[i].tp == 2) {
            scanf("%d%d", &q[i].x, &q[i].y);
        } else if (q[i].tp == 3) {
            scanf("%d", &q[i].x);
        } else {
            scanf("%d", &id);
        }

        g[id].push_back(i);
        id = i;
    }

    dfs(0);

    for (i = 1; i <= Q; ++i) {
        printf("%d\n", ans[i]);
    }
    return 0;
}