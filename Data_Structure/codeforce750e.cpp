#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 524292
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
#define MID ((l+r)>>1)
using namespace std;

struct segt {
    int cost[5][5];
};

segt tree[MAX_SIZE];
char st[MAX_SIZE >> 1];

segt pullup(segt t1, segt t2) {
    segt ret;
    int i, j, k;
    for (i = 0 ; i < 5; ++i) {
        for (j = 0 ; j < 5; ++j) {
            ret.cost[i][j] = MAX_SIZE;
            for (k = 0 ; k < 5; ++k) {
                ret.cost[i][j] = min(ret.cost[i][j], t1.cost[i][k] + t2.cost[k][j]);
            }
        }
    }
    return ret;
}

void build(int l, int r, int index) {
    int i, j;
    if (l > r) return;
    if (l == r) {
        for (i = 0; i < 5; ++i) {
            for (j = 0 ; j < 5; ++j) {
                tree[index].cost[i][j] = (i != j) * MAX_SIZE;
            }
        }

        if (st[l] == '2') {
            tree[index].cost[0][1] = 0, tree[index].cost[0][0] = 1;
        } else if (st[l] == '0') {
            tree[index].cost[1][2] = 0, tree[index].cost[1][1] = 1;
        } else if (st[l] == '1') {
            tree[index].cost[2][3] = 0, tree[index].cost[2][2] = 1;
        } else if (st[l] == '7') {
            tree[index].cost[3][4] = 0, tree[index].cost[3][3] = 1;
        } else if (st[l] == '6') {
            tree[index].cost[3][3] = 1, tree[index].cost[4][4] = 1;
        }
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    tree[index] = pullup(tree[LEFT], tree[RIGHT]);
}

segt query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return tree[0];
    if (start <= l && r <= end) return tree[index];
    if (end <= MID) return query(start, end, l, MID, LEFT);
    if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT);
    return pullup(query(start, end, l, MID, LEFT), query(start, end, MID + 1, r, RIGHT));
}

int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    scanf("%s", st + 1);
    build(1, n, 1);
    while (q-- > 0) {
        int l, r;
        scanf("%d%d", &l, &r);
        auto ret = query(l, r, 1, n, 1);
        if (ret.cost[0][4] >= MAX_SIZE) {
            printf("-1\n");
        } else {
            printf("%d\n", ret.cost[0][4]);
        }
    }
    return 0;
}