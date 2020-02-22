#include <bits/stdc++.h>
#define MOD 1000000007
typedef long long ll;
using namespace std;

ll dp[11][64][1025][2];
int a[64];

ll dfs(int bs, int pos, int bt, bool limit, bool zero) {
   if (pos < 0) return (bt == 0 && !zero);
   if (dp[bs][pos][bt][zero] != -1 && !limit) return dp[bs][pos][bt][zero];
   int up = (limit ? a[pos] : (bs - 1));
   int i;
   ll ret = 0;
   for (i = 0; i <= up; i++) {
   	   if (zero && i == 0) {
   	   	  ret += dfs(bs, pos - 1, bt, limit && (i == up), zero);
	   } else {
	   	  ret += dfs(bs, pos - 1, bt ^ (1 << i), limit && (i == up), (zero && i == 0));
	   }
   }
   if (!limit) dp[bs][pos][bt][zero] = ret;
   return ret;
}

ll calc(ll x, int b) {
	 int len = 0;
	 while (x > 0) {
	 	   a[len++] = x % b;
	 	   x /= b;
	 }
	 return dfs(b, len - 1, 0, true, true);
}

int main() {
	int i, j, k;
	for (k = 0 ; k < 11; k++) {
		for (i = 0 ; i < 64; i++) {
			for (j = 0 ; j < 1025; j++) {
				dp[k][i][j][0] = dp[k][i][j][1] = -1;
			}
		}
	}
	
	int q;
	scanf("%d", &q);
	while (q > 0) {
		  ll l, r;
		  int b;
		  scanf("%d%lld%lld", &b, &l, &r);
		  printf("%lld\n", calc(r, b) -  calc(l-1, b));
		  q--;
	}
	return 0;
}
