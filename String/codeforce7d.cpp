#pragma GCC optimize(3)
#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 5000011
using namespace std;

int dp[MAX_SIZE];
char s[MAX_SIZE];
ll ans = 0;
ll pre1[MAX_SIZE], pre2[MAX_SIZE];
ll suf1[MAX_SIZE], suf2[MAX_SIZE];
ll pw1[MAX_SIZE], pw2[MAX_SIZE];
const ll mod1 = 19260817, mod2 = 1000000007;
const int p1 = 94, p2 = 67;
int n;

// check whether [1, idx / 2] = rev[idx - idx / 2 + 1, idx]
bool palindrome(int idx) {
	ll c11 = (pre1[idx / 2] * pw1[n-idx]) % mod1;
	ll c12 = (suf1[n- idx + idx / 2] - suf1[n - idx] + mod1) % mod1;
	if (c11 != c12) return false;
	ll c21 = (pre2[idx / 2] * pw2[n - idx]) % mod2;
	ll c22 = (suf2[n- idx + idx / 2] - suf2[n - idx] + mod2) % mod2;
	return c21 == c22;
}

int main() {
	int i;
	scanf("%s", s + 1);
	n = strlen(s+1);
	pw1[0] = pw2[0] = pw1[n+1] = pw2[n+1] = 1;
	for (i = 1; i <= n; ++i) {
		pw1[i] = (pw1[i-1] * p1) % mod1;
		pw2[i] = (pw2[i-1] * p2) % mod2;
	}
	
	for (i = 1; i <= n; ++i) {
		pre1[i] = (pre1[i-1] + pw1[i] * s[i]) % mod1;
		pre2[i] = (pre2[i-1] + pw2[i] * s[i]) % mod2;
		suf1[i] = (suf1[i-1] + pw1[i] * s[n-i+1]) % mod1;
		suf2[i] = (suf2[i-1] + pw2[i] * s[n-i +1]) % mod2;
	}
	
	for (i = 1; i <= n; ++i) {
		if (i == 1) {
			dp[1] = 1, ans++;
		} else {
			// check whether string [1, i/2] equals [i - i/2 + 1, i]
			if (palindrome(i)) {
				dp[i] = dp[i/2] + 1;
				ans += dp[i];
			}
		}
	}
	
	printf("%I64d\n", ans);
	return 0;
}