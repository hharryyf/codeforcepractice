#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 262192
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
typedef long long ll;
using namespace std;

const ll inf = 1e13;

struct segt {
    // value is the answer 
    ll value;
    vector<ll> vc;
};

segt tree[MAX_SIZE];
ll a[MAX_SIZE];

void build(int l, int r, int index) {
    if (l > r) return;
    tree[index].value = inf;
    int i;
    for (i = l; i <= r; ++i) tree[index].vc.push_back(a[i]);
    sort(tree[index].vc.begin(), tree[index].vc.end());
    if (l == r) {
        return;
    }
    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
}

ll curr = inf;
// update val=a[pt] to the range tree of range [start, end]
void update(int start, int end, int l, int r, int index, ll val) {
    if (start > end || l > r || start > r || l > end) return;
    if (start <= l && r <= end) {
        // pruning condition
        int idx = lower_bound(tree[index].vc.begin(), tree[index].vc.end(), val) - tree[index].vc.begin();
        if (idx < r - l + 1) {
            tree[index].value = min(tree[index].value, tree[index].vc[idx] - val);
        }

        if (idx > 0) {
            tree[index].value = min(tree[index].value, -tree[index].vc[idx-1] + val);
        }

        if (tree[index].value >= curr) return;


        if (l == r) {
            tree[index].value = min(abs(a[l] - val), tree[index].value);    
            curr = min(curr, tree[index].value);
            return;
        }
    }
    if (end <= MID) {
        update(start, end, l, MID, LEFT, val);
    } else if (start >= MID + 1) {
        update(start, end, MID + 1, r, RIGHT, val);
    } else {
        update(start, end, MID + 1, r, RIGHT, val);
        update(start, end, l, MID, LEFT, val);
    }
    tree[index].value = min(tree[LEFT].value, tree[RIGHT].value);
}

ll query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return inf;
    if (start <= l && r <= end) {
        return tree[index].value;
    }
    if (end <= MID) {
        return query(start, end, l, MID, LEFT);
    } else if (start >= MID + 1) {
        return query(start, end, MID + 1, r, RIGHT);
    }

    return min(query(start, end, l, MID, LEFT), query(start, end, MID + 1, r, RIGHT));
}

struct qrs {
    int l, r, id;
    bool operator < (qrs other) const {
        return r < other.r;
    }
};

qrs q[MAX_SIZE << 1];
ll ans[MAX_SIZE << 1];

int main() {
    int n, i, j, m;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) scanf("%I64d", &a[i]);
    build(1, n, 1);
    scanf("%d", &m);
    for (i = 1; i <= m; ++i) {
        scanf("%d%d", &q[i].l, &q[i].r);
        q[i].id = i;
    }

    sort(q + 1, q + 1 + m);
    for (i = 1, j = 2; i <= m; ++i) {
        while (j <= n && j <= q[i].r) {
            curr = inf;
            update(1, j - 1, 1, n, 1, a[j]);
            j++;
        }
        ans[q[i].id] = query(q[i].l, q[i].r, 1, n, 1);
    }

    for (i = 1; i <= m; ++i) {
        printf("%I64d\n", ans[i]);
    }
    return 0;
}

