#include <bits/stdc++.h>
#define MAX_SIZE 103
typedef long long ll;
using namespace std;

const ll mod = 1e9 + 7;
int N, K;

struct Matrix {
    ll a[MAX_SIZE][MAX_SIZE];
    Matrix operator *(Matrix other) const {
        Matrix ret;
        int i, j, k;
        for (i = 0; i <= N; ++i) {
            for (j = 0; j <= N; ++j) {
                ret.a[i][j] = 0;
                for (k = 0 ; k <= N; ++k) {
                    ret.a[i][j] += a[i][k] * other.a[k][j];
                    ret.a[i][j] %= mod;
                }
            }
        }

        return ret;
    }
};

Matrix I;

Matrix fastpower(Matrix mt, ll p) {
    Matrix ret = I;
    while (p > 0) {
        if (p % 2 == 1) {
            ret = ret * mt;
            p--;
        } else {
            mt = mt * mt;
            p /= 2;
        }
    }

    return ret;
}

ll calc(ll v) {
    ll ret = 1, p = mod - 2;
    while (p > 0) {
        if (p % 2 == 1) {
            ret = ret * v;
            ret %= mod;
            p--;
        } else {
            v = v * v;
            v %= mod;
            p /= 2;
        }
    }

    return ret;
}

int inv[MAX_SIZE * MAX_SIZE];
int a[MAX_SIZE];
Matrix mt;

int main() {
    int i, cnt = 0;
    for (i = 1; i < (MAX_SIZE * MAX_SIZE); ++i) {
        inv[i] = calc(i);
    }

    scanf("%d%d", &N, &K);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &a[i]);
        if (a[i] == 0) {
            cnt++;
        }
        I.a[i][i] = 1;
    }
    I.a[0][0] = 1;
    if (cnt == 0 || cnt == N) {
        printf("1\n");
        return 0;
    }
    
    for (i = 0 ; i <= N; ++i) {
        ll iv = inv[N * (N - 1) / 2];
        if (i > 0) {
            if (cnt - (i - 1) >= 0 && N - cnt - (i - 1) >= 0) {
                mt.a[i][i-1] += 1ll * (cnt - (i - 1)) * (N - cnt - (i - 1)) * iv;
                mt.a[i][i-1] %= mod; 
            }
        }

        if (cnt - i >= 0 && N - cnt - i >= 0) {
            ll tol = N * (N - 1) / 2;
            tol -= 1ll * (cnt - i) * (N - cnt - i);
            tol -= 1ll * i * i;
            tol *= iv;
            tol %= mod;
            mt.a[i][i] += tol;
            mt.a[i][i] %= mod;
        }

        if (i < N) {
            if ((i + 1) <= cnt && N - cnt - (i + 1) >= 0) {
                mt.a[i][i + 1] += 1ll * (i + 1) * (i + 1) * iv;
                mt.a[i][i + 1] %= mod;
            }
        }
    }

    N = N - cnt;

    mt = fastpower(mt, K);
    /*
    for (i = 0 ; i <= N; ++i) {
        for (int j = 0 ; j <= N; ++j) {
            printf("%I64d ", mt.a[i][j]);
        }
        printf("\n");
    }*/
    
    int tol = 0;
    for (i = 1; i <= cnt; ++i) {
        tol += a[i];
    }

    printf("%I64d\n", (mt.a[0][tol] + mod) % mod);
    return 0;
}