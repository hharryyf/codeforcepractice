#include <bits/stdc++.h>
#define MOD 1000000007
typedef long long ll;
using namespace std;

struct Vector {
    ll a[17];
};

struct Matrix {
    ll a[17][17];
    Matrix operator *(Matrix other) const {
	    Matrix ret;
		int i, j, k;
		for (i = 0; i < 17; ++i) {
			for (j = 0 ; j < 17; ++j) {
				ret.a[i][j] = 0;
				for (k = 0 ; k < 17; ++k) {
					ret.a[i][j] += a[i][k] * other.a[k][j];
					ret.a[i][j] %= MOD;
				}
			}
		}	   
		return ret;
	}
	
	Vector operator ^(Vector other) const {
        Vector ret;
		int i, j;
		for (i = 0 ; i < 17; ++i) {
			ret.a[i] = 0;
			for (j = 0; j < 17; ++j) {
				ret.a[i] += a[i][j] * other.a[j];
				ret.a[i] %= MOD;
			}	
		} 
		return ret;
	}
};

Matrix matrix[17];
Vector ans;
Matrix I;

Matrix fastpower(Matrix mt, ll p) {
	   Matrix ret = I;
       Matrix base = mt;
	   while (p > 0) {
           if (p % 2 == 0) {
		   	  base = base * base;
		   	  p >>= 1;
		   } else {
		      ret = ret * base;
		      p--;
		   }
	   }
	   return ret;
}

void create() {
	 int i, j, k;
	 int dx[3] = {1, -1, 0};
	 for (i = 0; i < 17; ++i) {
	 	 I.a[i][i] = 1;
         for (j = 0; j <= i; ++j) {
			 for (k = 0; k < 3; ++k) {
			 	 int ty = j + dx[k];
			 	 if (ty >= 0 && ty <= i) matrix[i].a[j][ty] = 1;
			 }
         }
	 }
	 
	 ans.a[0] = 1;
}

int main() {
	create();
	int n, i;
	ll k;
	scanf("%d%lld", &n, &k);
	for (i = 0; i < n; i++) {
		ll l, r;
		int c;
		scanf("%lld%lld%d", &l, &r, &c);
		r = min(r, k);
		ans = fastpower(matrix[c], r - l) ^ ans;
	}
	printf("%lld\n", ans.a[0] % MOD);
	
	return 0;
}
