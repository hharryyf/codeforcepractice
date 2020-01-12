#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 262192
typedef long long ll;
using namespace std;

ll mul(ll a1, ll a2) {
    return (a1 * a2) % MOD;
}

ll add(ll a1, ll a2) {
    return (a1 + a2) % MOD;
}

struct segt {
    int len;
    ll value[6];
    ll lz;
};

segt tree[MAX_SIZE];
ll a[MAX_SIZE >> 1];
ll prefix[MAX_SIZE][6];
ll pw[MAX_SIZE][6];

ll c[6][6];

void precompute() {
    int i, j;
    c[0][0] = 1;
    c[1][0] = 1;
    c[1][1] = 1;
    for (i = 2; i < 6; i++) {
        c[i][0] = 1;
        for (j = 1; j <= i; j++) {
            c[i][j] = c[i-1][j] + c[i-1][j-1];
        }
    }
    
    for (i = 1; i < MAX_SIZE; i++) {
        ll curr = 1;
        for (j = 0; j < 6; j++) {
            prefix[i][j] = add(prefix[i-1][j], curr);
            pw[i][j] = curr;
            curr = mul(curr, i);
        }
    }
}


segt pullup(segt t1, segt t2) {
    segt ret;
    int i, j;
    ret.lz = -1;
    ret.len = t1.len + t2.len;
    
    for (i = 0; i < 6; i++) {
        ret.value[i] = t1.value[i];
        for (j = 0; j <= i; j++) {
            ret.value[i] = add(ret.value[i], mul(c[i][j], mul(pw[t1.len][i - j], t2.value[j])));
        }
    }
    return ret;
}

void pushdown(int index) {
    if (tree[index].lz != -1) {
        if (tree[index].len > 1) {
            tree[index * 2].lz = tree[index].lz;
            tree[index * 2 + 1].lz = tree[index].lz;
            int i;
            for (i = 0 ; i < 6; i++) {
                tree[index * 2].value[i] = mul(tree[index].lz, prefix[tree[index * 2].len][i]);
                tree[index * 2 + 1].value[i] = mul(tree[index].lz, prefix[tree[index * 2 + 1].len][i]);
            }
        }
        tree[index].lz = -1;
    }
}

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        int i;
        for (i = 0 ; i < 6; i++) {
            tree[index].value[i] = a[l];
        }
        tree[index].len = 1;
        tree[index].lz = -1;
        return;
    }
    
    int mid = l + (r - l) / 2;
    build(l, mid, index * 2);
    build(mid + 1, r, index * 2 + 1);
    tree[index] = pullup(tree[index * 2], tree[index * 2 + 1]);
}

void update(int start, int end, int l, int r, int index, ll val) {
    if (start > end || l > r) return;
    pushdown(index);
    if (start <= l && r <= end) {
        tree[index].lz = val;
        for (int i = 0 ; i < 6; i++) {
            tree[index].value[i] = mul(val, prefix[tree[index].len][i]);
        }
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
    pushdown(index);
    if (start <= l && r <= end) return tree[index];
    int mid = l + (r - l) / 2;
    if (end <= mid) return query(start, end, l, mid, index * 2);
    if (start >= mid + 1) return query(start, end, mid + 1, r, index * 2 + 1);
    return pullup(query(start, end, l, mid, index * 2), 
                  query(start, end, mid + 1, r, index * 2 + 1));
}

char st[4];

int main() {
    precompute();
    int n, m, i;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    
    build(1, n, 1);
    
    for (i = 0 ; i < m; i++) {
        int l, r, val;
        scanf("%s%d%d%d", st, &l, &r, &val);
        if (st[0] == '?') {
            printf("%lld\n", query(l, r, 1, n, 1).value[val]);
        } else {
            update(l, r, 1, n, 1, (ll) val);
        }
    }
    return 0;
}
