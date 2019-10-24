#include <bits/stdc++.h>
#define MAX_SIZE 5111

typedef long long ll;

using namespace std;

ll dp[2][MAX_SIZE];

vector<int> disc;

int a[MAX_SIZE];
int b[MAX_SIZE];

int n;

int main() {
	scanf("%d", &n);
	int i, j;
	for (i = 0 ; i < n; i++) {
		scanf("%d", &a[i]);
		b[i] = a[i];
	}
	
	sort(b, b + n);
	for (i = 0 ; i < n; i++) {
		if (i == 0 || b[i] != b[i-1]) {
			disc.push_back(b[i]);
		} 
	}
	
	int m = (int) disc.size();
	
	/* 
		dp[i][j] the minimum moves that would make the first i numbers in non decreasing order
		with ith number at most disc[j]
		
		dp[0][i] = dp[0][i-1], abs(disc[i] - a[0])
		dp[i][0] = dp[i-1][0] + abs(disc[0] - a[i])
	*/
	dp[0][0] = abs(a[0] - disc[0]);
	for (i = 1 ; i < m; i++) {
		dp[0][i] = min(dp[0][i-1], (ll) abs(disc[i] - a[0]));
	}
	
	for (i = 1; i < n; i++) {
		for (j = 0; j < m; j++) {
			if (j == 0) {
				dp[i % 2][0] = dp[(i - 1) % 2][0] + (ll) abs(disc[0] - a[i]);
			} else {
				dp[i % 2][j] = min(dp[i % 2][j-1], dp[(i - 1) % 2][j] + (ll) abs(disc[j] - a[i]));
			}
		}
	}
	
	cout << dp[(n-1) % 2][m - 1] << endl;
	return 0;
}
