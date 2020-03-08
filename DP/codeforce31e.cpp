#include <bits/stdc++.h>
#define MOD 1000000007
typedef long long ll;
using namespace std;

int n;
ll dp[19][19];
pair<int, int> pre[19][19];
char s[41];
ll p[19];

int main(){
	int i, j;
	p[0] = 1;
	for (i = 1; i <= 18; i++) p[i] = p[i-1] * 10;
	scanf("%d", &n);
	scanf("%s", s);
	for (i = 1; i <= n; i++) {
		dp[0][i] = dp[0][i-1] + p[i - 1] * (s[2 * n - i] - '0');
		pre[0][i] = {0, i - 1};
		dp[i][0] = dp[0][i];
		pre[i][0] = {i-1, 0};
	}
	
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			// dp[i][j-1] + p[j-1] * (s[2 * n - i - j] - '0')
			dp[i][j] = dp[i][j-1] + p[j-1] * (s[2 * n - i - j] - '0');
			if (dp[i][j] < dp[i-1][j] + p[i-1] * (s[2 * n - i - j] - '0')) {
			   dp[i][j] = dp[i-1][j] + p[i-1] * (s[2 * n - i - j] - '0');
			   pre[i][j] = {i-1, j};
			} else {
			   pre[i][j] = {i, j - 1};
			}
		}
	}
	
	i = n, j = n;
	string ans;
	while (i != 0 || j != 0) {
		  int cx = pre[i][j].first;
		  int cy = pre[i][j].second;
		  if (i - cx == 1) {
		  	 ans += 'H';
		  } else {
		     ans += 'M';
		  }
		  i = cx, j = cy;
	}
	
	cout << ans << endl;
	return 0;
}

