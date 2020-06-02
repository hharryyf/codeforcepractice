#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 2011
using namespace std;


int n, m, k;
// weight of each cell
int wt[MAX_SIZE][MAX_SIZE];
ll tree[MAX_SIZE][MAX_SIZE];
// (x[i][j], y[i][j]) position of the jth element in the ith garland
int x[MAX_SIZE][MAX_SIZE];
int y[MAX_SIZE][MAX_SIZE];
// the total number of elements in each garland
int len[MAX_SIZE];

ll ans[MAX_SIZE];
// active[i][j] means whether the jth garland is active for the ith query
int active[MAX_SIZE][MAX_SIZE];
int cnt[MAX_SIZE];
char st[12];

struct sqare {
    int x1, y1, x2, y2;
};

sqare sq[MAX_SIZE];

int shift(int x) {
    return x & (-x);
}

void update(int x, int y, int val) {
    if (x <= 0 || y <= 0) return;
    int i, j;
    for (i = x; i <= n; i += shift(i)) {
        for (j = y; j <= m; j += shift(j)) {
            tree[i][j] += val;
        }
    }
}

ll query(int x, int y) {
    ll ret = 0;
    int i, j;
    for (i = x; i > 0; i -= shift(i)) {
        for (j = y; j > 0; j -= shift(j)) {
            ret += tree[i][j];
        }
    }

    return ret;
}

int main() {
    int i, j;
    scanf("%d%d%d", &n, &m, &k);
    for (i = 1; i <= k; ++i) {
        scanf("%d", &len[i]);
        for (j = 1; j <= len[i]; ++j) {
            scanf("%d%d", &x[i][j], &y[i][j]);
            int w;
            scanf("%d", &w);
            wt[x[i][j]][y[i][j]] = w;
        }
        cnt[i] = 1;
    }

    int q = 0, Q;
    scanf("%d", &Q);
    while (Q > 0) {
        scanf("%s", st);
        if (st[0] == 'A') {
            ++q;
            for (i = 1; i <= k; ++i) {
                active[q][i] = cnt[i];
            }
            scanf("%d%d%d%d", &sq[q].x1, &sq[q].y1, &sq[q].x2, &sq[q].y2);
        } else {
            int id;
            scanf("%d", &id);
            cnt[id] ^= 1;
            
        }
        --Q;
    }

    for (i = 1; i <= k; ++i) {
        
        for (j = 1; j <= len[i]; ++j) {
            // single point update here
            update(x[i][j], y[i][j], wt[x[i][j]][y[i][j]]);
        }
        
        for (j = 1; j <= q; ++j) {
            if (active[j][i]) {
                // update ans[j]
                ans[j] += query(sq[j].x2, sq[j].y2) + query(sq[j].x1 - 1, sq[j].y1 - 1)
                         - query(sq[j].x1 - 1, sq[j].y2) - query(sq[j].x2, sq[j].y1 - 1);
            }
        }
        for (j = 1; j <= len[i]; ++j) {
            // single point update here, reverse
            update(x[i][j], y[i][j], -wt[x[i][j]][y[i][j]]);
        }
    }

    for (i = 1; i <= q; ++i) {
        printf("%I64d\n", ans[i]);
    }
    return 0;
}