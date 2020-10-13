#include <bits/stdc++.h>
#define MAX_SIZE 262192
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
using namespace std;
typedef long long ll;

const ll mod[2] = {19260421, 19260817};
const int base[2] = {47, 37};
ll inv[2];
struct segt {
    int l, r, len;
    ll hval[2];
};
ll pw[MAX_SIZE][2];
segt tree[MAX_SIZE << 1];
char st[MAX_SIZE];

ll fastpower(ll v, ll p, ll md) {
    ll base = v, ret = 1;
    while (p > 0) {
        if (p % 2 == 0) {
            base = base * base;
            base %= md;
            p /= 2;
        } else {
            ret = ret * base;
            ret %= md;
            p--;
        }
    }
    return ret;
}

void init() {
    int i, j;
    pw[0][0] = pw[0][1] = 1;
    for (j = 0; j < 2; ++j) {
        inv[j] = fastpower(base[j], mod[j] - 2, mod[j]);
        for (i = 1; i < MAX_SIZE; ++i) {
            pw[i][j] = pw[i-1][j] * base[j];
            pw[i][j] %= mod[j];
        }
    }
}

segt pullup(segt t1, segt t2) {
    segt ret;
    int i;
    if (t1.len == 0) return t2;
    if (t2.len == 0) return t1;
    ret.len = t1.len + t2.len;
    if (t1.r == 1 && t2.l == 1) {
        ret.len -= 2;
        for (i = 0 ; i < 2; ++i) {
            t1.hval[i] -= 2;
            t1.hval[i] *= inv[i];
            t1.hval[i] %= mod[i];
            t2.hval[i] -= pw[t2.len - 1][i] * 2;
            ret.hval[i] = t1.hval[i] * pw[t2.len - 1][i] + t2.hval[i];
            ret.hval[i] %= mod[i];
        }

        if (ret.len == 0) {
            ret.l = ret.r = 0;
        } else if (t1.len == 1) {
            ret.l = 0, ret.r = t2.r;
        } else if (t2.len == 1) {
            ret.l = t1.l, ret.r = 0;
        } else {
            ret.l = t1.l, ret.r = t2.r;
        }
        
    } else {
        ret.l = t1.l, ret.r = t2.r;
        for (i = 0 ; i < 2; ++i) {
            ret.hval[i] = t2.hval[i] + t1.hval[i] * pw[t2.len][i];
            ret.hval[i] %= mod[i];
        }    
    }

    for (i = 0 ; i < 2; ++i) {
        ret.hval[i] += mod[i];
        ret.hval[i] %= mod[i];
    }

    return ret;
}

segt query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return tree[0];
    if (start <= l && r <= end) return tree[index];
    if (end <= MID) return query(start, end, l, MID, LEFT);
    if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT);
    return pullup(query(start, end, l, MID, LEFT), query(start, end, MID + 1, r, RIGHT));
}

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        if (st[l] == '1') {
            tree[index].hval[0] = tree[index].hval[1] = 2;
            tree[index].l = tree[index].r = 1;
        } else {
            tree[index].hval[0] = tree[index].hval[1] = 1;
            tree[index].l = tree[index].r = 0;
        }   
        tree[index].len = 1;
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    tree[index] = pullup(tree[LEFT], tree[RIGHT]);
}

int main() {
    int n, q;
    init();
    scanf("%d", &n);
    scanf("%s", st + 1);
    build(1, n, 1);
    scanf("%d", &q);
    while (q-- > 0) {
        int l1, l2, len;
        scanf("%d%d%d", &l1, &l2, &len);
        auto ret1 = query(l1, l1 + len - 1, 1, n, 1);
        auto ret2 = query(l2, l2 + len - 1, 1, n, 1);
        printf("%s\n", ((ret1.hval[0] == ret2.hval[0]) && (ret1.hval[1] == ret2.hval[1])) ? "Yes" : "No");
    }
    return 0;
}