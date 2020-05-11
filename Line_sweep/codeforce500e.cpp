#include <bits/stdc++.h>
#define MAX_SIZE 262192
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
typedef long long ll;
using namespace std;
// the right endpoint, query id
vector<pair<int, int>> g[MAX_SIZE];
struct segt {
    // this is a range sum tree, which supports range
    // query and set a certain range to 0
    ll value, lz;
};

vector<int> disc;
segt tree[MAX_SIZE << 2];
pair<int, int> domino[MAX_SIZE];
int tmp[MAX_SIZE << 1];
ll ans[MAX_SIZE];
void pushdown(int l, int r, int index) {
    if (l > r) return;
    if (tree[index].lz != -1) {
        if (l != r) {
            tree[LEFT].value = 1ll * tree[index].lz * (MID - l + 1);
            tree[RIGHT].value = 1ll * tree[index].lz * (r - MID);
            tree[LEFT].lz = tree[RIGHT].lz = tree[index].lz;
        }
        tree[index].lz = -1;
    }
}

void update(int start, int end, int l, int r, int index, int val) {
    if (start > end || l > r || start > r || l > end) return;
    pushdown(l, r, index);
    if (start <= l && r <= end) {
        tree[index].lz = val;
        tree[index].value = 1ll * val * (r - l + 1);
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
    tree[index].value = tree[LEFT].value + tree[RIGHT].value;
}

ll query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return 0;
    pushdown(l, r, index);
    if (start <= l && r <= end) return tree[index].value;
    if (end <= MID) {
        return query(start, end, l, MID, LEFT);
    }

    if (start >= MID + 1) {
        return query(start, end, MID + 1, r, RIGHT);
    }

    return query(start, end, l, MID, LEFT) + query(start, end, MID + 1, r, RIGHT);
}

void build(int l, int r, int index) {
    if (l > r) return;
    tree[index].lz = -1;
    if (l == r) {
        tree[index].value = disc[l+1] - disc[l];
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    tree[index].value = tree[LEFT].value + tree[RIGHT].value;
}

int main() {
    int n, i, j = 0;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d%d", &domino[i].first, &domino[i].second);
        tmp[j++] = domino[i].first;
        tmp[j++] = domino[i].second + domino[i].first;
    }

    sort(tmp, tmp + j);

    for (i = 0 ; i < j; ++i) {
        if (i == 0 || tmp[i] != tmp[i-1]) {
            disc.push_back(tmp[i]);
        }
    }

    int sz = (int) disc.size() - 2;

    build(0, sz, 1);
    int q;
    scanf("%d", &q);
    for (i = 1 ; i <= q; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        g[x].emplace_back(y, i);
    }

    for (i = n; i >= 1; --i) {
        int L = lower_bound(disc.begin(), disc.end(), domino[i].first) - disc.begin();
        int R = lower_bound(disc.begin(), disc.end(), domino[i].first + domino[i].second) - disc.begin() - 1;
        update(L, R, 0, sz, 1, 0);
        for (auto np : g[i]) {
            int idx = lower_bound(disc.begin(), disc.end(), domino[np.first].first) - disc.begin() - 1;
            ans[np.second] = query(L, idx, 0, sz, 1);
        }
    }

    for (i = 1; i <= q; ++i) {
        printf("%I64d\n", ans[i]);
    }
    return 0;
}