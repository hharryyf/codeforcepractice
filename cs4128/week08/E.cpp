#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 1004

typedef long long ll;



using namespace std;

ll c[MAX_SIZE][MAX_SIZE];
int n;
int pref[MAX_SIZE];
ll dp[MAX_SIZE];

void precompute() {
	int i, j;
	for (i = 0; i <= 1000; i++) {
		c[i][0] = 1;
	}	
	
	for (i = 1; i <= 1000; i++) {
		for (j = 1; j <= i; j++) {
			c[i][j] = c[i-1][j] + c[i-1][j-1];
			c[i][j] %= MOD;
		}
	}
}

int main() {
	int i;
	precompute();
	scanf("%d", &n);
	dp[1] = 1;
	scanf("%d", &pref[1]);
	for (i = 2; i <= n; i++) {
		int v;
		scanf("%d", &v);
		pref[i] = v + pref[i-1];
		dp[i] = (dp[i-1] * c[pref[i]-1][v-1]) % MOD;
	}
	
	cout << dp[n] << endl;
	return 0;
}
