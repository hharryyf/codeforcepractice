#include <bits/stdc++.h>
#define MOD 1000000007
using namespace std;

/* dp[i][j] refers to the number of ways to fill the first i elements of the array
   that the sum of these elements mod 3 is j */
long long dp[2][3];
// the num[0] refers to how many num between l, r mod 3 is 0
// num[1] and num[2] is defined similarly
long long num[3];

void cal(int l, int r);

int main(int argc, char *argv[]) {
	int i, l, r, n;
	cin >> n >> l >> r;
	cal(l, r);
	// cout << num[0] << " " << num[1] << " " << num[2] << endl;
	dp[0][0] = num[0] % MOD;
	dp[0][1] = num[1] % MOD;
	dp[0][2] = num[2] % MOD;
	for (i = 1; i < n; i++) {
		dp[i % 2][0] = (dp[(i-1) % 2][0] * num[0]) % MOD +
						(dp[(i-1) % 2][1] * num[2]) % MOD + 
						(dp[(i-1) % 2][2] * num[1]) % MOD;
						
		dp[i % 2][1] = (dp[(i-1) % 2][0] * num[1]) % MOD 
						+ (dp[(i-1) % 2][2] * num[2]) % MOD
						+ (dp[(i-1) % 2][1] * num[0]) % MOD;
						
		dp[i % 2][2] = (dp[(i-1) % 2][0] * num[2]) % MOD 
						+ (dp[(i-1) % 2][2] * num[0]) % MOD
						+ (dp[(i-1) % 2][1] * num[1]) % MOD;  
	}
	cout << (dp[(n - 1) % 2][0] % MOD) << endl;
	return 0;
}

void cal(int l, int r) {
	int u3, l3;
	u3 = r - (r % 3);
	l3 = l + (3 - (l % 3)) % 3;
	num[0] = max((u3 - l3) / 3 + 1, 0);
	int u1, l1;
	u1 = r - ((r % 3) + 2) % 3;
	l1 = l + (4 - (l % 3)) % 3;
	num[1] = max((u1 - l1) / 3 + 1, 0);
	int u2, l2;
	u2 = r - ((r % 3) + 1) % 3;
	l2 = l + (5 - (l % 3)) % 3;
	num[2] = max((u2 - l2) / 3 + 1, 0);
}
