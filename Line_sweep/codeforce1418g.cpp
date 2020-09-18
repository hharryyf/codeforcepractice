#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 1048597
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
#define WAIT_FOR_WRONGANSWER
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

vector<int> occ[MAX_SIZE];
int a[MAX_SIZE];
int n;

int main() {
    int i;
    long long ans = 0;
    scanf("%d", &n);
    tree[0].rmin = MAX_SIZE << 3;
    build(1, n, 1);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }

    for (i = 1; i <= n; ++i) {
        occ[a[i]].push_back(i);
        int sz = occ[a[i]].size();
        if (sz == 1) {
            update(1, i, 1, n, 1, 1);
            #ifndef WAIT_FOR_WRONGANSWER
            cout << "cover " << 1 << " " << i << endl;
            #endif
        } else if (sz == 2) {
            update(occ[a[i]][0] + 1, occ[a[i]][1], 1, n, 1, 1);
            #ifndef WAIT_FOR_WRONGANSWER
            cout << "cover " << occ[a[i]][0] + 1 << " " << occ[a[i]][1] << endl;
            #endif
        } else if (sz == 3) {
            update(occ[a[i]][1] + 1, occ[a[i]][2], 1, n, 1, 1);
            update(1, occ[a[i]][0], 1, n, 1, -1);
            #ifndef WAIT_FOR_WRONGANSWER
            cout << "cover " << occ[a[i]][1] + 1 << " " << occ[a[i]][2] << endl;
            cout << "remove cover " << 1 << " " << occ[a[i]][0] << endl;
            #endif
        } else {
            update(occ[a[i]][sz - 2] + 1, occ[a[i]][sz - 1], 1, n, 1, 1);
            update(occ[a[i]][sz - 4] + 1, occ[a[i]][sz - 3], 1, n, 1, -1);
            update((sz >= 5 ? occ[a[i]][sz - 5] : 0) + 1, occ[a[i]][sz - 4], 1, n, 1, 1);
            #ifndef WAIT_FOR_WRONGANSWER
            cout << "cover " << occ[a[i]][sz - 2] + 1 << " " << occ[a[i]][sz - 1] << endl;
            cout << "remove " << occ[a[i]][sz - 4] + 1 << " " << occ[a[i]][sz - 3] << endl;
            cout << "cover " << ((sz >= 5 ? occ[a[i]][sz - 5] : 0) + 1) << " " << occ[a[i]][sz - 4] << endl;
            #endif
        }
        segt ret = query(1, i, 1, n, 1);
        int delta = ret.mcnt * (ret.rmin == 0);
        ans += delta;
    }

    printf("%I64d\n", ans);
    return 0;
}