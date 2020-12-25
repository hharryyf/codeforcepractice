#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2,fma") 
#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 524292
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
using namespace std;

struct segt {
    int lz, rmin, mcnt;
};

segt tree[MAX_SIZE];

void pushdown(int l, int r, int index) {
    if (l > r) return;
    if (tree[index].lz != 0) {
        if (l != r) {
            tree[LEFT].rmin += tree[index].lz;
            tree[RIGHT].rmin += tree[index].lz;
            tree[LEFT].lz += tree[index].lz;
            tree[RIGHT].lz += tree[index].lz;
        }
        tree[index].lz = 0;
        return;
    }
}

segt pullup(segt t1, segt t2) {
    segt ret;
    ret.rmin = min(t1.rmin, t2.rmin);
    ret.lz = 0;
    ret.mcnt = t1.mcnt * (ret.rmin == t1.rmin) + t2.mcnt * (ret.rmin == t2.rmin); 
    return ret;
}

void update(int start, int end, int l, int r, int index, int val) {
    if (start > end || l > r || start > r || l > end) return;
    pushdown(l, r, index);
    if (start <= l && r <= end) {
        tree[index].lz += val;
        tree[index].rmin += val;
        return;
    }

    if (end <= MID) {
        update(start, end, l, MID, LEFT, val);
    } else if (start >= MID + 1) {
        update(start, end, MID + 1, r, RIGHT, val);
    } else {
        update(start, end, l, MID, LEFT, val);
        update(start, end, MID + 1, r, RIGHT, val);
    }

    tree[index] = pullup(tree[LEFT], tree[RIGHT]);
}

segt query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return tree[0];
    pushdown(l, r, index);
    if (start <= l && r <= end) return tree[index];
    if (end <= MID) return query(start, end, l, MID, LEFT);
    if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT);
    return pullup(query(start, end, l, MID, LEFT), query(start, end, MID + 1, r, RIGHT));
}

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        tree[index].mcnt = 1;
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    tree[index] = pullup(tree[LEFT], tree[RIGHT]);
}

int a[MAX_SIZE], pos[31], L[MAX_SIZE];
vector<int> del[MAX_SIZE];
int N;



int main() {
    int i, j;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &a[i]);
    }

    for (i = 0 ; i < 31; ++i) pos[i] = MAX_SIZE;
    for (i = N; i >= 1; --i) {
        int right = MAX_SIZE;
        for (j = 0; j < 31; ++j) {
            if (!(a[i] & (1 << j))) {
                right = min(right, pos[j]);
            }
        }

        for (j = 0 ; j < 31; ++j) {
            if (a[i] & (1 << j)) {
                pos[j] = i;
            }
        }

        if (right < MAX_SIZE) del[right].push_back(i);
    }

    for (i = 0 ; i < 31; ++i) pos[i] = 0;
    build(1, N, 1);
    ll ans = 0;
    for (i = 1; i <= N; ++i) {
        for (j = 0; j < 31; ++j) {
            if (!(a[i] & (1 << j))) {
                L[i] = max(L[i], pos[j]);
            }
        }

        for (j = 0 ; j < 31; ++j) {
            if (a[i] & (1 << j)) {
                pos[j] = i;
            }
        }

        update(L[i] + 1, i, 1, N, 1, 1);
        for (auto v : del[i]) {
            update(L[v] + 1, v, 1, N, 1, -1);
        }

        auto ret = query(1, i, 1, N, 1);
        if (ret.rmin == 0) {
            ans += ret.mcnt;
        }
    }

    printf("%I64d\n", ans);
    return 0;
}