#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
#define MAX_SIZE 2097312
using namespace std;

struct segt {
    int lmax, rmax, sm, ans, lb, rb;
};

segt tree[MAX_SIZE];
/*
    (R(R)R(R(R)R)R)
*/
void pullup(int l, int r, int index) {
    if (l >= r) return;
    int match = min(tree[LEFT].lb, tree[RIGHT].rb);
    tree[index].lb = tree[LEFT].lb + tree[RIGHT].lb - match;
    tree[index].rb = tree[LEFT].rb + tree[RIGHT].rb - match;
    tree[index].lmax = max(tree[LEFT].lmax, tree[LEFT].sm + tree[RIGHT].lmax);
    tree[index].rmax = max(tree[RIGHT].rmax, tree[RIGHT].sm + tree[LEFT].rmax);
    tree[index].sm = tree[LEFT].sm + tree[RIGHT].sm;
    tree[index].ans = max(tree[LEFT].ans, tree[RIGHT].ans);
    tree[index].ans = max(tree[index].ans, tree[LEFT].rmax + tree[RIGHT].lmax);
}

void update(int pt, int l, int r, int index, int val) {
    if (pt < l || pt > r || l > r) return;
    if (l == r) {
        tree[index].lmax = tree[index].ans = tree[index].rmax = tree[index].sm = val;
        if (val == 0) {
            tree[index].lb = tree[index].rb = 0;
        } else if (val == 1) {
            tree[index].lb = 1, tree[index].rb = 0;
        } else {
            tree[index].lb = 0, tree[index].rb = 1;
        }
        return;
    }

    if (pt <= MID) {
        update(pt, l, MID, LEFT, val);
    } else {
        update(pt, MID + 1, r, RIGHT, val);
    }

    pullup(l, r, index);
}

char st[MAX_SIZE];

int main() {
    int n, curr = 1, i;
    scanf("%d", &n);
    scanf("%s", st + 1);
    for (i = 1; i <= n; ++i) {
        if (st[i] == 'L') {
            if (curr > 1) {
                curr--;
            }
        } else if (st[i] == 'R') {
            curr++;
        } else if (st[i] == '(') {
            update(curr, 1, n+1, 1, 1);
        } else if (st[i] == ')') {
            update(curr, 1, n+1, 1, -1);
        } else {
            update(curr, 1, n+1, 1, 0);
        }
        if (tree[1].lb == 0 && tree[1].rb == 0) {
            printf("%d ", tree[1].ans);
        } else {
            printf("-1 ");
        }
    }
    return 0;
}