#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;

int sz[MAX_SIZE];
int cycle[MAX_SIZE];
int f[MAX_SIZE];

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int a = find(x), b = find(y);
    if (a != b) {
        if (sz[a] < sz[b]) {
            cycle[b] |= cycle[a];
            f[a] = b;
            sz[b] += sz[a];
        } else {
            cycle[a] |= cycle[b];
            f[b] = a;
            sz[a] += sz[b];
        }
    } else {
        cycle[a] = 1;
    }
}

void init() {
    int i;
    for (i = 0 ; i < MAX_SIZE; ++i) {
        f[i] = i;
        cycle[i] = 0;
        sz[i] = 1;
    }
}

struct point {
    int x, y, id;
};

point pt[MAX_SIZE];

static bool cmp1(const point &p1, const point &p2) {
    if (p1.x != p2.x) return p1.x < p2.x;
    return p1.y < p2.y;
}

static bool cmp2(const point &p1, const point &p2) {
    if (p1.y != p2.y) return p1.y < p2.y;
    return p1.x < p2.x;
}

set<int> gx[MAX_SIZE];
set<int> gy[MAX_SIZE];

ll fastpower(ll p) {
    ll base = 2;
    ll ret = 1;
    while (p > 0) {
        if (p % 2 == 0) {
            base = base * base;
            p /= 2;
            base %= mod;
        } else {
            ret = ret * base;
            ret %= mod;
            p--;
        }
    }
    return ret;
}

int main() {
    init();
    int i, n;
    ll ans = 1;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d%d", &pt[i].x, &pt[i].y);
        pt[i].id = i;
    }

    sort(pt + 1, pt + 1 + n, cmp1);

    for (i = 2; i <= n; ++i) {
        if (pt[i].x == pt[i-1].x) {
            unionset(pt[i].id, pt[i-1].id);
        }
    }

    sort(pt + 1, pt + 1 + n, cmp2);

    for (i = 2; i <= n; ++i) {
        if (pt[i].y == pt[i-1].y) {
            unionset(pt[i].id, pt[i-1].id);
        }
    }

    for (i = 1; i <= n; ++i) {
        gx[find(pt[i].id)].insert(pt[i].x);
        gy[find(pt[i].id)].insert(pt[i].y);
    }

    for (i = 1; i <= n; ++i) {
        if (find(i) == i) {
            if (cycle[i]) {
                int xsz = gx[i].size();
                int ysz = gy[i].size();
                ans = ans * fastpower(xsz);
                ans %= mod;
                ans = ans * fastpower(ysz);
                ans %= mod;
            } else {
                ans = ans * (fastpower(sz[i] + 1) - 1);
                ans %= mod;
                if (ans < 0) ans += mod;
            }
        }
    }

    printf("%I64d\n", ans);
    return 0;
}