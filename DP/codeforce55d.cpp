#include <bits/stdc++.h>
#define MAX_SIZE 2541
#define MOD 2520

typedef long long ll;

using namespace std;

ll dp[20][50][MAX_SIZE];
int arr[20];
int h[MOD + 1];

int gcd(int a, int b) {
	if (a == 0) return b;
	return gcd(b % a, a);
}

ll dfs(int pos, int lcm, int rem, int flag) {
	if (pos == -1) return rem % lcm == 0;
	if (dp[pos][h[lcm]][rem] != -1 && !flag) return dp[pos][h[lcm]][rem];
	int upper = flag ? arr[pos] : 9;
	ll ans = 0;
	for (int i = 0 ; i <= upper; i++) {
		ans = ans + dfs(pos - 1, (i != 0 ? (lcm * i / gcd(lcm, i)) : lcm), (rem * 10 + i) % MOD
			, flag && i == upper);
	}
	
	if (!flag) dp[pos][h[lcm]][rem] = ans;
	return ans;
}

ll solve(ll a) {
	int curr = 0;
	while (a > 0) {
		arr[curr++] = a % 10;
		a = a / 10;
	}
	
	return dfs(curr - 1, 1, 0, 1);
}

int main(int argc, char *argv[]) {
	int T, i, cnt = 0;
	scanf("%d", &T);
	for (i = 1; i <= MOD; i++) {
		if (MOD % i == 0) {
			h[i] = cnt++;
		}
	}
	memset(dp, -1, sizeof(dp));
	while (T > 0) {
		ll a, b;		
		scanf("%lld%lld", &a, &b);
		ll r1 = solve(a - 1);
		ll r2 = solve(b);
		cout << r2 - r1 << endl;
		T--;
	}
	return 0;
}
