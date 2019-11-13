#include <bits/stdc++.h>
#define MAX_SIZE 104
#define MOD 1000000007
using namespace std;
typedef long long ll;
struct matrix {
	int k;
	ll a[MAX_SIZE][MAX_SIZE];
};

matrix M;
matrix B;
matrix Z;

matrix matrixmul(matrix a, matrix b) {
	matrix ret = Z;
	ret.k = a.k;
	int i, j, k;
	for (i = 1; i <= ret.k; i++) {
		for (j = 1; j <= ret.k; j++) {
			for (k = 1; k <= ret.k; k++) {
				ret.a[i][j] = ret.a[i][j] + a.a[i][k] * b.a[k][j];
				ret.a[i][j] %= MOD;
			}
		}
	}
	return ret;
}

void matrixexp(ll t) {
	while (t > 0) {
		if (t % 2 == 0) {
			B = matrixmul(B, B);
			t = t / 2;
		} else {
			M = matrixmul(M, B);
			t--;
		}
	}
}

void preprocess() {
	ll n;
	int m;
	scanf("%lld%d", &n, &m);
	M.k = m;
	B.k = m;
	for (int i = 1; i <= m; i++) {
		M.a[i][i] = 1;
		if (i == 1) {
			B.a[1][1] = 1;
			B.a[1][m] = 1;
		} else {
			B.a[i][i-1] = 1;
		}
	}
	
	matrixexp(n);
	
	cout << M.a[1][1] << endl;
}

int main() {
	preprocess();
	return 0;
}
