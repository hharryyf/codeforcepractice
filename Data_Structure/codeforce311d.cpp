#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
#define MAX_SIZE 262192
typedef long long ll;
using namespace std;

struct segt {
    int lz;
    ll ans[48];
};

segt tree[MAX_SIZE];
ll tmp[48][2];
const ll mod = 95542721;
ll a[MAX_SIZE];

ll calc(ll x) {
    return (((x * x) % mod) * x) % mod;
}

void pushdown(int l, int r, int index) {
    if (l > r) return;
    int i;
    if (tree[index].lz != 0) {
        if (l != r) {
            for (i = 0 ; i < 48; ++i) {
                tmp[i][0] = tree[LEFT].ans[(i + tree[index].lz) % 48];
                tmp[i][1] = tree[RIGHT].ans[(i + tree[index].lz) % 48];
            }

            for (i = 0 ; i < 48; ++i) {
                tree[LEFT].ans[i] = tmp[i][0];
                tree[RIGHT].ans[i] = tmp[i][1];
            }

            tree[LEFT].lz += tree[index].lz;
            tree[RIGHT].lz += tree[index].lz;
        }

        tree[index].lz = 0;
    }
}

void pullup(int l, int r, int index) {
    if (l >= r) return;
    int i;
    for (i = 0 ; i < 48; ++i) tree[index].ans[i] = (tree[LEFT].ans[i] + tree[RIGHT].ans[i]) % mod;
}

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        int i;
        tree[index].ans[0] = a[l];
        for (i = 1; i < 48; ++i) tree[index].ans[i] = calc(tree[index].ans[i-1]);
        return; 
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    pullup(l, r, index);
}

void update(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return;
    pushdown(l, r, index);
    if (start <= l && r <= end) {
        int i;
        for (i = 0 ; i < 48; ++i) {
            tmp[i][0] = tree[index].ans[(i+1) % 48];
        }

        for (i = 0 ; i < 48; ++i) {
            tree[index].ans[i] = tmp[i][0];
        }

        tree[index].lz++;
        return;
    }

    if (end <= MID) {
        update(start, end, l, MID, LEFT);
    } else if (start >= MID + 1) {
        update(start, end, MID + 1, r, RIGHT);
    } else {
        update(start, end, l, MID, LEFT);
        update(start, end, MID + 1, r, RIGHT);
    }
    pullup(l, r, index);
}

ll query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return 0;
    pushdown(l, r, index);
    if (start <= l && r <= end) return tree[index].ans[0];
    if (end <= MID) return query(start, end, l, MID, LEFT);
    if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT);
    return (query(start, end, l, MID, LEFT) + query(start, end, MID + 1, r, RIGHT)) % mod;
}

int main() {
    int n, i;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) scanf("%I64d", &a[i]);
    build(1, n, 1);
    int q;
    scanf("%d", &q);
    while (q-- > 0) {
        int tp, l, r;
        scanf("%d%d%d", &tp, &l, &r);
        if (tp == 1) {
            printf("%I64d\n", query(l, r, 1, n, 1));
        } else {
            update(l, r, 1, n, 1);
        }
    }
    return 0;
}