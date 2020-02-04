#pragma GCC optimize(3)
#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 262192
using namespace std;

const ll mod1 = 19260817;
const ll mod2 = 1000000007;
const ll p1 = 133, p2 = 1011;

ll pw1[MAX_SIZE << 1], pw2[MAX_SIZE << 1];
ll pfx1[MAX_SIZE << 1], pfx2[MAX_SIZE << 1];

void preprocess() {
    int i;
    pfx1[0] = pfx2[0] = pw1[0] = pw2[0] = 1;
    for (i = 1 ; i < (MAX_SIZE << 1); i++) {
        pw1[i] = (pw1[i-1] * p1) % mod1;
        pw2[i] = (pw2[i-1] * p2) % mod2;
        pfx1[i] = (pfx1[i-1] + pw1[i]) % mod1;
        pfx2[i] = (pfx2[i-1] + pw2[i]) % mod2;
    }
}

struct segt {
    ll h1, h2;
    int len, lz;
};

segt tree[MAX_SIZE];
char st[MAX_SIZE];

segt pullup(segt t1, segt t2) {
    segt t;
    t.len = t1.len + t2.len, t.lz = -1;
    t.h1 = (t1.h1 + (t2.h1 * pw1[t1.len])) % mod1;
    t.h2 = (t1.h2 + (t2.h2 * pw2[t1.len])) % mod2;
    return t;
}

void pushdown(int l, int r, int index) {
    if (l > r) return;
    if (tree[index].lz != -1) {
        if (l != r) {
            int l1 = tree[index * 2].len, l2 = tree[index * 2 + 1].len;
            tree[index * 2].lz = tree[index * 2 + 1].lz = tree[index].lz;
            tree[index * 2].h1 = (tree[index].lz * pfx1[l1 - 1]) % mod1;
            tree[index * 2].h2 = (tree[index].lz * pfx2[l1 - 1]) % mod2;
            tree[index * 2 + 1].h1 = (tree[index].lz * pfx1[l2 - 1]) % mod1;
            tree[index * 2 + 1].h2 = (tree[index].lz * pfx2[l2 - 1]) % mod2;
        }
        tree[index].lz = -1;
    }
}

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        tree[index].lz = -1;
        tree[index].len = 1;
        tree[index].h1 = tree[index].h2 = st[l-1] - '0';
        return;
    }
    int mid = l + (r - l) / 2;
    build(l, mid, index * 2);
    build(mid + 1, r, index * 2 + 1);
    tree[index] = pullup(tree[index * 2], tree[index * 2 + 1]);
}

void update(int start, int end, int l, int r, int index, int val) {
    if (start > end || l > r) return;
    pushdown(l, r, index);
    if (start <= l && r <= end) {
        tree[index].lz = val;
        tree[index].h1 = (pfx1[tree[index].len - 1] * val) % mod1;
        tree[index].h2 = (pfx2[tree[index].len - 1] * val) % mod2;
        return;
    }
    
    int mid = l + (r - l) / 2;
    if (end <= mid) {
        update(start, end, l, mid, index * 2, val);
    } else if (start >= mid + 1) {
        update(start, end, mid + 1, r, index * 2 + 1, val);
    } else {
        update(start, end, l, mid, index * 2, val);
        update(start, end, mid + 1, r, index * 2 + 1, val);
    }
    tree[index] = pullup(tree[index * 2], tree[index * 2 + 1]);
}

segt query(int start, int end, int l, int r, int index) {
    if (start > end || l > r) return tree[0];
    pushdown(l, r, index);
    if (start <= l && r <= end) return tree[index];
    int mid = l + (r - l) / 2;
    if (end <= mid) {
        return query(start, end, l, mid, index * 2);
    } else if (start >= mid + 1) {
        return query(start, end, mid + 1, r, index * 2 + 1);
    }
    return pullup(query(start, end, l, mid, index * 2),
                  query(start, end, mid + 1, r, index * 2 + 1));
}

int n, m, k, q;

int main() {
    preprocess();
    scanf("%d%d%d", &n, &m, &k);
    scanf("%s", st);
    build(1, n, 1);
    q = m + k;
    while (q > 0) {
        int tp, l, r, val;
        scanf("%d%d%d%d", &tp, &l, &r, &val);
        if (tp == 1) {
            update(l, r, 1, n, 1, val);
        } else {
            segt ret1 = query(l, r-val, 1, n, 1);
            segt ret2 = query(l+val, r, 1, n, 1);
            if (ret1.h1 == ret2.h1 && ret1.h2 == ret2.h2) {
                printf("YES\n");
            } else {
                printf("NO\n");
            }
        }
        q--;
    }
    return 0;
}
