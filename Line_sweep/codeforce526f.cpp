#include <bits/stdc++.h>
#define MAX_SIZE 1048596
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
using namespace std;

struct segt {
    int rmin, lz, rcnt;
};

segt tree[MAX_SIZE];

void pushdown(int l, int r, int index) {
    if (l > r) return;
    if (tree[index].lz != 0) {
        if (l != r) {
            tree[LEFT].lz += tree[index].lz;
            tree[RIGHT].lz += tree[index].lz;
            tree[LEFT].rmin += tree[index].lz;
            tree[RIGHT].rmin += tree[index].lz;
        }
        tree[index].lz = 0;
    }
}

segt pullup(segt t1, segt t2) {
    segt ret;
    ret.lz = 0;
    ret.rmin = min(t1.rmin, t2.rmin);
    ret.rcnt = (ret.rmin == t1.rmin) * t1.rcnt + (ret.rmin == t2.rmin) * t2.rcnt;
    return ret;
}

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        tree[index].rmin = l;
        tree[index].rcnt = 1;
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    tree[index] = pullup(tree[LEFT], tree[RIGHT]);
}

void update(int start, int end, int l, int r, int index, int val) {
    if (start > end || l > r || start > r || l > end) return;
    pushdown(l, r, index);
    if (start <= l && r <= end) {
        tree[index].rmin += val;
        tree[index].lz += val;
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

int a[MAX_SIZE];
int n;
// the min and max stack
// max stack is strictly decreasing
// min stack is strictly increasing
// here we actually use the same trick as 1422F boring query
vector<pair<int, int>> mn, mx;

int main() {
    int i;
    long long ans = 0;
    scanf("%d", &n);
    build(1, n, 1);
    for (i = 1; i <= n; ++i) {
        int r, c;
        scanf("%d%d", &r, &c);
        a[r] = c;
    }
    // count number of l such that max(l, r) - min(l, r) + l == r
    // a key property: max(l, r) - min(l, r) + l >= r !!!
    // then this is equivalent to count min value in a range of max(l, r) - min(l, r) + l
    mn.emplace_back(-10000000, 0);
    mx.emplace_back(10000000, 0);
    for (i = 1; i <= n; ++i) {
        while (a[i] <= mn.back().first) {
            int sz = mn.size();
            update(mn[sz - 2].second + 1, mn[sz - 1].second, 1, n, 1, mn[sz - 1].first);
            mn.pop_back();
        }
        update(mn.back().second + 1, i, 1, n, 1, -a[i]);
        mn.emplace_back(a[i], i);
        while (a[i] >= mx.back().first) {
            int sz = mx.size();
            update(mx[sz - 2].second + 1, mx[sz - 1].second, 1, n, 1, -mx[sz - 1].first);
            mx.pop_back();
        }
        update(mx.back().second + 1, i, 1, n, 1, a[i]);
        mx.emplace_back(a[i], i);
        auto ret = query(1, i, 1, n, 1);
        if (ret.rmin == i) {
            ans += ret.rcnt;
        }
    }

    cout << ans << endl;
    return 0;
}