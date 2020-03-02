#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 100011
typedef long long ll;
using namespace std;
// dp[i] refers to the largest possible 
// number with the end ball of color i
ll dp[MAX_SIZE];
int v[MAX_SIZE];
int c[MAX_SIZE];
int main() {
	int i, n, q;
	scanf("%d%d", &n, &q);
	for (i = 1; i <= n; i++) scanf("%d", &v[i]);
	for (i = 1; i <= n; i++) scanf("%d", &c[i]);
	
	while (q > 0) {
		for (i = 1; i < MAX_SIZE; i++) dp[i] = -1e16;
		ll a, b;
		// the ending color with the maximum dp
		// the ending color with the second maximum dp
		int first = 0, second = -1;
		scanf("%lld%lld", &a, &b);
		for (i = 1; i <= n; i++) {
			ll costa = a * v[i], costb = b * v[i];
			dp[c[i]] = max(dp[c[i]], dp[c[i]] + costa);
			if (c[i] != first) {
			   dp[c[i]] = max(dp[c[i]], dp[first] + costb);
			} else {
			   dp[c[i]] = max(dp[c[i]], dp[second] + costb);
			}
			
			if (first != c[i]) {
			   if (dp[c[i]] > dp[first]) {
			   	  second = first, first = c[i];
			   } else if (dp[c[i]] > dp[second]) {
			   	  second = c[i];
			   }
			}
		}  
		
		printf("%lld\n", dp[first]);
        q--;
	}
	return 0;
}

