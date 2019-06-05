#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#define MAX_LEN 513

using namespace std;

char str[MAX_LEN];
/*
	let dp[i][j] refers to the minimum number of time requires to remove 
	everything from i to j
	
	consider the leftmost character str[i]:
	dp[i][j] = 1 + dp[i+1][j]  -> remove the leftmost character first
	dp[i][j] = dp[i+1][k-1] + dp[k][j] -> if str[k] == str[i], merge together i and k
	and make a removal on i+1, k-1 and k, j seperately
*/
vector<vector<int> > dp;
int f(int start, int end);

int main(int argc, char *argv[]) {
	int n;
	cin >> n;
	scanf("%s", str);
	dp = vector<vector<int> >(n, vector<int>(n, MAX_LEN));
	cout << f(0, n - 1) << endl;
	return 0;
}

int f(int start, int end) {
	if (start > end) return 0;
	if (start == end) return 1;
	if (dp[start][end] != MAX_LEN) return dp[start][end];
	int ans = 1 + f(start + 1, end);
	int i;
	for (i = start + 1; i <= end; i++) {
		if (str[i] == str[start]) {
			ans = min(ans, f(i, end) + f(start + 1, i - 1));
		}
	}
	
	dp[start][end] = ans;
	return ans;
}
