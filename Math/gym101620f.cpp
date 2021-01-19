#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll inv(ll val, int p) {
    ll ret = 1, pw = p - 2;
    while (pw > 0) {
        if (pw % 2 == 1) {
            ret = ret * val;
            ret %= p;
            pw--;
        } else {
            val = val * val;
            val %= p;
            pw /= 2;
        }
    }
    return ret;
}

int main() {
    ll N;
    int p, r, i;
    cin >> N >> p >> r;
    if (N >= p * 2) {
        if (r == 0) {
            printf("2 1\n");
            return 0;
        }

        printf("-1 -1\n");
        return 0;
    }

    if (N < p) {
        ll tol = 1;
        for (i = 2; i <= N; ++i) {
            tol = tol * i;
            tol %= p;
        }

        ll iv = inv(tol, p);
        for (i = 2; i <= N; ++i) {
            ll desire = 1ll * ((iv * r) % p) * i;
            desire %= p;
            if (desire < i && desire > 0) {
                printf("%d %I64d\n", i, desire);
                return 0;
            }
        }
        printf("-1 -1\n");
        return 0;
    }

    // 2 * p > N >= p
    if (r == 0) {
        if (N == 2) {
            printf("-1 -1\n");
            return 0;
        }
        if (N == p) {
            printf("2 1\n");
        } else {
            printf("%d %d\n", p + 1, p);
        }
        return 0;
    }

    // r != 0, fix p
    ll tol = 1;
    for (i = 2; i <= N; ++i) {
        if (i == p) continue;
        tol = tol * i;
        tol %= p;
    }

    tol = inv(tol, p);
    ll desire = (tol * r) % p;
    if (desire < p && desire > 0) {
        printf("%d %I64d\n", p, desire);
        return 0;
    }
    printf("-1 -1\n");
    return 0;
}