#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#define LEFT (index<<1)
#define RIGHT (index<< 1|1)
#define MID ((l+r)>>1)
#define MAX_SIZE 524292
using namespace std;


struct segt {
    int to[101];
};

segt tree[MAX_SIZE];
int a[MAX_SIZE];
int n;

// we maintain a range tree, which tree[index].to[i] refers to in this
// range which value i is mapped to

void build(int l, int r, int index) {
    if (l > r) return;
    int i;
    for (i = 1; i <= 100; ++i) {
        tree[index].to[i] = i;
    }

    if (l == r) return;

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
}

void pushdown(int l, int r, int index) {
    if (l >= r) return;
    int i;
    for (i = 1; i <= 100; ++i) {
        tree[LEFT].to[i] = tree[index].to[tree[LEFT].to[i]];
        tree[RIGHT].to[i] = tree[index].to[tree[RIGHT].to[i]];
    }

    for (i = 1; i <= 100; ++i) {
        tree[index].to[i] = i;
    }

}

// change all "from" in [l, r] to "to"
void update(int start, int end, int l, int r, int index, int from, int to) {
    if (start > r || l > end || start > end || l > r) return;
    // push
    pushdown(l, r, index);
    int i;
    if (start <= l && r <= end) {
        for (i = 1; i <= 100; ++i) { 
            if (tree[index].to[i] == from) {
                tree[index].to[i] = to;
            }
        }

        return;
    }

    if (end <= MID) {
        update(start, end, l, MID, LEFT, from, to);
    } else if (start >= MID + 1) {
        update(start, end, MID + 1, r, RIGHT, from, to);
    } else {
        update(start, end, l, MID, LEFT, from, to);
        update(start, end, MID + 1, r, RIGHT, from, to);
    }
}

int query(int pt, int l, int r, int index, int val) {
    if (pt < l || pt > r || l > r) return 0;
    pushdown(l, r, index);
    if (l == r) return tree[index].to[val];
    if (pt <= MID) {
        return query(pt, l, MID, LEFT, val);
    }
    return query(pt, MID + 1, r, RIGHT, val);
}

int main() {
    int i;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }

    build(1, n, 1);

    int q;
    scanf("%d", &q);
    while (q > 0) {
        int l, r, x, y;
        scanf("%d%d%d%d", &l, &r, &x, &y);
        update(l, r, 1, n, 1, x, y);
        --q;
    }

    for (i = 1; i <= n; ++i) {
        printf("%d ", query(i, 1, n, 1, a[i]));
    }
    return 0;
}