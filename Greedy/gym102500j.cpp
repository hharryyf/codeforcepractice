#include <bits/stdc++.h>
#define MAX_SIZE 1048597
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
typedef long long ll;
using namespace std;

struct segt {
    int pp, pn, np, nn;
};

segt tree[MAX_SIZE];
int s[MAX_SIZE];
segt pullup(segt t1, segt t2) {
    segt ret;
    ret.pp = ret.pn = ret.np = ret.nn = 0;
    ret.pp = max(t1.pp, t2.pp);
    if (t1.pn != 0 && t2.pp != 0)
        ret.pp = max(ret.pp, t1.pn + t2.pp);
    if (t1.pp != 0 && t2.np != 0)
        ret.pp = max(ret.pp, t1.pp + t2.np);
    ret.nn = max(t1.nn, t2.nn);
    if (t1.nn != 0 && t2.pn != 0)
        ret.nn = max(ret.nn, t1.nn + t2.pn);
    if (t1.np != 0 && t2.nn != 0)
        ret.nn = max(ret.nn, t1.np + t2.nn);
    ret.pn = max(t1.pn, t2.pn);
    if (t1.pn != 0 && t2.pn != 0)
        ret.pn = max(ret.pn, t1.pn + t2.pn);
    if (t1.pp != 0 && t2.nn != 0)
        ret.pn = max(ret.pn, t1.pp + t2.nn);
    ret.np = max(t1.np, t2.np);
    if (t1.np != 0 && t2.np != 0)
        ret.np = max(ret.np, t1.np + t2.np);
    if (t1.nn != 0 && t2.pp != 0)
        ret.np = max(ret.np, t1.nn + t2.pp);
    return ret;
}

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        if (s[l] > 0) {
            tree[index].pp = 1;
        } else if (s[l] < 0) {
            tree[index].nn = 1;
        }
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    tree[index] = pullup(tree[LEFT], tree[RIGHT]);
}

void update(int pt, int l, int r, int index, int sgn) {
    if (l > r || pt < l || pt > r) return;
    if (l == r) {
        if (sgn == 0) {
            tree[index].pp = tree[index].nn = 1;
        } else if (sgn > 0) {
            tree[index].pp = 1;
        } else {
            tree[index].nn = 1;
        }
        return;
    }

    if (pt <= MID) {
        update(pt, l, MID, LEFT, sgn);
    } else {
        update(pt, MID + 1, r, RIGHT, sgn);
    }
    tree[index] = pullup(tree[LEFT], tree[RIGHT]);
}

int query() {
    // cout << tree[1].nn << " " << tree[1].pp << " " << tree[1].pn << " " << tree[1].pp << endl;
    return max(max(tree[1].nn, tree[1].pp), max(tree[1].pn, tree[1].np));
}

map<int, vector<int>> mp;

int main() {
    int N, i;
    ll C, R, ans;
    scanf("%d%I64d%I64d", &N, &C, &R);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &s[i]);
    }

    build(1, N, 1);

    ans = R * (N - query());
    // cout << query() << endl;
    for (i = 1; i <= N; ++i) {
        mp[abs(s[i]) + 1].push_back(i);
    }

    for (auto iter : mp) {
        int cnt = iter.first;
        for (auto idx : iter.second) {
            update(idx, 1, N, 1, 0);
            ans = min(ans, C * cnt + R * (N - query()));
        }
    }

    cout << ans << endl;
    return 0;
}