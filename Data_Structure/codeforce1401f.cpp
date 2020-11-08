#include <bits/stdc++.h>
#define MAX_SIZE 524292
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
#define MID ((l+r)>>1)
using namespace std;
typedef long long ll;


int swp[19], a[MAX_SIZE];
ll tree[MAX_SIZE];

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        tree[index] = a[l];
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    tree[index] = tree[LEFT] + tree[RIGHT];
}

void update(int pt, int l, int r, int index, int dep, ll val) {
    if (pt < l || pt > r || l > r) return;
    if (l == r) {
        tree[index] = val;
        return;
    }

    int shift = (1 << (dep - 1)) * swp[dep - 1];
    if (shift == 0) {
        if (pt <= MID) {
            update(pt, l, MID, LEFT, dep - 1, val);
        } else {
            update(pt, MID + 1, r, RIGHT, dep - 1, val);
        }
    } else {
        if (pt <= MID) {
            update(pt, l, MID, RIGHT, dep - 1, val);
        } else {
            update(pt, MID + 1, r, LEFT, dep - 1, val);
        }
    }
    tree[index] = tree[LEFT] + tree[RIGHT];
}

ll query(int start, int end, int l, int r, int index, int dep) {
    if (start > end || l > r || start > r || l > end) return 0;
    if (start <= l && r <= end) return tree[index];

    int shift = (1 << (dep - 1)) * swp[dep - 1];
    if (shift == 0) {
        return query(start, end, l, MID, LEFT, dep - 1) + query(start, end, MID + 1, r, RIGHT, dep - 1);
    } else {
        return query(start, end, MID + 1, r, LEFT, dep - 1) + query(start, end, l, MID, RIGHT, dep - 1);
    }
}

int main() {
    int n, i, q;
    scanf("%d%d", &n, &q);
    for (i = 1; i <= (1 << n); ++i) scanf("%d", &a[i]);
    build(1, 1 << n, 1);
    while (q-- > 0) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int idx, v;
            scanf("%d%d", &idx, &v);
            update(idx, 1, 1 << n, 1, n, v);
        } else if (op == 2) {
            int v;
            scanf("%d", &v);
            for (i = 0; i < v; ++i) swp[i] ^= 1;
        } else if (op == 3) {
            int v;
            scanf("%d", &v);
            swp[v] ^= 1;
        } else {
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%I64d\n", query(l, r, 1, 1 << n, 1, n));
        }
    }
    return 0;
}