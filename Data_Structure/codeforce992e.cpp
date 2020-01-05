#include <bits/stdc++.h>
#define MAX_SIZE 524292
typedef long long ll;
using namespace std;

struct segt {
    ll rmax;
    ll lz;
};

segt tree[MAX_SIZE];
// we are looking for a place that x[i] - a[i-1] = 0
// let a[i] = sum(x[j], j = 1..i)
ll a[MAX_SIZE], x[MAX_SIZE];
int n, q;
// for every update x[i] -> val, we decrease all value of range tree [i:n] by val - x[i]
// and increment x[i] by val

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        tree[index].rmax = x[l] - a[l-1];
        tree[index].lz = 0;
        return;
    }
    
    int mid = l + (r - l) / 2;
    build(l, mid, index * 2);
    build(mid + 1, r, index * 2 + 1);
    tree[index].rmax = max(tree[index * 2].rmax, tree[index * 2 + 1].rmax);
}

void pushdown(int l, int r, int index) {
    if (l > r) return;
    if (tree[index].lz != 0) {
        if (l != r) {
            tree[index * 2].lz += tree[index].lz;
            tree[index * 2 + 1].lz += tree[index].lz;
            tree[index * 2].rmax += tree[index].lz;
            tree[index * 2 + 1].rmax += tree[index].lz;
        }
        tree[index].lz = 0;
    }
}

void update(int start, int end, int l, int r, int index, ll val) {
    if (start > end || l > r) return;
    pushdown(l, r, index);
    int mid = l + (r - l) / 2;
    if (start > r || l > end) return;
    if (start <= l && r <= end) {
        tree[index].rmax += val;
        tree[index].lz += val;
        return;
    }
    
    if (end <= mid) {
        update(start, end, l, mid, index * 2, val);
    } else if (start >= mid + 1) {
        update(start, end, mid + 1, r, index * 2 + 1, val);
    } else {
        update(start, end, l, mid, index * 2, val);
        update(start, end, mid + 1, r, index * 2 + 1, val);
    }
    tree[index].rmax = max(tree[index * 2].rmax, tree[index * 2 + 1].rmax);
}

// return the index of the 0 element in [l, r]
int query(int l, int r, int index) {
    if (l > r) return -1;
    pushdown(l, r, index);
    if (tree[index].rmax < 0) return -1;
    if (l == r) {
        if (tree[index].rmax == 0) return l;
        return -1;
    }
    
    int mid = l + (r - l) / 2;
    int v = query(l, mid, index * 2);
    if (v != -1) return v;
    return query(mid + 1, r, index * 2 + 1);
}

int main() {
    scanf("%d%d", &n, &q);
    int i;
    for (i = 1; i <= n; i++) {
        scanf("%lld", &x[i]);
        a[i] = a[i-1] + x[i];
    }
    // every node of the tree stores x[i] - a[i-1]
    build(1, n, 1);
    
    while (q > 0) {
        int pos;
        ll v;
        scanf("%d%lld", &pos, &v);
        update(pos, pos, 1, n, 1, v - x[pos]);
        update(pos + 1, n, 1, n, 1, x[pos] - v);
        printf("%d\n", query(1, n, 1));
        x[pos] = v;
        q--;
    }
    return 0;
}
