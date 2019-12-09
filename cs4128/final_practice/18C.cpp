#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 1000011
typedef long long ll;


using namespace std;

ll fac[MAX_SIZE];

int n;

ll ivt(ll num) {
	ll base = num, exp = MOD - 2;
	ll ret = 1;
	while (exp > 0) {
		if (exp % 2 == 0) {
			base = base * base;
			base = base % MOD;
			exp /= 2;
		} else {
			ret = ret * base;
			ret %= MOD;
			exp--;
		}
	}
	
	return ret % MOD;
}

void precompute() {
	fac[0] = 1;
	int i;
	for (i = 1; i <= MAX_SIZE; i++) fac[i] = (fac[i-1] * i) % MOD;
}

int main() {
	scanf("%d", &n);
	int i;
	precompute();
	unordered_map<int, int> cnt;
	for (i = 1; i <= n; i++) {
		int v;
		scanf("%d", &v);
		cnt[v]++;
	}
	
	ll ret = fac[n];
	
	unordered_map<int, int> :: iterator iter = cnt.begin();
	while (iter != cnt.end()) {
		ret = ret * ivt(fac[iter->second]);
		ret %= MOD;
		iter++;
	}
	
	cout << ret % MOD << endl;	
	return 0;
}
