#include <bits/stdc++.h>
#define MAX_SIZE (1926 + 101)
#define MOD 1000000007
typedef long long ll;
using namespace std;

ll dp[MAX_SIZE][MAX_SIZE];
char a[MAX_SIZE], b[MAX_SIZE];
int bi[MAX_SIZE];

int m, d, n;

ll dfs(int pos, int rem, int flag) {
	if (pos == n) return rem == 0;
	if (dp[pos][rem] != -1 && !flag) {
		return dp[pos][rem];
	}
	
	ll ans = 0;
	int i;
	int upper = (flag ? bi[pos] : 9);
	for (i = 0 ; i <= upper; i++) {
		if (pos % 2 == 0 && i == d) continue;
		if (pos % 2 == 1 && i != d) continue;
		ans = ans + dfs(pos + 1, (rem * 10 + i) % m, flag && i == upper);
		ans = ans % MOD;
	}
	
	if (!flag) {
		dp[pos][rem] = ans;
	}
	return ans;
}

ll getans(char s[]) {
	int i, j;
	for (i = 0 ; i < n; i++) {
		for (j = 0 ; j < m; j++) {
			dp[i][j] = -1;
		}
	}
	for (i = 0 ; i < n; i++) {
		bi[i] = s[i] - '0';
		// cout << bi[i] << " ";
	}
	// cout << endl;
	return dfs(0, 0, 1);
}

int isvalid() {
	int i;
	ll ans = 0ll;
	for (i = 0 ; i < n; i++) {
		ans = (ans * 10 + (a[i] - '0')) % m;
		// cout << a[i] << " " << d << endl;
		if (a[i] == d + '0' && i % 2 == 0)
			return 0;
		if (i % 2 == 1 && a[i] != d + '0') return 0;
	}
	
	
	return ans == 0;
}

int main() {
	// COUNT the number of d-magic number between a and b which is divisable by m
	scanf("%d%d", &m, &d);
	scanf("%s", a);
	scanf("%s", b);
	n = strlen(a);
	
	cout << (getans(b) - getans(a) + isvalid() + MOD) % MOD << endl;	
	return 0;
}
