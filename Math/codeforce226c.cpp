#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int MOD;

/*
	the property we are going to use on Fibonacci numbers is
	gcd(Fib(v1), Fib(v2)) = Fib(gcd(v1, v2))
	
	Hence, the problem is changed to the following, give [l, r] and k
	find the maximum number v in [l, r] such that there's at least k numbers 
	that are a multiple of v
	
	step 1. r / v - l / v >= k, find maximum v
	
	Then, the solution to this problem is Fib(v) % MOD
	step 2. fib(v)
*/


struct matrix {
	ll a[2][2];
	matrix operator *(matrix other) const {
		int i, j, k;
		matrix m;
		for (i = 0 ; i < 2; i++) {
			for (j = 0 ; j < 2; j++) {
				m.a[i][j] = 0;
				for (k = 0 ; k < 2; k++) {
					m.a[i][j] += a[i][k] * other.a[k][j];
					m.a[i][j] %= MOD;
				}
			}
		}
		return m;
	}
};

matrix fastmul(ll p) {
	matrix ret;
	ret.a[0][0] = ret.a[1][1] = 1;
	ret.a[0][1] = ret.a[1][0] = 0;
	matrix base;
	base.a[0][0] = base.a[0][1] = base.a[1][0] = 1;
	base.a[1][1] = 0;
	while (p > 0) {
		if (p % 2 == 0) {
			base = base * base;
			p >>= 1;
		} else {
			ret = ret * base;
			--p;
		}
	}

	return ret;
}

ll count(ll L, ll R, ll k) {
	ll left = L / k, right = R / k;
	
	if (L % k != 0) left++;
	
	return right - left + 1;
}

/*
   note that floor(n / i) has only sqrt(n) many values
*/

int main() {
	// freopen("input.txt", "r", stdin);
	ll l, r, k;
	while (scanf("%d%I64d%I64d%I64d", &MOD, &l, &r, &k) != EOF) {
		ll v = 1, i;
		for (i = 1; i * i <= r; i++) {
			if (count(l, r, i) >= k) {
				v = max(v, i);
			}
			if (count(l, r, r / i) >= k) {
				v = max(v, r / i);
			}
		}
		matrix m = fastmul(v-1);
		printf("%I64d\n", m.a[0][0] % MOD);
	}
	return 0;
}