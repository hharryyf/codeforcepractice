#include <bits/stdc++.h>
#define MOD 1000000007 
typedef long long ll;
using namespace std;

ll dp[68][132];
int a[68];
int k;

ll dfs(int pos, int rem, bool limit) {
	 if (pos < 0) return rem == 0;
	 if (dp[pos][rem + 66] != -1 && !limit) return dp[pos][rem + 66];
	 int up = limit ? a[pos] : 1;
	 int i;
	 ll ret = 0;
	 for (i = 0 ; i <= up; ++i) {
	 	 ret += dfs(pos - 1, rem - (i > 0), limit && (i == up));
	 }
	 
	 if (!limit) dp[pos][rem + 66] = ret;
	 return ret;
}

ll solve(ll n) {
   int i = 0;
   while (n > 0) {
   		 a[i++] = n % 2;
   		 n >>= 1;
   }
   return dfs(i - 1, k, true);
}

int main() {
	// binary search for the smallest number that has at least m numbers
	// that has k 1-bit
	ll m;
	int i, j;
	scanf("%lld%d", &m, &k);
	ll low = 1, high = 1e18;
	for (i = 0; i < 68; i++) {
		for (j = 0 ; j < 132; j++) {
			dp[i][j] = -1;
		}
	}
	ll ans = 1e18;
	while (low <= high) {
		  ll mid = low + ((high - low) >> 1ll);
		  if (solve(mid << 1) - solve(mid) >= m) {
		  	 ans = mid;
		  	 high = mid - 1;
		  } else {
		  	 low = mid + 1;
		  }
	}
	printf("%lld\n", ans);
	return 0;
}
