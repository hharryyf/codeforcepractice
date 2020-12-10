#include <bits/stdc++.h>
#define MAX_SIZE 100011
typedef long long ll;
using namespace std;
int N;
struct BIT {
    ll tree[MAX_SIZE];
    int shift(int x) {
        return x & (-x);
    }

    void update(int x, ll val) {
        if (x <= 0) return;
        while (x <= N) {
            tree[x] += val;
            x += shift(x);
        }
    }

    ll query(int x) {
        ll ret = 0;
        while (x > 0) {
            ret = ret + tree[x];
            x -= shift(x);
        }   
        return ret;
    }
};

BIT t1, t2;
int a[MAX_SIZE];

int main() {
    int i;
    double ans = 0;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) scanf("%d", &a[i]);

    for (i = 1; i <= N; ++i) {
        ans = ans + 1.0 * i * (i - 1) * (N - i + 1);
    }

    for (i = 1; i <= N; ++i) {
        ll tol = t1.query(N), tol2 = t2.query(N);
        ans = ans + 2.0 * (tol - t1.query(a[i])) * (1ll * N * N + N) - 2.0 * (tol2 - t2.query(a[i])) * (2.0 * N + 2 - 2 * i);
        t1.update(a[i], 1);
        t2.update(a[i], i);
    }
    
    ans = ans / (2.0 * N * (N + 1));
    printf("%.20lf\n", ans);
    return 0;
}