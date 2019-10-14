#include <bits/stdc++.h>
#define MOD 998244353

typedef long long ll;
using namespace std;

// dp[i][j].first  ==> the total number that could be added to the sum when
// the current state is i and is at the jth position
pair<ll, ll> dp[1100][20];
int bitcnt[1100];
ll p10[21];
string a;
int n, k;

pair<ll,ll> dfs(int bi, int pos, int flag, int leading) {
	// if (pos == n && bi == 1) return make_pair(0,0);
	if (pos == -1) return make_pair(0, 1);
	if (dp[bi][pos].second != -1 && !flag && !leading) {
		return dp[bi][pos];
	}
	
	ll ans = 0;
	ll cnt = 0;
	int upper = (flag ? a[n - pos - 1] - '0' : 9);
	for (int i = 0 ; i <= upper; i++) {
		int nextstate = (bi | (1 << i));
		if ((bi & (1 << i)) == 0 && !(leading && i == 0)) {
			if (bitcnt[nextstate] > k) continue;
			pair<ll, ll> p = dfs(nextstate, pos - 1, flag && (i == upper), leading && (i == 0));
			cnt = (cnt + p.second) % MOD;
			ans = (ans + ((((p.second * i) % MOD) * p10[pos]) % MOD+ p.first) % MOD) % MOD;
		} else {
			pair<ll, ll> p = dfs(bi, pos - 1, flag && (i == upper), leading && (i == 0));
			cnt = (cnt + p.second) % MOD;
			ans = (ans + ((((p.second * i) % MOD) * p10[pos]) % MOD + p.first) % MOD) % MOD;
		}
	}
	
	if (!flag && !leading) {
		dp[bi][pos] = make_pair(ans % MOD, cnt % MOD);
	}
	return make_pair(ans % MOD, cnt % MOD);
}

ll solve(ll num) {
	a = to_string(num);
	n = (int) a.length();
	pair<ll, ll> p = dfs(0 , n - 1, 1, 1);
	return p.first % MOD;
}

int main() {
	ll l, r;
	int i, j;
	p10[0] = 1;
	for (i = 1; i <= 20; i++) {
		p10[i] = (p10[i-1] * 10) % MOD;
	}
	
	for (i = 0 ; i < 1100; i++) {
		for (j = 0 ; j < 20; j++) {
			dp[i][j] = make_pair(0, -1);
		}
	}
	
	bitcnt[0] = 0;
	bitcnt[1] = 1;
	for(i = 2;i < 1100;i++) 
		bitcnt[i] = bitcnt[i-(i & -i)] + 1;
	
	
	cin >> l >> r >> k;
	cout << (solve(r) - solve(l - 1) + MOD) % MOD<< endl;
	return 0;
}
