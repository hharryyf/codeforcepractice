#include <bits/stdc++.h>
#define MAX_SIZE 524292
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
using namespace std;
typedef long long ll;
const ll mod = 998244353;

struct segt {
    ll tree[MAX_SIZE];
    ll lz[MAX_SIZE];
    void pushdown(int l, int r, int index) {
        if (l > r) return;
        if (lz[index] != 0) {
            if (l != r) {
                tree[LEFT] += 1ll * (MID - l + 1) * lz[index];
                tree[RIGHT] += 1ll * (r - MID) * lz[index];
                lz[LEFT] += lz[index];
                lz[RIGHT] += lz[index];
            }
            lz[index] = 0;
        }
    }

    void update(int start, int end, int l, int r, int index, int val) {
        if (start > end || l > r || start > r || l > end) return;
        pushdown(l, r, index);
        if (start <= l && r <= end) {
            tree[index] += 1ll * val * (r - l + 1);
            lz[index] += val;
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

        tree[index] = tree[LEFT] + tree[RIGHT];
    }

    ll query(int start, int end, int l, int r, int index) {
        if (start > end || l > r || start > r || l > end) return 0;
        pushdown(l, r, index);
        if (start <= l && r <= end) return tree[index];
        if (end <= MID) return query(start, end, l, MID, LEFT);
        if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT);
        return query(start, end, l, MID, LEFT) + query(start, end, MID + 1, r, RIGHT);
    }
};

int visited[MAX_SIZE];
vector<int> disc1, disc2;
ll f[MAX_SIZE], fac[MAX_SIZE];
int a[MAX_SIZE];
int N;
segt big, small, ivt;

ll inv(int v) {
    ll base = v, p = mod - 2;
    ll ret = 1;
    while (p > 0) {
        if (p & 1) {
            ret = ret * base;
            ret %= mod;
            --p;
        } else {
            base = base * base;
            base %= mod;
            p >>= 1;
        }
    }

    return ret;
}

void precompute() {
    int i;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &a[i]);
        if (a[i] != -1) {
            visited[a[i]] = 1;
            disc1.push_back(a[i]);
        }
    }

    sort(disc1.begin(), disc1.end());
    fac[0] = 1;
    f[0] = f[1] = 0;
    for (i = 1; i <= N; ++i) {
        fac[i] = fac[i-1] * i;
        fac[i] %= mod;
        if (!visited[i]) disc2.push_back(i);
    }

    for (i = 2; i <= N; ++i) {
        f[i] = f[i-1] * i + ((fac[i] * (i - 1)) % mod) * inv(2);
        f[i] %= mod;
    }
}

int main() {
    int i;
    ll ans = 0;
    precompute();
    int sz1 = (int) disc1.size(), sz2 = (int) disc2.size();
    ans = f[sz2];
    for (i = 1; i <= N; ++i) {
        if (a[i] != -1) {
            int idx = lower_bound(disc1.begin(), disc1.end(), a[i]) - disc1.begin();
            int idx2 = lower_bound(disc2.begin(), disc2.end(), a[i]) - disc2.begin();
            ans += (ivt.query(idx + 1, sz1 - 1, 0, sz1 - 1, 1) * fac[sz2]) % mod;
            ans %= mod;
            ivt.update(idx, idx, 0, sz1 - 1, 1, 1);
            small.update(idx2, sz2 - 1, 0, sz2 - 1, 1, 1);
        }
    }

    for (i = 1; i <= N; ++i) {
        if (a[i] != -1) {
            int idx = lower_bound(disc2.begin(), disc2.end(), a[i]) - disc2.begin();
            big.update(0, idx - 1, 0, sz2 - 1, 1, 1);
            small.update(idx, sz2 - 1, 0, sz2 - 1, 1, -1);
        } else {
            ll ret = big.query(0, sz2 - 1, 0, sz2 - 1, 1);
            ret += small.query(0, sz2 - 1, 0, sz2 - 1, 1);
            // cout << ret << endl;
            ret %= mod;
            ret *= fac[sz2 - 1];
            ans = ans + ret;
            ans %= mod;
        }
    }
    cout << (ans * inv(fac[sz2])) % mod << endl;
    return 0;
}