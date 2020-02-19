#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int shift = 1800;

ll dp[20][20][3611];
int a[20];
ll dfs(int pos, int pidx, int bvalue, bool limit) {
   if (pos < 0) return bvalue == 0;
   if (!limit && dp[pos][pidx][bvalue + shift] != -1)
   	  return dp[pos][pidx][bvalue + shift];
   ll ans = 0;
   int i;
   int up = limit ? a[pos] : 9;
   for (i = 0 ; i <= up; i++) {
   	   ans += dfs(pos - 1, pidx, bvalue + (pos - pidx) * i, limit && (i == up));
   }
   if (!limit) dp[pos][pidx][bvalue + shift] = ans;
   return ans;
}

ll calc(ll x) {
	 int len = 0;
	 int i;
	 while (x > 0) {
	 	   a[len++] = x % 10;
	 	   x /= 10;
	 }
	 ll ret = 0;
	 for (i = 0 ; i < len; i++) {
	 	 ret += dfs(len - 1, i, 0, true);
	 }
	 return ret - (len - 1);
}

int main() {
	int T, i, j, k;
	for (i = 0 ; i < 20; i++) {
		for (j = 0 ; j < 20; j++) {
			for (k = 0 ; k < 3611; k++) {
				dp[i][j][k] = -1;
			}
		}
	}
	scanf("%d", &T);
	while (T > 0) {
		  ll x, y;
		  scanf("%lld%lld", &x, &y);
		  if (x == 0) {
		  	  printf("%lld\n", calc(y));
		  } else {
	      	  printf("%lld\n", calc(y) - calc(x-1));
		  }
		  T--;
	}
	return 0;
}
