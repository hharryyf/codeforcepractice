#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
#define MAX_SIZE 524292
typedef long long ll;
using namespace std;

const ll mod = 1e9 + 7;

struct segt {
    // for a leaf node d = wt_i * (x_i - i)
    ll wt, d;
    segt operator + (segt other) const {
        segt ret;
        ret.wt = this->wt + other.wt;
        ret.d = (this->d + other.d) % mod;
        return ret;
    }
};

segt tree[MAX_SIZE];
ll x[MAX_SIZE], w[MAX_SIZE];
int n, q;

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        tree[index].wt = w[l];
        tree[index].d = w[l] * (x[l] - l);
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    tree[index] = tree[LEFT] + tree[RIGHT];
}
// update w[pt] to val
void update(int pt, int l, int r, int index, ll val) {
    if (l > r || pt < l || pt > r) return;
    if (l == r) {
        w[pt] = val;
        tree[index].wt = w[pt];
        tree[index].d = w[pt] * (x[pt] - l);
        return;
    }

    if (pt <= MID) {
        update(pt, l, MID, LEFT, val);
    } else {
        update(pt, MID + 1, r, RIGHT, val);
    }

    tree[index] = tree[LEFT] + tree[RIGHT];
}

segt query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return tree[0];
    if (start <= l && r <= end) return tree[index];
    if (end <= MID) {
        return query(start, end, l, MID, LEFT);
    }

    if (start >= MID + 1) {
        return query(start, end, MID + 1, r, RIGHT);
    }

    return query(start, end, l, MID, LEFT) + query(start, end, MID + 1, r, RIGHT);
}

int main() {
    int i;
    scanf("%d%d", &n, &q);
    for (i = 1; i <= n; ++i) {
        scanf("%I64d", &x[i]);
    }

    for (i = 1; i <= n; ++i) {
        scanf("%I64d", &w[i]);
    }

    build(1, n, 1);

    while (q-- > 0) {
        ll L, R;
        scanf("%I64d%I64d", &L, &R);
        if (L < 0) {
            update(-L, 1, n, 1, R);
        } else {
            if (L == R) {
                printf("0\n");
                continue;
            }
            // query [x, y] moving cost
            int low = L, high = R;
            int pivot = low;
            auto W = query(L, R, 1, n, 1).wt;
            while (low <= high) {
                int mid = (low + high) >> 1;
                auto ret1 = query(L, mid, 1, n, 1);
                if (ret1.wt >= W - ret1.wt) {
                    pivot = mid;
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }

            // moving all [x, pivot] to pivot
            auto ret1 = query(L, pivot, 1, n, 1);
            auto ret2 = query(pivot + 1, R, 1, n, 1);
            // moving all [pivot + 1, y] to pivot
            ll cost1 = (x[pivot] - pivot) * (ret1.wt % mod) - ret1.d;
            ll cost2 = ret2.d + (ret2.wt % mod) * (pivot - x[pivot]);
            ll ans = (cost1 + cost2) % mod;
            if (ans < 0) ans += mod;
            printf("%I64d\n", ans);
        }
    }
    return 0;
}