#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 1048592
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
using namespace std;
typedef long long ll;
struct segt {
    ll rmax, rsum;
};

segt tree[MAX_SIZE];
int d[MAX_SIZE];
int a[MAX_SIZE];

void update(int pt, int l, int r, int index, int val) {
    if (l > r || pt < l || pt > r) return;
    if (l == r) {
        tree[index].rmax = tree[index].rsum = val;
        return;
    }

    if (pt <= MID) {
        update(pt, l, MID, LEFT, val);
    } else {
        update(pt, MID + 1, r, RIGHT, val);
    }

    tree[index].rmax = max(tree[LEFT].rmax, tree[RIGHT].rmax);
    tree[index].rsum = tree[LEFT].rsum + tree[RIGHT].rsum;
}

ll query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return 0;
    if (start <= l && r <= end) return tree[index].rsum;
    if (end <= MID) return query(start, end, l, MID, LEFT);
    if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT);
    return query(start, end, l, MID, LEFT) + query(start, end, MID + 1, r, RIGHT);
}

// get the leftmost position in [start, end] such that a[pos] > val
int search(int start, int end, int l, int r, int index, int val) {
    if (start > end || l > r || start > r || l > end) return MAX_SIZE;
    if (tree[index].rmax <= val) return MAX_SIZE;
    if (start <= l && r <= end) {
        if (l == r) return l;
        if (tree[LEFT].rmax > val) return search(start, end, l, MID, LEFT, val);
        return search(start, end, MID + 1, r, RIGHT, val);
    }

    if (end <= MID) return search(start, end, l, MID, LEFT, val);
    if (start >= MID + 1) return search(start, end, MID + 1, r, RIGHT, val);
    return min(search(start, end, l, MID, LEFT, val), search(start, end, MID + 1, r, RIGHT, val));
}

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        tree[index].rsum = tree[index].rmax = a[l];
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    tree[index].rsum = tree[LEFT].rsum + tree[RIGHT].rsum;
    tree[index].rmax = max(tree[LEFT].rmax, tree[RIGHT].rmax);
}

int main() {
    int i, j, n, q;
    for (i = 1; i <= 1000000; ++i) {
        for (j = 1; j * i <= 1000000; ++j) {
            d[i * j]++;
        }
    }

    scanf("%d%d", &n, &q);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }

    build(1, n, 1);

    while (q-- > 0) {
        int t, l, r, pos;
        scanf("%d%d%d", &t, &l, &r);
        if (t == 1) {
            while (l <= r) {
                pos = search(l, r, 1, n, 1, 2);
                if (pos <= r) {
                    a[pos] = d[a[pos]];
                    update(pos, 1, n, 1, a[pos]);
                }
                l = pos + 1;
            }
        } else {
            printf("%I64d\n", query(l, r, 1, n, 1));
        }
    }
    return 0;
}