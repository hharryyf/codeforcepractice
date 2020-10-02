#include <bits/stdc++.h>
#define MAXN 1000005
#define ll long long int
using namespace std;
const ll mod = 1000000007L;

string s;
ll dp[MAXN][4][2];
void calc(int at, char is) {
	if (is == '?') {
		calc(at, '0');
		calc(at, '1');
		calc(at, '2');
		calc(at, '*');
		return;
	}
	if (at == 0) {
		if (is == '0') {
			dp[at][0][0] = 1;
			dp[at][0][1] = 0;
		}
		if (is == '1') {
			dp[at][1][0] = 0;
			dp[at][1][1] = 1;
		}
		if (is == '2') {
			dp[at][2][0] = 0;
			dp[at][2][1] = 0;
		}
		if (is == '*') {
			dp[at][3][0] = 1;
			dp[at][3][1] = 1;
		}
	} else {
		if (is == '0') {
			dp[at][0][0] += dp[at-1][0][0];
			dp[at][0][0] += dp[at-1][1][0];
		}
		if (is == '1') {
			dp[at][1][0] += dp[at-1][3][0];
			dp[at][1][1] += dp[at-1][0][0];
			dp[at][1][1] += dp[at-1][1][0];
		}
		if (is == '2') {
			dp[at][2][1] += dp[at-1][3][0];
		}
		if (is == '*') {
			dp[at][3][0] += dp[at-1][1][1];
			dp[at][3][0] += dp[at-1][2][1];
			dp[at][3][0] += dp[at-1][3][1];
			dp[at][3][1] += dp[at-1][1][1];
			dp[at][3][1] += dp[at-1][2][1];
			dp[at][3][1] += dp[at-1][3][1];
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			dp[at][i][j] = dp[at][i][j] % mod;
		}
	}
}

int main() {
	cin >> s;
	for (int i = 0; i < s.length(); i++) calc(i, s[i]);
	ll answer = 0;
	for (int i = 0; i <= 3; i++) {
		answer += dp[s.length()-1][i][0];
		answer %= mod;
	}
	cout << answer << endl;
}
