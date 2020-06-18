#include <bits/stdc++.h>
#define MAX_SIZE 2511
typedef long long ll;
using namespace std;

struct encoder {
    int mod = 1e9 + 7;
    encoder(int x = 1e9 + 7) {
        this->mod = x;
    }

    ll getcode(int x, int y) {
        return x * mod + y;
    }
};

struct BIT {
    encoder e;
    ll a[MAX_SIZE][MAX_SIZE];
    int n, m;

    void init(int n=MAX_SIZE-1, int m=MAX_SIZE-1, int mod=1e9+7) {
        this->n = n, this->m = m;
        this->e = encoder(mod);
    }

    int shift(int x) {
        return x & (-x);
    }

    void add(int x, int y, ll val) {
        if (x == 0 || y == 0) return;
        int i, j;
        for (i = x; i <= n; i += shift(i)) {
            for (j = y; j <= m; j += shift(j)) {
                a[i][j] += val;
            }
        }
    }

    ll query(int x, int y) {
        int i, j;
        ll ret = 0;
        for (i = x; i > 0; i -= shift(i)) {
            for (j = y; j > 0; j -= shift(j)) {
                ret += a[i][j];
            }
        }
        return ret;
    }

    void update(int x1, int y1, int x2, int y2, int tp) {
        ll val = e.getcode(x2, y2) * tp;
        add(x1 , y1, val);
        add(x1, y2 + 1, -val);
        add(x2 + 1, y1, -val);
        add(x2 + 1,y2 + 1, val);
    }
};

BIT t1, t2;

int main() {
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    t1.init(n, m, 1e9 + 7);
    t2.init(n, m, 19260817);
    while (q-- > 0) {
        int tp, x1, y1, x2, y2;
        scanf("%d%d%d%d%d", &tp, &x1, &y1, &x2, &y2);
        if (tp == 1) {
            t1.update(x1, y1, x2, y2, 1);
            t2.update(x1, y1, x2, y2, 1);
        } else if (tp == 2) {
            t1.update(x1, y1, x2, y2, -1);
            t2.update(x1, y1, x2, y2, -1);
        } else {
            printf("%s\n", (t1.query(x1, y1) == t1.query(x2, y2) && t2.query(x1, y1) == t2.query(x2, y2)) ? "Yes" : "No");
        }
    }   
    return 0;
}