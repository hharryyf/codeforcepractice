#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2,fma") 
#include <bits/stdc++.h>
#define MAX_SIZE 256
typedef int ll;
using namespace std;
const ll mod = 1e9;
int N;
struct Matrix {
    ll m[MAX_SIZE][MAX_SIZE];
    Matrix operator ^(Matrix other) const {
        Matrix ret;
        int i, j, k;
        for (i = 0 ; i < N; ++i) {
            for (j = 0 ; j < N; ++j) {
                ret.m[i][j] = 0;
                for (k = 0 ; k < N; ++k) {
                    ret.m[i][j] += (1ll * m[i][k] * other.m[k][j]) % mod;
                    if (ret.m[i][j] >= mod) ret.m[i][j] -= mod;
                }
            }
        }
        return ret;
    }
};

Matrix I;

Matrix fastpower(Matrix m, long long p) {
    Matrix ret = I, base = m;
    while (p > 0) {
        if (p % 2 == 0) {
            p = p / 2;
            base = base ^ base;
        } else {
            ret = ret ^ base;
            p--;
        }
    }

    return ret;
}

Matrix mt;
int n;
long long m;

void dfs(int pos, int curr, int nxt) {
    if (pos == n) {
        mt.m[curr][nxt]++;
        return;
    }

    if (pos > n) return;
    if (curr & (1 << pos)) {
        dfs(pos + 1, curr, nxt);
        dfs(pos + 1, curr, nxt | (1 << pos));
        if (curr & (1 << (pos+1))) {
            if (pos + 2 <= n) {
                dfs(pos + 2, curr, nxt | (1 << pos) | (1 << (pos+1)));
            }
        }
    } else {
        dfs(pos + 1, curr, nxt | (1 << pos));
    }
}

int main() {
    int i;
    cin >> n >> m;
    N = 1 << n;
    for (i = 0 ; i < N; ++i) {
        dfs(0, i, 0);
    }

    for (i = 0 ; i < N; ++i) {
        I.m[i][i] = 1;
    }

    mt = fastpower(mt, m);
    printf("%d\n", mt.m[N-1][N-1]);
    return 0;
}