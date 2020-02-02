#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 262192
using namespace std;

struct segt {
    double value;
    double lz1, lz2;
    int len;
};

segt tree[MAX_SIZE];
double a[MAX_SIZE];

segt pullup(segt t1, segt t2) {
    segt t;
    t.lz1 = 1.0, t.lz2 = 0.0;
    t.len = t1.len + t2.len;
    t.value = t1.value + t2.value;
    return t;
}

void pushdown(int index) {
    if (tree[index].len > 1) {
        if (tree[index].lz1 != 1.0) {
            tree[index * 2].value *= tree[index].lz1;
            tree[index * 2 + 1].value *= tree[index].lz1;
            tree[index * 2].lz1 *= tree[index].lz1;
            tree[index * 2 + 1].lz1 *= tree[index].lz1;
            tree[index * 2].lz2 *= tree[index].lz1;
            tree[index * 2 + 1].lz2 *= tree[index].lz1;
        }
        
        if (tree[index].lz2 != 0.0) {
            tree[index * 2].value += tree[index].lz2 * tree[index * 2].len;
            tree[index * 2 + 1].value += tree[index].lz2 * tree[index * 2 + 1].len;
            tree[index * 2].lz2 += tree[index].lz2;
            tree[index * 2 + 1].lz2 += tree[index].lz2;
        }
    }
    tree[index].lz1 = 1.0, tree[index].lz2 = 0.0;
}

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        tree[index].value = a[l];
        tree[index].lz1 = 1.0, tree[index].lz2 = 0.0;
        tree[index].len = 1;
        return;
    }
    
    int mid = l + (r - l) / 2;
    build(l, mid, index * 2);
    build(mid + 1, r, index * 2 + 1);
    tree[index] = pullup(tree[index * 2], tree[index * 2 + 1]); 
}

segt query(int start, int end, int l, int r, int index) {
    if (start > end || l > r) return segt{0,1.0,0,0};
    pushdown(index);
    if (start <= l && r <= end) return tree[index];
    int mid = l + (r - l) / 2;
    if (end <= mid) return query(start, end, l, mid, index * 2);
    if (start >= mid + 1) return query(start, end, mid + 1, r, index * 2 + 1);
    return pullup(query(start, end, l, mid, index * 2), 
                  query(start, end, mid + 1, r, index * 2 + 1));
}

void update(int start, int end, int l, int r, int index, double v1, double v2) {
    if (start > end || l > r) return;
    pushdown(index);
    if (start <= l && r <= end) {
        tree[index].value *= v1;
        tree[index].value += v2 * tree[index].len;
        tree[index].lz1 *= v1;
        tree[index].lz2 += v2;
        return;
    }
    
    int mid = l + (r - l) / 2;
    if (end <= mid) {
        update(start, end, l, mid, index * 2, v1, v2);
    } else if (start >= mid + 1) {
        update(start, end, mid + 1, r, index * 2 + 1, v1, v2);
    } else {
        update(start, end, l, mid, index * 2, v1, v2);
        update(start, end, mid + 1, r, index * 2 + 1, v1, v2);
    }
    tree[index] = pullup(tree[index * 2], tree[index * 2 + 1]);
}

int main() {
    int i, n, q;
    scanf("%d%d", &n, &q);
    for (i = 1; i <= n; i++) scanf("%lf", &a[i]);
    build(1, n, 1);
    while (q > 0) {
        int tp, l1, r1, l2, r2;
        scanf("%d", &tp);
        if (tp == 1) {
            scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
            segt v1 = query(l1, r1, 1, n, 1);
            segt v2 = query(l2, r2, 1, n, 1);
            update(l1, r1, 1, n, 1, (1.0 * v1.len - 1.0) / (1.0 * v1.len), v2.value / (1.0 * v1.len * v2.len));
            update(l2, r2, 1, n, 1, (1.0 * v2.len - 1.0) / (1.0 * v2.len), v1.value / (1.0 * v1.len * v2.len));
        } else {
            scanf("%d%d", &l1, &l2);
            printf("%.7lf\n", query(l1, l2, 1, n, 1).value);
        }
        
        q--;
    }
    return 0;
}
