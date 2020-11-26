#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

struct Matrix {
    ll a[3][3];
    
    void init() {
        int i, j;
        for (i = 0 ; i < 3; ++i) {
            for (j = 0 ; j < 3; ++j) {
                a[i][j] = 0;
            }
        }
    }
    
    Matrix operator *(Matrix other) const {
        Matrix ret;
        int i, j, k;
        for (i = 0; i < 3; ++i) {
            for (j = 0 ; j < 3; ++j) {
                ret.a[i][j] = 0;
                for (k = 0 ; k < 3; ++k) {
                    ret.a[i][j] += a[i][k] * other.a[k][j];
                    ret.a[i][j] %= mod - 1;
                }
            }
        }

        return ret;
    }
};

Matrix I;

void init() {
    I.a[0][0] = I.a[1][1] = I.a[2][2] = 1;
}

Matrix fastmatrix(Matrix mt, ll p) {
    Matrix ret = I;
    while (p > 0) {
        if (p % 2 == 0) {
            mt = mt * mt;
            p /= 2;
        } else {
            ret = ret * mt;
            p--;
        }
    }
    return ret;
}

ll fastpower(ll val, ll p) {
    ll ret = 1;
    val %= mod;
    while (p > 0) {
        if (p % 2 == 0) {
            val = val * val;
            val %= mod;
            p /= 2;
        } else {
            ret = ret * val;
            ret %= mod;
            p--;
        }
    }

    return ret;
}

ll mul(ll v, ll u) {
    return (v * u) % mod;
}

int main() {
    init();
    Matrix mt;
    mt.init();
    mt.a[0][0] = mt.a[0][1] = mt.a[0][2] = mt.a[1][0] = mt.a[2][1] = 1;
    ll n, f1, f2, f3, c;
    cin >> n >> f1 >> f2 >> f3 >> c;
    mt = fastmatrix(mt, n - 3);
    ll p3 = mt.a[0][0];
    ll p2 = mt.a[0][1];
    ll p1 = mt.a[0][2];
    ll F1 = fastpower(mul(f1, c), p1), F2 = fastpower(mul(mul(f2, c), c), p2), F3 = fastpower(mul(mul(mul(f3, c), c), c), p3);
    cout << mul(mul(mul(F1, F2), F3), fastpower(fastpower(c, n), mod - 2)) << endl;
    return 0;
}