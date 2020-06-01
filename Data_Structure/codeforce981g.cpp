#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MID ((l+r)>>1)
#define LEFT (index << 1)
#define RIGHT (index << 1 | 1)
typedef long long ll;
#define MAX_SIZE 524292
using namespace std;

const int mod = 998244353;

struct segt {
    ll rsum, lz1, lz2;
};

// uncovered interval by each number
set<pair<int, int>> uncov[MAX_SIZE];
segt tree[MAX_SIZE];
ll ivt = 1;
int n;

ll mul(ll v1, ll v2) {
    return (v1 * v2) % mod;
}

ll add(ll v1, ll v2) {
    return (v1 + v2) % mod;
}

ll fix(ll num) {
    return (num % mod + mod) % mod;
}

void pushdown(int l, int r, int index) {
    if (l > r) return;
    int len1 = MID - l + 1, len2 = r - MID;
    if (tree[index].lz1 != 1) {
        if (l != r) {
            tree[LEFT].lz1 = mul(tree[LEFT].lz1, tree[index].lz1);
            tree[LEFT].lz2 = mul(tree[LEFT].lz2, tree[index].lz1);
            tree[RIGHT].lz1 = mul(tree[RIGHT].lz1, tree[index].lz1);
            tree[RIGHT].lz2 = mul(tree[RIGHT].lz2, tree[index].lz1);
            tree[LEFT].rsum = mul(tree[LEFT].rsum, tree[index].lz1);
            tree[RIGHT].rsum = mul(tree[RIGHT].rsum, tree[index].lz1);
        }
        tree[index].lz1 = 1;
    }

    if (tree[index].lz2 != 0) {
        if (l != r) {
            tree[LEFT].lz2 = add(tree[LEFT].lz2, tree[index].lz2);
            tree[RIGHT].lz2 = add(tree[RIGHT].lz2, tree[index].lz2);
            tree[LEFT].rsum = add(tree[LEFT].rsum, tree[index].lz2 * len1);
            tree[RIGHT].rsum = add(tree[RIGHT].rsum, tree[index].lz2 * len2);
        }
        tree[index].lz2 = 0;
    }
}

void update(int start, int end, int l, int r, int index, int mlt, int adv) {
    if (start > end || l > r || start > r || l > end) return;
    pushdown(l, r, index);
    if (start <= l && r <= end) {
        tree[index].rsum = mul(tree[index].rsum, mlt);
        tree[index].rsum = add(tree[index].rsum, adv * (r - l + 1));
        tree[index].lz1 = mlt;
        tree[index].lz2 = adv;
        return;
    }

    if (end <= MID) {
        update(start, end, l, MID, LEFT, mlt, adv);
    } else if (start >= MID + 1) {
        update(start, end, MID + 1, r, RIGHT, mlt, adv);
    } else {
        update(start, end, l, MID, LEFT, mlt, adv);
        update(start, end, MID + 1, r, RIGHT, mlt, adv);
    }
    tree[index].rsum = add(tree[LEFT].rsum, tree[RIGHT].rsum);
}

ll query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return 0;
    pushdown(l, r, index);
    if (start <= l && r <= end) return tree[index].rsum;
    if (end <= MID) {
        return query(start, end, l, MID, LEFT);
    } else if (start >= MID + 1) {
        return query(start, end, MID + 1, r, RIGHT);
    } 

    return add(query(start, end, l, MID, LEFT), query(start, end, MID + 1, r, RIGHT));
}

// insert x to the range [l, r]
// here we need to do the following things
// eliminate the interval from (l, r)
void insert(int l, int r, int x) {
    if (uncov[x].empty()) return;
    vector<pair<int, int>> tmp;
    auto iter = uncov[x].lower_bound(make_pair(l, 0));
    if (iter != uncov[x].begin()) {
        iter = prev(iter);
    }

    while (iter != uncov[x].end()) {
        if (iter->first > r) break;
        if (iter->second >= l) {
            tmp.push_back(*iter);
        }
        iter++;
    }
    // cout << "dealing with " << x << endl;
    // cout << "erase " << l << " " << r << endl;
    for (auto p : tmp) {
        // total overlap case
        // cout << p.first << " " << p.second << endl;
        if (p.second <= r && p.first >= l) {
            uncov[x].erase(p);
            update(p.first, p.second, 1, n, 1, ivt, 1);
        } else if (p.first >= l && p.second > r) {
            uncov[x].erase(p);
            uncov[x].insert(make_pair(r + 1, p.second));
            update(p.first, r, 1, n, 1, ivt, 1);
        } else if (p.first < l && p.second <= r) {
            uncov[x].erase(p);
            uncov[x].insert(make_pair(p.first, l - 1));
            update(l, p.second, 1, n, 1, ivt, 1);
        } else if (p.first < l && p.second > r) {
            uncov[x].erase(p);
            uncov[x].insert(make_pair(p.first, l - 1));
            uncov[x].insert(make_pair(r + 1, p.second));
            update(l, r, 1, n, 1, ivt, 1);
        }
    }
}

void calc() {
    ll p = mod - 2;
    ivt = 1;
    ll base = 2;
    while (p > 0) {
        if (p % 2 == 0) {
            base = mul(base, base);
            p /= 2;
        } else {
            ivt = mul(ivt, base);
            p--;
        }
    }
}

int main() {
    int q, i;
    scanf("%d%d", &n, &q);
    for (i = 1 ; i < MAX_SIZE; ++i) {
        tree[i].lz1 = 1;
        uncov[i].insert(make_pair(1, n));
    }

    calc();

    while (q > 0) {
        int t, l, r, x;
        scanf("%d%d%d", &t, &l, &r);
        if (t == 1) {
            scanf("%d", &x);
            update(l, r, 1, n, 1, 2, 0);
            insert(l, r, x);
        } else {
            printf("%I64d\n", query(l, r, 1, n, 1));
        }
        --q;
    }
    return 0;
}