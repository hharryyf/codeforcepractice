#include <bits/stdc++.h>
#define MAX_SIZE 711
#define BLUE 1
#define NOC 2
#define RED 0
#define MOD 1000000007

typedef long long ll;
using namespace std;


ll dp[MAX_SIZE][MAX_SIZE][3][3];
int match[MAX_SIZE];
char str[MAX_SIZE];

void dfs(int l, int r) {
	if (l >= r) return;
	if (l + 1 == r) {
		dp[l][r][RED][NOC] = 1ll;
		dp[l][r][BLUE][NOC] = 1ll;
		dp[l][r][NOC][RED] = 1ll;
		dp[l][r][NOC][BLUE] = 1ll;
		return;
	}	
	
	if (match[l] == r) {
		dfs(l+1, r-1);
		dp[l][r][RED][NOC] = dp[l+1][r-1][BLUE][NOC] + dp[l+1][r-1][BLUE][BLUE] +
		                     dp[l+1][r-1][BLUE][RED] + dp[l+1][r-1][NOC][NOC] + 
		                     dp[l+1][r-1][NOC][BLUE] + dp[l+1][r-1][NOC][RED]; 
		dp[l][r][BLUE][NOC] = dp[l+1][r-1][RED][NOC] + dp[l+1][r-1][RED][BLUE] + 
							  dp[l+1][r-1][RED][RED] + dp[l+1][r-1][NOC][NOC] + 
							  dp[l+1][r-1][NOC][BLUE] + dp[l+1][r-1][NOC][RED];
		dp[l][r][NOC][BLUE] = dp[l+1][r-1][BLUE][NOC] + dp[l+1][r-1][BLUE][RED] + 
							  dp[l+1][r-1][RED][NOC] + dp[l+1][r-1][RED][RED] + 
							  dp[l+1][r-1][NOC][NOC] + dp[l+1][r-1][NOC][RED];
		dp[l][r][NOC][RED] = dp[l+1][r-1][BLUE][NOC] + dp[l+1][r-1][BLUE][BLUE] + 
							 dp[l+1][r-1][RED][NOC] + dp[l+1][r-1][RED][BLUE] + 
							 dp[l+1][r-1][NOC][NOC] + dp[l+1][r-1][NOC][BLUE];
	} else {
		dfs(l, match[l]);
		dfs(match[l] + 1, r);
		int index = match[l];
		for (int i = 0 ; i < 3; i++) {
			for(int j = 0 ; j < 3; j++) {
				for (int k = 0 ; k < 3; k++) {
					for (int p = 0 ; p < 3; p++) {
						if (k != p || (k == NOC && p == NOC)) {
							dp[l][r][i][j] = dp[l][r][i][j] + (dp[l][index][i][k] * dp[index + 1][r][p][j]) % MOD;
							dp[l][r][i][j] %= MOD;
						}
 					}
				}
			}
		}
	}
	
	for (int i = 0 ; i < 3; i++) {
		for (int j = 0 ; j < 3; j++) {
			dp[l][r][i][j] %= MOD;
		}
	}
}

int main() {
	scanf("%s", str);
	stack<int> s;
	int i, n = strlen(str), j;
	
	for (i = 0 ; i < n; i++) {
		if (str[i] == '(') {
			s.push(i);
		} else {
			match[s.top()] = i;
			s.pop();
		}
 	}
	
	ll ans = 0ll;
	dfs(0, n - 1);
	for (i = 0 ; i < 3; i++) {
		for (j = 0 ; j < 3; j++) {
			ans = ans + dp[0][n-1][i][j];
		}
	}
	
	cout << ans % MOD << endl;
	return 0;
}
