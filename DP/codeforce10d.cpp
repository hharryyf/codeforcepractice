#include <bits/stdc++.h>
#define MAX_LEN 514

using namespace std;

int a[MAX_LEN];
int b[MAX_LEN];
int dp[MAX_LEN][MAX_LEN];

int main(int argc, char *argv[]) {
	int n, m, i, j;
	cin >> n;
	for (i = 1 ; i <= n; i++) {
		cin >> a[i];
	}
	
	cin >> m;
	for (i = 1 ; i <= m; i++) {
		cin >> b[i];
	}
	
	/*
		we define dp[i][j] as the maximum length of the LCIS such that
		it ends at the ith element of a and use upto the jth element of 
		suppose a[i] == b[j]:
			dp[i][j] = 1 + max(dp[p][j-1]) which p < i and a[p] < a[i]
		suppose a[i] != b[j]:
			dp[i][j] = dp[i][j-1]
	*/
	int ans = 0;
	for (j = 1; j <= m; j++) {
		int f = 0;
		for (i = 1; i <= n; i++) {
			if (a[i] != b[j]) {
				dp[i][j] = dp[i][j-1];
			}
			
			if (a[i] < b[j]) {
				f = max(f, dp[i][j-1]);
			}
			
			/*
				the only values we are interested in are
				a[k] < a[i] and in other words the maximum value
				of dp[k][j-1] such that a[k] < b[j]
					
				we update the maximum dp[k][j-1] when we see a value
				a[k] < b[j]
			*/
			
			if (a[i] == b[j]) {
				dp[i][j] = f + 1;
				ans = max(ans, dp[i][j]);
			} 
		}
	}
	
	cout << ans << endl;
	if (ans == 0) return 0;
	vector<int> res = vector<int>();
	i = n;
	j = m;
	while (i > 0 && j > 0) {
		if (ans == dp[i][j]) {
			if (a[i] == b[j]) {
				res.push_back(a[i]);
				i--;
				j--;
				ans--;	
			} else {
				j--;
			}
		} else {
			i--;
		}
	}
	
	reverse(res.begin(), res.end());
	cout << res[0];
	for (i = 1; i < (int) res.size(); i++) {
		cout << " " << res[i];
	}
	cout << endl;
	return 0;
}
