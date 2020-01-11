#include <bits/stdc++.h>
#define MAX_SIZE 2097252
using namespace std;
typedef long long ll;
struct segt {
    ll rsum, rmax;
    int l;
};

segt tree[MAX_SIZE];

void build(int l, int r, int index) {
    if (l > r) return;
    
    if (l == r) {
        tree[index].l = l;
        return;
    }
    
    int mid = l + (r - l) / 2;
    build(l, mid, index * 2);
    build(mid + 1, r, index * 2 + 1);
    tree[index].l = tree[index * 2].l;
}

segt pullup(segt t1, segt t2) {
    segt t;
    t.l = t1.l;
    t.rsum = t1.rsum + t2.rsum;
    if (t1.rmax <= t2.l) {
        t.rmax = t2.rmax;
    } else {
        t.rmax = max(t1.rmax + t2.rsum, t2.rmax);
    }
    
    return t;
}

void update(int pos, int l, int r, int index, ll d) {
    if (pos < l || pos > r || l > r) return;
    if (l == r && pos == l) {
        tree[index].rsum = d;
        if (d != 0) {
            tree[index].rmax = d + tree[index].l;
        } else {
            tree[index].rmax = 0;
        }
        return;
    }
    
    int mid = l + (r - l) / 2;
    if (pos <= mid) {
        update(pos, l, mid, index * 2, d);
    } else {
        update(pos, mid + 1, r, index * 2 + 1, d);
    }
    tree[index] = pullup(tree[index * 2], tree[index * 2 + 1]);
}

segt query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return segt{0,0,0};
    if (start <= l && r <= end) return tree[index];
    int mid = l + (r - l) / 2;
    if (end <= mid) {
        return query(start, end, l, mid, index * 2);
    } else if (start >= mid + 1) {
        return query(start, end, mid + 1, r, index * 2 + 1);
    }
    
    return pullup(query(start, end, l, mid, index * 2), query(start, end, mid + 1, r, index * 2 + 1));
}

int visited[MAX_SIZE >> 2];
char st[4];
int U = 1000000;
int main() {
    int q, i;
    scanf("%d", &q);
    build(1, U, 1);
    for (i = 1 ; i <= q; i++) {
        int t, d;
        scanf("%s", st);
        if (st[0] == '+') {
            scanf("%d%d", &t, &d);
            visited[i] = t;
            update(t, 1, U, 1, d);
        } else if (st[0] == '-') {
            scanf("%d", &d);
            update(visited[d], 1, U, 1, 0);
            visited[d] = 0;
        } else {
            scanf("%d", &t);
            segt ret = query(1, t, 1, U, 1);
            printf("%lld\n", max(0ll, ret.rmax - (ll) t));
        }
    }
    return 0;
}
